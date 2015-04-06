import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.PrintWriter;
import java.io.File;
import java.nio.ByteBuffer;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.BitSet;
import java.math.BigInteger;
import org.ejml.simple.*;

public class PGMProcessor {

    public int maxvalue;
    public int picWidth;
    public int picHeight;

    // Creates a PGM File based on array input 
    // @string outputPath location of the file
    // @int[][] grid 2D array of integers representing PGM files
    public void printPGM(String outputPath, int grid[][]) throws Exception {
        File file = new File(outputPath);
        
        int maxValue = 0;
        PrintWriter writer = new PrintWriter(outputPath);
        
        writer.println("P2");
        writer.println("# " + outputPath);
        writer.println(grid[0].length + " " + grid.length);
        
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
        byte[] bytes = new byte[picHeight * picWidth];
        int byteNum = bytes.length;

        int count = 0; //used for keeping track of num of bytes processed
        for(int i = 0; i < picHeight; ++i) {
            for(int j = 0; j < picWidth; ++j) {
                byte val = ((Integer)grid[i][j]).byteValue();
                if(count < byteNum) {
                    bytes[count] = val;
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

            for(byte b : bytes) {
                fos.write(b);
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            fos.close();
        }

        System.out.println("Binary size: " + file.length());
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

        System.out.println("Width: " + picWidth);
        System.out.println("Height: " + picHeight);
        System.out.println("Maxvalue: " + maxvalue);

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
				
				grid[i][j] = fis.read();
			}
		}
		
		return grid;
	}

    public void pgmToSVD(String headerPath, String svdPath, int[][] grid) throws Exception {

        int height = grid.length;
        int width = grid[0].length;

        //convert all the ints to doubles for ejml library
        double[][] dGrid = new double[height][width];
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                dGrid[i][j] = (double) grid[i][j];
            }
        }

        //perform svd
        SimpleMatrix A = new SimpleMatrix(dGrid);
        SimpleSVD svd = A.svd();

        SimpleMatrix U = svd.getU();
        SimpleMatrix W = svd.getW();
        SimpleMatrix V = svd.getV();

        //write the output
        File headerFile = new File(headerPath);
        File svdFile = new File(svdPath);

        headerFile = new File("pgm_svd/" + headerFile.getName());
        svdFile = new File("pgm_svd/" + svdFile.getName());

        PrintWriter headWriter = new PrintWriter(headerFile);
        PrintWriter svdWriter = new PrintWriter(svdFile);

        //write to the header file
        //write the width
        headWriter.write(width + " ");
        //write the height
        headWriter.write(height + " ");
        //write the maxValue
        headWriter.write(maxvalue + " ");
        headWriter.close();

        //write the matrices
        //write U first
        int Ucols = U.numCols();
        int Urows = U.numRows();
        for(int row = 0; row < Urows; ++row) {
            for(int col = 0; col < Ucols; ++col) {
                float value = (float)(U.get(row, col));
                svdWriter.write(value + " ");
            }
        }

        //write the w matrix
        int Wcols = W.numCols();
        int Wrows = W.numRows();
        for(int row = 0; row < Wrows; ++row) {
            for(int col = 0; col < Wcols; ++col) {
                float value = (float)(W.get(row, col));
                svdWriter.write(value + " ");
            }
        }
        //write the V matrix
        int Vcols = V.numCols();
        int Vrows = V.numRows();
        for(int row = 0; row < Vrows; ++row) {
            for(int col = 0; col < Vcols; ++col) {
                float value = (float)(V.get(row, col));
                svdWriter.write(value + " ");
            }
        }

        svdWriter.close();
    }

    public void svdPGMApprox(String headerPath, String svdPath, int k) throws Exception {
        File headerFile = new File(headerPath);
        File svdFile = new File(svdPath);

        Scanner sc = new Scanner(headerFile);
        int width = 0;
        int height = 0;
        int maxValue = 0;
        try {
            width = sc.nextInt();
            height = sc.nextInt();
            maxValue = sc.nextInt();
        } catch(Exception e) {
            System.err.println("Invalid header file");
        }

        sc = new Scanner(svdFile);
        int m = height;
        int n = width;
        //U is an m x m matrix stored first in the file
        double[][] u = new double[m][m];
        for(int row = 0; row < m; ++row) {
            for(int col = 0; col < m; ++col) {
                u[row][col] = (double) sc.nextFloat();
            }
        }

        //W is an m x n matrix stored second in the file
        double[][] w = new double[m][n];
        for(int row = 0; row < m; ++row) {
            for(int col = 0; col < n; ++col) {
                w[row][col] = (double) sc.nextFloat();
            }
        }

        //V is an n x n matrix stored last in the file
        double[][] v = new double[n][n];
        for(int row = 0; row < n; ++row) {
            for(int col = 0; col < n; ++col) {
                v[row][col] = (double) sc.nextFloat();
            }
        }

        SimpleMatrix U = new SimpleMatrix(u);
        SimpleMatrix W = new SimpleMatrix(w);
        SimpleMatrix V = new SimpleMatrix(v);

        //get the 2 norm of the matrix

        SimpleMatrix Uprime = U.extractMatrix(0, SimpleMatrix.END, 0, k);
        SimpleMatrix Wprime = W.extractMatrix(0, k, 0, k);
        SimpleMatrix Vprime = V.extractMatrix(0, SimpleMatrix.END, 0, k);

        File file = new File("image_b.pgm.SVD");
        File raw = new File("image_out.SVD.txt");

        FileOutputStream fos = null;

        ArrayList<byte[]> bin = new ArrayList<byte[]>();

        try {
            fos = new FileOutputStream(file);

            //store width
            ByteBuffer bb = ByteBuffer.allocate(2);
            bb.putShort((short) width);
            fos.write(bb.array());
            //store height
            bb = ByteBuffer.allocate(2);
            bb.putShort((short) height);
            fos.write(bb.array());
            //store maxvalue
            bb = ByteBuffer.allocate(2);
            bb.putShort((short) maxValue);
            fos.write(bb.array());
            //store num of eigen values
            bb = ByteBuffer.allocate(2);
            bb.putShort((short) k);
            fos.write(bb.array());

        } catch(Exception e) { e.printStackTrace(); }


        //store array of truncated floats
        try {

            //write U first
            int Ucols = Uprime.numCols();
            int Urows = Uprime.numRows();
            // System.out.println("UCols: " + Ucols + ", Urows: " + Urows);
            for(int row = 0; row < Urows; ++row) {
                for(int col = 0; col < Ucols; ++col) {
                    //to store a decimal value as a short we multiply by 100000
                    // we know it can never exceed the size of short because vectors are orthogonal
                    // therefore being no larger than 1
                    byte[] value = encode( (float)(Uprime.get(row, col)) );
                    bin.add(value);
                    fos.write(value);
                }
            }

            //extract eigen values
            SimpleMatrix diag = Wprime.extractDiag();
            int diagCols = diag.numCols();
            int diagRows = diag.numRows();
            // System.out.println("WCols: " + diagCols + ", Wrows: " + diagRows);
            for(int row = 0; row < diagRows; ++row) {
                for(int col = 0; col < diagCols; ++col) {
                    byte[] value =  encode( (float)(diag.get(row, col)) );
                    bin.add(value);
                    fos.write(value);
                }
            }

            //write the V matrix

            int Vcols = Vprime.numCols();
            int Vrows = Vprime.numRows();
            // System.out.println("VCols: " + Vcols + ", Vrows: " + Urows);
            for(int row = 0; row < Vrows; ++row) {
                for(int col = 0; col < Vcols; ++col) {
                    byte[] value = encode( (float)(Vprime.get(row, col)) );
                    bin.add(value);
                    fos.write(value);
                }
            }

            fos.close();
        }

        catch(Exception e) { e.printStackTrace(); }

        // get the 2 norm
        // the 2 norm is the eigenvalue at position (k, k)
        // normally its K+1 but java is 0-based indexing
        System.out.println("2norm: " + W.get(k, k));

        long origin_s = width * height * 4;
        long comp_s = file.length();
        double comp_rate = (origin_s - comp_s)  * 1.0 / origin_s;
        System.out.println("Approx Original size: " + origin_s + " bytes." );
        System.out.println("SVD size: " + comp_s + " bytes");
        System.out.println("Approx Compression rate: " + (comp_rate * 100) + "%");
    }

    public void binarySVDtoPGM(String filePath) {
        //values we're looking for
        short width = 0;
        short height = 0;
        short maxValue = 0;
        short k = 0;
        
        //read in the file
        File file = new File(filePath);
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(file);
        }
        catch (Exception e) {
            System.err.println("Error opening file.");
        }
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
            byte[] buffer = new byte[2];
            fis.read(buffer);
            ByteBuffer bb = ByteBuffer.wrap(buffer);
            maxValue = bb.getShort();
            System.out.println(maxValue);
        }
        catch(Exception e) {
            System.err.println("Failed to get max value bytes");
        }
        try {
            byte[] buffer = new byte[2];
            fis.read(buffer);
            ByteBuffer bb = ByteBuffer.wrap(buffer);
            k = bb.getShort();
            System.out.println(k);
        }
        catch(Exception e) {
            System.err.println("Failed to get k value");
        }
        
        int m = height;
        int n = width;
        double[][] u = new double[m][k];
        double[] diag = new double[k];
        double[][] v = new double[n][k];

        try {
            //get the values of the u matrix
            for(int row = 0; row < m; ++row) {
                for(int col = 0; col < k; ++col) {
                    byte[] buffer = new byte[3];
                    fis.read(buffer);
                    u[row][col] = (double) decode(buffer);
                }
            }

            //get the eigen values for the w matrix
            for(int i = 0; i < k; ++i) {
                byte[] buffer = new byte[3];
                fis.read(buffer);
                diag[i] = (double) decode(buffer);
            }

            //get the v matrix
            for(int row = 0; row < n; ++row) {
                for(int col = 0; col < k; ++col) {
                    byte[] buffer = new byte[3];
                    fis.read(buffer);
                    v[row][col] = (double) decode(buffer);
                }
            }
        }
        catch(Exception e) {
            System.err.println("Error reading matrix values.");
        }

        SimpleMatrix U = new SimpleMatrix(u);
        SimpleMatrix W = SimpleMatrix.diag(diag);
        SimpleMatrix V = new SimpleMatrix(v);

        SimpleMatrix A = U.mult(W).mult(V.transpose());

        int[][] pgm = new int[A.numRows()][A.numCols()];
        for(int row = 0; row < A.numRows(); ++row) {
            for(int col = 0; col < A.numCols(); ++col) {
                int val = (int) Math.round(A.get(row, col));
                if(val < 0) {
                    val = 0;
                }
                pgm[row][col] = val;
            }
        }
        try {
            printPGM("image_k.pgm", pgm);
        }
        catch(Exception e) { 
            System.err.println("Failed to write k approx image.");
        }
    }

    //adopted from http://javastack.tumblr.com/post/13740168684/extracting-sign-exponent-and-mantissa-from-a
    public byte[] encode(float value) {

        BitSet byte1 = new BitSet(7);

        int fbits = Float.floatToIntBits(value);
        int fsign = fbits >>> 31;
        int fexp = (fbits >>> 23 & ((1 << 8) - 1)) - ((1 << 7) - 1);

        //get the exponent value as a short
        short sfexp = (short) fexp;
        // System.out.println(sfexp);

        //get the abs value of exponent
        //store it in 7 bits
        //subtract the number and add 1

        BigInteger bexp = new BigInteger( ((Short)sfexp).toString() );

        // System.out.println(bexp);
        BigInteger bias = new BigInteger("63");
        bexp = bexp.add(bias);
        String binExpStr = bexp.toString(2);

        BitSet expBits = new BitSet(8);

        //ensure that the binary representation needs less than 7 bits
        if(binExpStr.length() > 7) {
            System.err.println("bad things happened");
        }

        //fill in the bits into the first 7 bits
        int cnt = 0;
        for(int i = binExpStr.length() - 1; i >= 0; --i) {
            // System.out.print(binExpStr.charAt(i));

            if(binExpStr.charAt(i) == '1') {
                expBits.set(cnt);
            }
            cnt++;
        }
        // System.out.println();

        //set the 8th bit if its negative
        if(fsign == 1) {
            expBits.set(7);
        }

        // for(int i = 0; i < 8; ++i) {
        //     System.out.println("Bit" + i + ":" + expBits.get(i));
        // }

        // System.out.println();
        // System.out.println("EXP BITS: " + expBits);

        //store the mantissa
        int fmantissa = fbits & ((1 << 23) - 1);
        short smantissa = (short) (fmantissa / 256);
        // System.out.println("MANTISSA: " + fmantissa + " " + smantissa);

        // System.out.println(fsign + " " + fexp + " "  + sfexp + " " + fmantissa);
        // System.out.println(Float.intBitsToFloat((fsign << 31) | (fexp + ((1 << 7) - 1)) << 23 | fmantissa));
        // System.out.println(Float.intBitsToFloat((fsign << 31) | (fexp + ((1 << 7) - 1)) << 23 | (int)(smantissa * 256)));

        byte[] encode = new byte[3];
        for (int i=0; i<expBits.length(); i++) {
            if (expBits.get(i)) {
                encode[0] |= 1<<(i%8);
            }
        }

        ByteBuffer buffer = ByteBuffer.allocate(2);
        buffer.putShort(smantissa);
        byte[] mantissa_b = buffer.array();
        encode[1] = mantissa_b[0];
        encode[2] = mantissa_b[1];


        return encode;
    }

    public float decode(byte[] bytes) {
        // System.out.println("=====DECODE=====");
        byte[] expByte = new byte[1];
        expByte[0] = bytes[0];
        BitSet expBits = BitSet.valueOf(expByte);
        // System.out.println(expBits);

        //if the sign is negative
        int fsign = 0;
        if(expBits.get(7)) {
            fsign = 1;
        }

        //recover the exponent
        String bitStr = "";
        for(int i = 0; i < 7; ++i) {
            if(expBits.get(i)) {
                bitStr = '1' + bitStr;
            }   
            else {
                bitStr = '0' + bitStr;
            }
        }

        int fexp = Integer.parseInt(bitStr, 2);
        fexp -= 63;
        // System.out.println(fexp);

        //mantissa recovery
        byte[] sbytes = new byte[2];
        sbytes[0] = bytes[1];
        sbytes[1] = bytes[2];
        ByteBuffer bb = ByteBuffer.wrap(sbytes);
        int mantissa = (int)(bb.getShort()) * 256;

        // System.out.println(mantissa);
        float f = Float.intBitsToFloat((fsign << 31) | (fexp + ((1 << 7) - 1)) << 23 | mantissa);

        return f;
    }


    public static void main(String args[]) {
        PGMProcessor pp = new PGMProcessor();
        int[][] grid = null;
        try {
            grid = pp.readPGM(args[0]);
            pp.pgmToSVD(args[0] + "_header.txt", args[0] + ".SVD", grid);
            // byte[] fval = pp.encode2(-0.0068513555f);
            // float decode = pp.decode2(fval);
        } catch(Exception e) { e.printStackTrace(); }
    }
}
