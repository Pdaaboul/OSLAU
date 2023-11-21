package Problem3;

import java.util.Scanner;

public class MyArrayThread extends Thread {
	private int[] array = new int[5];
	private ComputeAverageThread thread2;

	@Override
	public void run() {
		Scanner scanner = new Scanner(System.in);
		System.out.println("**From Thread1- Please enter 5 integers to fill the array:");
		for (int i = 0; i < array.length; i++) {
			array[i] = scanner.nextInt();
		}
		System.out.println("** From Thread1- The array elements are as follows:");
		for (int value : array) {
			System.out.print(value + " ");
		}
		System.out.println();

		thread2 = new ComputeAverageThread(array);
		System.out.println("** From Thread1- Starting Thread 2");
		thread2.start();
		try {
			thread2.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("** From Thread1- Thread 2 terminated...");
		System.out.println("** From Thread1- The average is: " + thread2.getAvg());
	}
}
