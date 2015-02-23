import java.io.FileInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.util.Scanner;

public class PGMReader {
    // Reads a PGM file 
    // credit to BalusC http://stackoverflow.com/questions/3639198/how-to-read-pgm-images-in-java
    // @string filePath location of the file
    public void readPGM(String filePath) throws Exception {
		File file = new File(filePath);
		
		filePath = file.getAbsolutePath();
		
		System.out.println(filePath);
		System.out.flush();
		
        FileInputStream fileInputStream = new FileInputStream(filePath);
        Scanner scan = new Scanner(fileInputStream);
        // Discard the magic number
        scan.nextLine();
        // Discard the comment line
        scan.nextLine();
        // Read pic width, height and max value
        int picWidth = scan.nextInt();
        int picHeight = scan.nextInt();
        int maxvalue = scan.nextInt();

        fileInputStream.close();

        // Now parse the file as binary data
        fileInputStream = new FileInputStream(filePath);
        DataInputStream dis = new DataInputStream(fileInputStream);

        // look for 4 lines (i.e.: the header) and discard them
        int numnewlines = 4;
        while (numnewlines > 0) {
        char c;
            do {
                c = (char)(dis.readUnsignedByte());
            } while (c != '\n');
            numnewlines--;
        }

        // read the image data
        int[][] data2D = new int[picHeight][picWidth];
        for (int row = 0; row < picHeight; row++) {
            for (int col = 0; col < picWidth; col++) {
                data2D[row][col] = dis.readUnsignedByte();
                System.out.print(data2D[row][col] + " ");
            }
            System.out.println();
        }
        //return data2D;
    }

    public static void main(String args[]) {
        PGMReader r = new PGMReader();
        String filePath = "pgm/coins.ascii.pgm";
        try {
			r.readPGM(filePath);
		}
		catch(Exception ex) {
			//ex.printStackTrace();
		}
    }
}
