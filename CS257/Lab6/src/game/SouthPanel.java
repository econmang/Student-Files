/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * */
package game;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SouthPanel extends JPanel implements Constants, ActionListener
{
/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
/**
	 * 
	 */
private JLabel label;
private int level;
private int points;
private JButton plus, minus;

public SouthPanel()
{
	level = 0;
	points = 0;
	
	setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
	JButton reset = new JButton("Reset");
	reset.setForeground(Color.WHITE);
	reset.setBackground(Color.BLUE);
	reset.setToolTipText("Start the game over");
	add(reset);
	reset.addActionListener(this);
	add(Box.createHorizontalStrut(5));
	
	plus = new JButton("+");
	plus.addActionListener(this);
	plus.setForeground(Color.WHITE);
	plus.setBackground(Color.GREEN);
	plus.setToolTipText("Increase the difficulty from" + LEVELS[level]);
	add(plus);
	add(Box.createHorizontalStrut(5));
	
	minus = new JButton("-");
	minus.addActionListener(this);
	minus.setForeground(Color.WHITE);
	minus.setBackground(Color.GREEN);
	minus.setToolTipText("Decrease the difficulty from" + LEVELS[level]);
	add(minus);
	add(Box.createHorizontalStrut(5));
	
	add(Box.createHorizontalStrut(5));
	add(avatarPanel);
	
	add(Box.createHorizontalGlue());
	label = new JLabel("Points: " + points);
	label.setBackground(Color.BLUE);
	label.setOpaque(true);
	label.setForeground(Color.WHITE);
	label.setPreferredSize(new Dimension(150,30));
	label.setPreferredSize(getPreferredSize());
	label.setMinimumSize(getPreferredSize());
	label.setMaximumSize(getPreferredSize());
	add(label);
	
}

	public int getLevel()
	{
		return level;
		
				
	}
	@Override
	public void actionPerformed(ActionEvent event)
	{
		JButton button = (JButton)event.getSource();
		String text = button.getText();
		switch(text)
		{
		case "+":
			if (level < LEVELS.length-1)
	    		level++;
	        else Toolkit.getDefaultToolkit().beep();
			break;
			
		case"-":
			if(level >0)
				 level --;
			else Toolkit.getDefaultToolkit().beep();
			break;
		case"Reset":
			break;
			
		}
		plus.setToolTipText("Increase the difficulty from" + LEVELS[level]);
		minus.setToolTipText("Decrease the difficulty from" + LEVELS[level]);
		
		avatarPanel.reset();
		background.reset(level);
		points = 0;
		label.setText("Points: " + points);
		
	}
	
	
	public void adjustPoints(int points)
	{
		this.points += points;
		label.setText("Points"+this.points);
	}
}