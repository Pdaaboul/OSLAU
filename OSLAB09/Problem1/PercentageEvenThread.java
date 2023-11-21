package Problem1;

public class PercentageEvenThread extends Thread {
	private int count;
	private double percentage;

	public PercentageEvenThread(int count) {
		this.count = count;
	}

	public double getPercentage() {
		return percentage;
	}

	@Override
	public void run() {
		System.out.println("-3- From Thread3 - counting the percentage of even integers...");
		percentage = (double) count / 5 * 100;
		System.out.printf("-3- From Thread3 - The percentage of even integers is: %.2f%%%n", percentage);
	}
}
