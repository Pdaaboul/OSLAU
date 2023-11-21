package Problem3;

public class ComputeAverageThread extends Thread {
	private int[] myArray;
	private double avg;

	public ComputeAverageThread(int[] array) {
		this.myArray = array;
	}

	public double getAvg() {
		return avg;
	}

	@Override
	public void run() {
		System.out.println("* From Thread2 - computing the average...");
		int sum = 0;
		for (int value : myArray) {
			sum += value;
		}
		avg = sum / (double) myArray.length;
	}
}
