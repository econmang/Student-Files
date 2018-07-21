/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * */
package game;


import java.awt.BorderLayout;

import javax.swing.JPanel;

public class MainPanel extends JPanel implements Constants
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * 
	 */

	public MainPanel()
	{
		setLayout(new BorderLayout());
		add(background, BorderLayout.CENTER);
		add(southPanel, BorderLayout.SOUTH);
	}
}

