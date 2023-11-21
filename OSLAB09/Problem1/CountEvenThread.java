package Problem1;

public class CountEvenThread extends Thread {
	private int[] array;
	private int count;

	public CountEvenThread(int[] array) {
		this.array = array;
	}

	public int getCount() {
		return count;
	}

	@Override
	public void run() {
		System.out.println("-2- From Thread2 - counting the even integers...");
		for (int value : array) {
			if (value % 2 == 0) {
				count++;
			}
		}
		System.out.println("-2- From Thread2 - The count of even integers is: " + count);
	}
}
