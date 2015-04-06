
public class Project {

    public static void main(String[] args) {     
        
        PGMProcessor proc = new PGMProcessor();
        
        if (args.length == 2 && args[0].equals("1")) {
        	String path = args[1];
        	String outPath = "image_b.pgm";
        	int[][] grid = null;
        	
        	try {
			grid = proc.readPGM(path);
		} catch(Exception e) { e.printStackTrace(); }
			
		try {
			proc.writeBinaryPGM(outPath, grid);
		} catch(Exception e) { e.printStackTrace(); }
        }
        else if (args.length == 2 && args[0].equals("2")) {
        	String path = args[1];
        	int[][] pgm = null;
        	
        	try {
			pgm = proc.binaryToPgm(path);
		} catch(Exception e) { e.printStackTrace(); }
			
		try {
			proc.printPGM("image2.pgm", pgm);
		} catch(Exception e) { e.printStackTrace(); }
        }
        else if (args.length == 4 && args[0].equals("3")) {
            String headerPath = args[1];
            String svdPath = args[2];
            int k = Integer.parseInt(args[3]);
            try {
                proc.svdPGMApprox(headerPath, svdPath, k);
            }
            catch(Exception e) { e.printStackTrace(); }
        }
        else if (args.length == 2 && args[0].equals("4")) {
        	String filePath = args[1];

            try {
                proc.binarySVDtoPGM(filePath);
            }
            catch(Exception e) { e.printStackTrace(); }
        }
	else if (args.length == 2 && args[0].equals("5")) {
		System.out.println("PCA stuff goes here");
	}
    	else {
        	System.out.println("Invalid arguments supplied");
        }
    }
}
