
Computer Graphics, Lab X, Group 4 - Ali Reda Khalife, Finja Papke, Khai-Hao Tram

NOTE: Not all files needed for the project to run have been uploaded along this readme file.
In order to run the code it needs to be added into the given base project that has been provided at the beginning of the course.
We decided to only hand in the original parts of the code that we either edited or added in completely.
If this might cause problems, please let us know.

These files contain the results of tasks 4 and 5 (we mentioned that we skipped Problem 2 c of task 4 to begin directly with 5 instead).

To use the program:

1. Add in your local directory path leading to the desired .obj-file that you want to draw (starting at line 45 with method ReadData in oglwidget.cpp).
   We provided the following files for testing out the program along the given files:
	- The gem shape, Primo.obj
	- The game controller shape in low-poly style, ps4.obj

2. If you want to draw ...
	- ... just the control mesh, comment out the SubdivLevel-method in line 65 of oglwidget.cpp.
	- ... the shape with the Loop subdivision applied once, give a 1 as the second parameter of the SubdivLevel-method call.
	- ... the shape with the Loop subdivision applied twice, give a 2 as the second parameter of the SubdivLevel-method call.

3. Click run. The shape should pop up in a separate window, drawn with the faces in red or blue and the outlines in yellow.
	NOTE!!!
	The scaling of the view possibly needs to be adjusted depending on the loaded file 
	(adjust float values in line 281 of oglwidget.cpp).

Thanks for reading :)
