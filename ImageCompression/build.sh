#clean
rm *.class
echo "Cleaning up old class files..."
echo "Recompiling..."
javac SVD.java 
javac PGMProcessor.java 
javac PCAFileReader.java
javac PCA.java
javac Project.java
echo "Done."
