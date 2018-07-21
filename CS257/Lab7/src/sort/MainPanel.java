package sort;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.DefaultListModel;
import javax.swing.JComboBox;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

public class MainPanel extends JPanel implements ActionListener
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public MainPanel()
	{
		JList<String> lister = new JList<String>(new DefaultListModel<String>());
		JScrollPane centerPane = new JScrollPane(lister);
		JComboBox stringLength = new JComboBox();
		JComboBox dataSetSize = new JComboBox();
		JComboBox sortType = new JComboBox();
		
		JPanel main = new JPanel();
		main.setLayout(new BorderLayout());
		add(centerPane, BorderLayout.CENTER);
		
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
