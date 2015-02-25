import java.io.File;
import java.io.PrintWriter;

public class PGMPrinter {
    // Creates a PGM File based on array input 
    // @string filePath location of the file
    public void printPGM(String outputPath, int grid[][]) throws Exception {
		new File(outputPath).getParentFile().mkdirs();
		
		int maxValue = 0;
		PrintWriter writer = new PrintWriter(outputPath);
		
		writer.println("P2");
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

    public static void main(String args[]) {
        String outputPath = "pgm/test.pgm";
        
        int grid[][] = {
        		{1, 2, 3, 4, 5, 6},	
        		{1, 1, 3, 4, 5, 3},
        		{1, 2, 1, 4, 5, 7},
        		{4, 2, 3, 5, 1, 6}
        };
                
        try {
			new PGMPrinter().printPGM(outputPath, grid);
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
}
