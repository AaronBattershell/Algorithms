#clean
rm *.class
echo "Cleaning up old class files..."
echo "Recompiling..."
javac SVD.java 
javac PGMProcessor.java 
javac PCA.java
javac Project.java
javac PCAFileReader.java
echo "Done."
