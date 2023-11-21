package Problem1;

import java.util.Scanner;

public class FillArrayThread extends Thread {
	private int[] array;

	public FillArrayThread(int[] array) {
		this.array = array;
	}

	@Override
	public void run() {
		Scanner scanner = new Scanner(System.in);
		System.out.println("-1- From Thread1- Please enter 5 integers to fill the array:");
		for (int i = 0; i < array.length; i++) {
			array[i] = scanner.nextInt();
		}
		System.out.println("-1- From Thread1- The array elements are as follows:");
		for (int value : array) {
			System.out.print(value + " ");
		}
		System.out.println();
	}
}
