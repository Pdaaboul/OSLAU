package Problem2;

import java.util.Scanner;

public class Problem2 {
	public static void main(String[] args) throws InterruptedException {
		Scanner scanner = new Scanner(System.in);

		
		System.out.println("Please enter the first name:");
		String firstName = scanner.nextLine();
		System.out.println("Please enter the second name:");
		String secondName = scanner.nextLine();
		System.out.println("Please enter the third name:");
		String thirdName = scanner.nextLine();

		
		MyThread t1 = new MyThread(10, firstName);
		MyThread t2 = new MyThread(11, secondName);
		MyThread t3 = new MyThread(12, thirdName);

		t1.start();
		t2.start();
		t3.start();

		
		t1.join();
		t2.join();
		t3.join();

		
		System.out.println("After running all the threads:");

		
		System.out.println("The length of the first name is: " + t1.getLength());
		System.out.println("The length of the second name is: " + t2.getLength());
		System.out.println("The length of the third name is: " + t3.getLength());
	}
}
