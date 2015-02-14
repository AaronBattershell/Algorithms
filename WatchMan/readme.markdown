<h3>Watch, Man!

<a href="http://acm-ecna.ysu.edu/ProblemSet/ecna2014.pdf" target="_blank">Problem Description <br/>
<a href="http://acm-ecna.ysu.edu/ProblemSet/Problems/I/I.in" target="_blank">Problem Input <br/>
<a href="http://acm-ecna.ysu.edu/ProblemSet/Problems/I/I.out" target="_blank">Problem Output <br/>
<a href="https://docs.google.com/a/zips.uakron.edu/document/d/1o3FiO_CLLbPdnd6F10IHJFM-K7UefA5GbJyx6taoPhw/edit" target="_blank"> Problem Write-up <br/>

<h4>Introduction</h4>
Our solution to the “Watch, Man!” problem and the Ford-Fulkerson network flow problem is written in C++11. In order to compile and run out code, a user needs to have a compiler capable of compiling the C++11 standard. Our environment was Linux, compiled with gcc-4.8, and built with CMake 3.0. 

<h4>How to Run Our Program</h4>
You can compile our code using CMake. Included with our source code is a CMakeLists.txt file. As our project was built on Linux machines, instructions to do so will be in Linux command line. <br/><br/>
$ mkdir build <br/>
$ export cxx=gcc-4.8 <br/>
$ cd build <br/>
$ cmake .. <br/>
$ make <br/> <br/>
At this point, you will have created an executable called ‘watchman.’ Included with our source code at a number of test cases. To run our program with the test cases:<br/>

$ ./watchman -b ../test/filename.txt 0 3 (for BFS cases)<br/>
$ ./watchman -f ../test/filename.txt (for Ford-Fulkerson cases without details)<br/>
$ ./watchman -df ../test/filename.txt (with detailed output)<br/>
$ ./watchman -m ../watchman/filename.txt assignment.txt (for Museum problem)<br/>
