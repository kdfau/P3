/// @file
 
#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
 
#include "wavfile_mono.h"
#include "pitch_analyzer.h"
 
#include "docopt.h"
 
#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */
 
using namespace std;
using namespace upc;
 
static const char USAGE[] = R"(
get_pitch - Pitch Detector
 
Usage:
    get_pitch [options] <input-wav> <output-txt>
    get_pitch (-h | --help)
    get_pitch --version
 
Options:
    -1 FLOAT, --pot_th FLOAT     Umbral potencia en dB [default: -20]
    -2 FLOAT, --r1_th FLOAT    Umbral autocorrelación normalizada [default: 0.9]
    -3 FLOAT, --rlag_th FLOAT  Umbral autocorrelación normalizada en pitch [default: 0.4]
    -h, --help  Show this screen
    --version   Show the version of the project
   
Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the detection:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";
 
int main(int argc, const char *argv[]) {
  /// \TODO
  ///  Modify the program syntax and the call to **docopt()** in order to
  ///  add options and arguments to the program.
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},  // array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string
 
  std::string input_wav = args["<input-wav>"].asString();
  std::string output_txt = args["<output-txt>"].asString();
  float p = atof(args["--pot_th"].asString().c_str());
  float r1 = atof(args["--r1_th"].asString().c_str());
  float rlag = atof(args["--rlag_th"].asString().c_str());
 
  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }
 
  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;
 
  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, p, r1, rlag, PitchAnalyzer::HAMMING, 50, 500); //antes era Hamming
  //analyzer.thresh1 = thresh1;
 
  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  /// \DONE
  /// Central clipping
  float maximo = *max_element(x.begin(), x.end());
  
  #if 1
    for(int i=0; i<(int)x.size(); ++i){
      if((abs(x[i]) / maximo ) < 0.001){
        x[i]=0.0F;
    }
  }
  #endif

  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }
 
  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
  /// \DONE
  /// Median Filter
  #if 0 //Per compilar només si està definit => evitem errors al executar el run_get_pitch
    int win_median = 3;
    for (long unsigned int i = 0; i < f0.size(); i += win_median){
      for (long unsigned int j = 0; j < f0.size(); ++j)
        f0[i+j] = f0[i + (win_median -1) / 2];
    }
  #endif


  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }
 
  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX)
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur
 
  return 0;
}