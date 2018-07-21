package sort;

import javax.swing.JFrame;

public class Main
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame();
		MainPanel panel = new MainPanel();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(panel);
		frame.setVisible(true);
		frame.setSize(400,600);
		frame.setTitle("Sort Lab");
	}
}
