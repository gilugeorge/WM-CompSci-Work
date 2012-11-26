package knightsTour;

public class selfTest1 {


	public static void main(String[] args) {
		
		Tour test1 = new KnightsTourP1();
		
		test1.setDimension(6);
		System.out.println("Board Size: "+test1.getDimension());
		test1.printTour(3, 3);
		
		
		Tour test2 = new KnightsTourP1();
		test2.setDimension(6);
		System.out.println("Board Size: "+test2.getDimension());
		test2.printTour(0, 0);
		
		Tour test3 = new KnightsTourP1();
		test3.setDimension(6);
		System.out.println("Board Size: "+test3.getDimension());
		test3.printTour(0, 0);
		

	}

}
