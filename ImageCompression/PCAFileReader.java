import java.io.FileInputStream;
//import java.io.FileOutputStream;
//import java.io.DataInputStream;
//import java.io.DataOutputStream;
//import java.io.PrintWriter;
import java.io.File;
//import java.nio.ByteBuffer;
import java.util.Scanner;

public class PCAFileReader {
	
	public double[][] readPointData(String filePath) throws Exception {

		File file = new File(filePath);
        	filePath = file.getAbsolutePath();

		FileInputStream fileInputStream = new FileInputStream(filePath);
		Scanner scan = new Scanner(fileInputStream);

		int points = scan.nextInt();
		int dimensions  = scan.nextInt();
		
		double[][] pointData = new double[points][dimensions];
		for (int row = 0; row < points; row++) {
		    for (int col = 0; col < dimensions; col++) {
		    	pointData[row][col] = scan.nextDouble();
		    }
		}
		
		return pointData;
	}
}
