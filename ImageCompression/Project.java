
public class Project {

    public static void main(String[] args) {     
        
        PGMProcessor proc = new PGMProcessor();
        
        if (args.length == 2 && args[0].equals("1")) {
        	String path = args[1];
        	String outPath = path + ".bin";
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
				proc.printPGM(path + ".pgm", pgm);
			} catch(Exception e) { e.printStackTrace(); }
        }
        else if (args.length == 4 && args[0].equals("3")) {
        	
        }
        else if (args.length == 2 && args[0].equals("4")) {
        	
        }
    	else {
        	System.out.println("Invalid arguments supplied");
        }
    }
}
