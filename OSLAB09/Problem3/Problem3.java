package Problem3;

public class Problem3 {
	public static void main(String[] args) {
		MyArrayThread thread1 = new MyArrayThread();
		System.out.println("*** From the main: Thread 1 started...");
		thread1.start();
		try {
			thread1.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("*** From the main: Thread 1 terminated...");
	}
}
