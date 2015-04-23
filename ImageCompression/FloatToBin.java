import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

/**
 * Created by chuka on 3/30/15.
 */

// NOT CLOSE TO FINISHED YET! JUST TINKERING ABOUT A MORE PRECISE CONVERSION TO
//SHORT FROM FLOAT. THIS IMPLEMENTATION WILL BE CHANGED

public class FloatToBin {

    //public byte[][] getPgmSVD(String header,String svdArray,int k)throws Exception{
    public void getPgmSVD(String header,String svdArray,int k)throws Exception{
        //byte[][] a = new byte[20][20]; // not used yet

        int[] vals = new int[3];int i = 0;

        File file = new File(header);
        header = file.getAbsolutePath();
        FileInputStream fileInputStream = new FileInputStream(header);
        Scanner scan = new Scanner(fileInputStream);

        //Get dimensions of array
        while(scan.hasNext()){
            vals[i] = scan.nextInt();
            i++;
        }
        int row = vals[0], column = vals[1];

        //create an array of short type
        short[][] U = new short[row][row];
        short[][] E = new short[row][column];
        short[][] V = new short[column][column];

        file = new File(svdArray);
        svdArray = file.getAbsolutePath();
        fileInputStream = new FileInputStream(svdArray);
        scan = new Scanner(fileInputStream);

        while(scan.hasNext()){

            for(i = 0; i < row; i++){
                for(int j = 0; j < row; j++){
                    float hold = scan.nextFloat() * 10000; //Multiplied by 10,000
                    U[i][j] = (short) hold;
                }

            }

            for(i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    float hold = scan.nextFloat() * 10000; //Multiplied by 10,000
                    E[i][j] = (short) hold;
                }

            }

            for(i = 0; i < column; i++){
                for(int j = 0; j < column; j++){
                    float hold = scan.nextFloat() * 10000; //Multiplied by 10,000
                    V[i][j] = (short) hold;
                    System.out.println("\n===============================\n");
                    System.out.print("Short val: " + V[i][j] + " ");
                    System.out.print("Float val:" + hold + "\n");
                }
                System.out.println();

            }

        }

        //testing...

        for(i = 0; i < column; i++){
            for(int j = 0; j < column; j++){

                System.out.print(((float)V[i][j]/10000)+" ");
            }
            System.out.println();
        }

        //STILL TO COME:
        // (1.) I WILL CHANGE IMPLEMENTATION OF CONVERTING FLOAT TO SHORT
        // (2.) I WILL REMOVE ROWS AND/OR COLUMNS I CAN DISCARD DEPENDING ON VALUE OF K
        // (3.) I WILL COPY INTO THREE NEW ARRAYS CALLED U',E',V' AND WRITE TO FILE


        //return a;
    }
}
