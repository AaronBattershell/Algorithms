import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.PrintWriter;
import java.io.File;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class PGMProcessor {

    public int maxvalue;
    public int picWidth;
    public int picHeight;

    // Creates a PGM File based on array input 
    // @string outputPath location of the file
    // @int[][] grid 2D array of integers representing PGM files
    public void printPGM(String outputPath, int grid[][]) throws Exception {
        new File(outputPath).getParentFile().mkdirs();
        
        int maxValue = 0;
        PrintWriter writer = new PrintWriter(outputPath);
        
        writer.println("P2");
        writer.println("# " + outputPath);
        writer.println(grid[0].length + " " + grid.length);
        writer.println(maxvalue);
        
        for (int arr[] : grid) {
            for (int iter : arr) {
                maxValue = Math.max(iter, maxValue);
            }
        }
        
        writer.println(maxValue);
        
        for (int i = 0; i < grid.length; ++i) {
            for (int n = 0; n < grid[0].length; ++n) {
                maxValue = Math.max(grid[i][n], maxValue);
                writer.print((n != 0 ? " " : "") + grid[i][n]);
            }
            writer.print((i != grid.length - 1 ? "\n" : ""));
        }
        
        writer.close();
    }

    public void writeBinaryPGM(String outputPath, int grid[][]) throws Exception {
        File file = new File(outputPath);

        String filePath = file.getAbsolutePath();

        //convert PGM grid into array of shorts (2 bytes)

        //array of 2 byte arrays
        byte[][] bytes = new byte[picHeight * picWidth][2];
        int byteNum = bytes.length;

        int count = 0; //used for keeping track of num of bytes processed
        for(int i = 0; i < picHeight; ++i) {
            for(int j = 0; j < picWidth; ++j) {
                ByteBuffer bb = ByteBuffer.allocate(2);
                short val = (short) grid[i][j];
                bb.putShort(val);
                if(count < byteNum) {
                    bytes[count] = bb.array();
                }
                ++count;
            }
        }

        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(filePath);
            //write the width integer
            short sWide = (short) picWidth;
            ByteBuffer bWide = ByteBuffer.allocate(2);
            bWide.putShort(sWide);
            fos.write(bWide.array());

            //wrie the height integer
            short sHei = (short) picHeight;
            ByteBuffer bHei = ByteBuffer.allocate(2);
            bHei.putShort(sHei);
            fos.write(bHei.array());

            //write the byte representing maxvalue
            fos.write(((Integer)maxvalue).byteValue());

            for(byte[] b : bytes) {
                fos.write(b);
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            fos.close();
        }
    }

    // Reads a PGM file 
    // credit to BalusC http://stackoverflow.com/questions/3639198/how-to-read-pgm-images-in-java
    // modified because their implementation was not actually correct
    // @string filePath location of the file
    public int[][] readPGM(String filePath) throws Exception {

		File file = new File(filePath);
		
		filePath = file.getAbsolutePath();
		
        FileInputStream fileInputStream = new FileInputStream(filePath);
        Scanner scan = new Scanner(fileInputStream);
        // Discard the magic number
        scan.nextLine();
        // Discard the comment line
        scan.nextLine();
        // Read pic width, height and max value
        picWidth = scan.nextInt();
        picHeight = scan.nextInt();
        maxvalue = scan.nextInt();

        // read the image data
        int[][] data2D = new int[picHeight][picWidth];
        for (int row = 0; row < picHeight; row++) {
            for (int col = 0; col < picWidth; col++) {
                data2D[row][col] = scan.nextInt();
            }
        }

        return data2D;
    }
    
    //reads bytes from fileinputstream
    //converts bytes back into integers and then outputs PGM
    public int[][] binaryToPgm(String filePath) throws Exception {
		//values we're looking for
		short width = 0;
		short height = 0;
		short max = 0;
		
		//read in the file
		File file = new File(filePath);
		filePath = file.getAbsolutePath();
		FileInputStream fis = new FileInputStream(filePath);
		//first 2 bytes are the width
		try {
			byte[] buffer = new byte[2];
			fis.read(buffer);
			ByteBuffer bb = ByteBuffer.wrap(buffer);
			width = bb.getShort();
			System.out.println(width);
		}
		catch(Exception e) {
			System.err.println("Failed to get width bytes");
		}
		//second 2 bytes are the length
		try {
			byte[] buffer = new byte[2];
			fis.read(buffer);
			ByteBuffer bb = ByteBuffer.wrap(buffer);
			height = bb.getShort();
			System.out.println(height);
		}
		catch(Exception e) {
			System.err.println("Failed to get height bytes");
		}
		//next is one byte for the maxvalue
		try {
			int in = fis.read();
			if(in != -1)
				System.out.println(in);
		}
		catch(Exception e) {
			System.err.println("Failed to get max value bytes");
		}
		
		int[][] grid = new int[height][width];
		//last is a bunch of 2 bytes for the image grid
		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < width; ++j) {
				byte[] buffer = new byte[2];
				fis.read(buffer);
				ByteBuffer bb = ByteBuffer.wrap(buffer);
				grid[i][j] = (int) bb.getShort();
			}
		}
		
		return grid;
	}

    public static void main(String args[]) {
        PGMProcessor r = new PGMProcessor();
        String filePath = "pgm/baboon.ascii.pgm";
        try {
			int[][] out = r.readPGM(filePath);
            //r.printPGM("pgm_files/out.pgm", out);
            r.writeBinaryPGM("pgm_out/out.bin", out);
            int[][] pgm = r.binaryToPgm("pgm_out/out.bin");
            r.printPGM("pgm_out/out.pgm", pgm);
		}
		catch(Exception ex) {
			//ex.printStackTrace();
		}
    }
}
