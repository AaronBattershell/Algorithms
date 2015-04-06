<h3>Image compression using SVD and dimensionality reduction using PCA

<a href="http://www.cs.uakron.edu/~duan/class/635/projects/project2/project2.pdf" target="_blank">Problem Description <br/>
<a href="https://docs.google.com/a/zips.uakron.edu/document/d/1s3KPi7sAXxNkcwp0fEZ7fa-yf_9p4oA_cms_RPz45z4/edit" target="_blank">Problem Write-up <br/>
<a href="https://docs.google.com/a/zips.uakron.edu/presentation/d/1ht5pYtdhwtoHnk3AJGOO_OD8LWKVrBcQbgveTFQ0oCI/edit#slide=id.p" target="_blank">Presentation <br/>

<h4>How to Run This Program <br />

The following are instructions for how to run and compile our program. As our project was built on Linux machines, instructions to do so will be in Linux command line. From the root directory: <br />
	
$ cd ejml-v0.26-libs <br />
$ jar xf EJML-core-0.26.jar  <br />
$ mv org ..  <br />
$ cd ..  <br />
$ ./build.sh  <br />

<p>If $ ./build.sh failes verify that you have javac installed using $ javac -version. If you don’t, install it using $ sudo apt-get install openjdk-7-jdk. At this point you will be able to run our program providing it with specific command line arguments.</p>
 
$ java Project 1 pgm/image.pgm (output: image_b.pgm, pgm translated into binary format) <br />
$ java Project 2 image_b.pgm (output: image.pgm, the binary translated into pgm format) <br />
$ java Project 3 header.txt SVD.txt k (output: image_b.pgm.SVD, the three matrices U, Σ, V and an integer k representing the rank of the approximation) <br />
$ java Project 4 image_b.pgm.SVD (output: image_k.pgm, the reversal of what was done in part 3)  <br />

For further documentation view <a href="http://www.cs.uakron.edu/~duan/class/635/projects/project2/project2.pdf" target="_blank">this source.<br/>
