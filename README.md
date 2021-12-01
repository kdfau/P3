PAV - P3: detección de pitch
============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la detección de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
	
	![image](https://user-images.githubusercontent.com/91891272/144233228-c7b6cb81-8640-432f-a91d-0964b50bd62d.png)

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.
	 
	 ![Autocorrelacio](https://user-images.githubusercontent.com/91891272/144233379-2aeb37a5-9549-4506-b5ab-696fc92c920b.png)
	 Como vemos el periodo de pitch es de aproximadamente 5 seg. 
	 La posición del primer máximo secundario es de 20-25 muestras desdel primer maximo. 

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.
	
	![image](https://user-images.githubusercontent.com/91891272/144234262-47235192-9757-4de9-a435-6eb2f71904dc.png)
	Lo que vemos comentado fue la primera implementación, más adelante con el objetivo de mejorar los valores obtenidos
	llegamos al codigo que vemos en la captura. 
	
   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
   
   	![image](https://user-images.githubusercontent.com/91891272/144234436-c6828c6c-3c6f-4744-9cf6-e5ecde1636d2.png)
	En los comentarios podemos ver la evolucion desde lo que hicimos en clase hasta la versión final de este codigo. 
	Pensamos que una buena forma de obtener la diferencia entre tramas sonoras o sordas era usando los umbrales de 
	autocorrelaciones vistos en clase.

- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.
		
		![Captura_wavesurfer1](https://user-images.githubusercontent.com/91891272/144306993-2ab8e81a-ba18-4e8b-889a-f7b525ddcd4a.PNG)

		En la primera(empezando por arriba) vemos la potencia de la señal, en la segunda vemos la autocorrelación
		normalizada, es decir, r[1]/r[0], y en la tercera vemos la autocorrelación en su máximo secundario, es decir, 
		r[lag]/r[0], finalmente vemos la señal. 
		
		De la potencia vemos que se corresponde con los tramos sonoros y sordos pero no es un dato significativo por si sólo. 
		Las autocorrelaciones, por lo estudiado en teoria, són algo más útiles para encontrar el pitch puesto que las formas
		de onda se parecen mas cuando son tramos sordos o sonoros. 
		De aquí sacamos que lo más útil para detectar el pitch es usar todos los parámetros anteriores. 
		
      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.
  
  		
		![image](https://user-images.githubusercontent.com/91891272/144302950-d66cb7ee-a78c-4cad-b9af-0a817059a4ef.png)


  		
		Como vemos nuestro detector de pitch coincide bastante con el pitch del wavesurfer, aunque no es ideal. 
		
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

	![image](https://user-images.githubusercontent.com/91891272/144249118-671c66b3-c6b9-45e7-b08f-966601ff39ab.png)
	
	![image](https://user-images.githubusercontent.com/91891272/144249581-6bf1dbea-d0d2-4e61-b389-086e2ae02811.png)

   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
   
   ![image](https://user-images.githubusercontent.com/91891272/144305416-68b53512-780f-492b-ba38-753f2033c304.png)
   

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
	 
	 ![image](https://user-images.githubusercontent.com/91891272/144250040-2e39f569-bbcc-4d6e-8ae2-411eb74728df.png)

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.

  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.

  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el detector, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al detector. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
  
  Para mejorar nuestro detector hemos decidido implementar center-clipping como preprocesado y el filtro de mediana como postprocesado. 
  
  Aquí podemos ver el código del center-clipping: 
  
 ![image](https://user-images.githubusercontent.com/91891272/144264161-61f52754-b397-49d0-8e52-803b9b455087.png)

  
  Aquí podemos ver el código del filtro de mediana: 
  
![image](https://user-images.githubusercontent.com/91891272/144250906-e56ee85a-eb12-4557-9adb-64504f6d9277.png)

  Y aquí vemos los resultados finales obetenidos: 
  
Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
