# A small example to demonstrate a potential bug in the PCL PPFEstimation class.

To compile go to the build directory with a terminal and execute 
```
cmake ..; make
```
When it's done start the program with
```
./ppf_object_recognition
```
The program will load the two PCD files in the build folder and run the PPF registration algorithm. This should not result in an error the first time you run the program. Changing the discretization step-size in ppf_object_recognition.cpp (line 26) from 
```
1.0f/8.0f * float(M_PI)
```
to 
```
1.0f/7.0f * float(M_PI)
```
and recompiling and running the program results in a segmentation fault. 
