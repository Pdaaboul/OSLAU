package Problem1;

public class Problem1 {
	public static void main(String[] args) throws InterruptedException {
		int[] array = new int[5];

		
		FillArrayThread thread1 = new FillArrayThread(array);
		System.out.println("*** From the main: Thread 1 started...");
		thread1.start();
		thread1.join();
		System.out.println("*** From the main: Thread 1 terminated...");

		
		System.out.println("*** From the main: The array elements are as follows:");
		for (int value : array) {
			System.out.print(value + " ");
		}
		System.out.println();

		
		CountEvenThread thread2 = new CountEvenThread(array);
		thread2.start();
		thread2.join();
		System.out.println("*** From the main: Thread 2 terminated...");
		System.out.println("*** From the main: The count of even integers is: " + thread2.getCount());

		
		PercentageEvenThread thread3 = new PercentageEvenThread(thread2.getCount());
		thread3.start();
		thread3.join();
		System.out.println("*** From the main: Thread 3 terminated...");
		System.out.printf("*** From the main: The percentage of even integers is: %.2f%%%n", thread3.getPercentage());
	}
}
