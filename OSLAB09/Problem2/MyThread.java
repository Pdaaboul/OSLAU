package Problem2;

public class MyThread extends Thread {
	private int id;
	private String name;
	private int length;

	public MyThread(int id, String name) {
		this.id = id;
		this.name = name;
		this.length = name.length();
	}

	public int getLength() {
		return length;
	}

	@Override
	public void run() {
		System.out.println("Hello " + name + "! I am thread " + id + " counting the length of your name..");
	}
}
