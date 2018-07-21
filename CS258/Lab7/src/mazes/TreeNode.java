package mazes;

	public class TreeNode
	{  
		public int row, column;   
		public TreeNode north, south, east, west;
		  
		public TreeNode(int row, int column)
		{
			this.row = row;
			this.column = column;
			north = null;
			south = null;
			east = null;
			west = null;
		}
		public String toString()
		{
			return ("("+row+","+column+")\n");
		}
	}
