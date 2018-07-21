package mazes;

public class MazeTree
{
	private TreeNode root;
	private int numCols;
	private int numRows;

	public MazeTree(int[][] grid)
	{
		root = new TreeNode(0,0);
		numCols = grid[0].length;
		numRows = grid.length;
		grid[0][0] = 2; //Integer to act as a marker to show the path we took
		make(grid, root);
	}
	private void make(int[][] grid, TreeNode parent)
	{
            grid[parent.row][parent.column] = 2;
			for (int i = -1; i < 2; i++)
			{
				for(int id = -1; id < 2; id++)
				{
					int rowVal = parent.row + i;
					int colVal = parent.column + id;
					if(valid(grid, rowVal, colVal))
					{
						switch (id)
						{
							case -1:
								if(i == 0)
								{
									parent.west = new TreeNode(rowVal,colVal);
								}
								break;
							case 0:
								if(i == -1)
								{
									parent.north = new TreeNode(rowVal, colVal);
								}
								else if(i == 1)
								{
									parent.south = new TreeNode(rowVal,colVal);
								}
								break;
							case 1:
								if (i == 0)
								{
									parent.east = new TreeNode(rowVal,colVal);
								}
								break;
						}
					}
				}
			}
			for(int index = 0; index < 4; index++)
			{
				switch (index)
				{
				case 0:
					if (parent.west != null)
					{
						make(grid,parent.west);
					}
					break;
				case 1:
					if (parent.north != null)
					{
						make(grid,parent.north);
					}
					break;
				case 2:
					if (parent.south != null)
					{
						make(grid,parent.south);
					}
					break;
				case 3:
					if (parent.east != null)
					{
						make(grid,parent.east);
					}
					break;
				}
			}
		}   
	private boolean valid(int[][] grid, int row, int column)
	{
		boolean val = true;
		int numCols = grid[0].length;
		int numRows = grid.length;
		try
		{
			if ((row < 0 || row >= numRows ) || (column < 0 || column >= numCols )) {throw new IndexOutOfBoundsException();}
			if (grid[row][column] == 1)
			{
				val = true;
				return val;
			}
			else	{throw new NullPointerException();}
		}
		catch (NullPointerException npe)
		{
			val = false;
			return val;
		}
		catch (IndexOutOfBoundsException ioobe)
		{
			val = false;
			return val;
		}
	}
	private String depthFirstSearch(TreeNode thisNode)
	{
		
		String result = thisNode.toString();
		String path = "";
		
		if (thisNode.row == (numRows - 1) && thisNode.column == (numCols - 1) )
		/*(thisNode.west == null && thisNode.east == null && thisNode.south == null && thisNode.north == null && (thisNode.row != 0 && thisNode.column != 0))*/
		{
			return result;
		}
		for(int adjacentNode = 0; adjacentNode < 4; adjacentNode++)
		{
			switch (adjacentNode)
			{
				case 0: if (thisNode.west != null)
				{
					path = depthFirstSearch(thisNode.west);
					if (path != "")
					{
						return result + path;
					}
					break;
				}
				case 1: if (thisNode.east != null)
				{
					path = depthFirstSearch(thisNode.east);
					if (path != "")
					{
						return result + path;
					}
					break;
				}
				case 2: if (thisNode.north != null)
				{
					path = depthFirstSearch(thisNode.north);
					if (path != "")
					{
						return result + path;
					}
					break;
				}
				case 3: if (thisNode.south != null)
				{
					path = depthFirstSearch(thisNode.south);
					if (path != "")
					{
						return result + path;
					}
					break;
				}
			}
		}
		return path;
	}   
	public String depthFirstSearch()
	{
		TreeNode node = root;
		return depthFirstSearch(node);
	}
	
	public static void main(String[] args)
	{
		int[][] grid =  {
						{1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
						{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1},
						{0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
						{1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
						{1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
						{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
						};
		MazeTree gridMaze = new MazeTree(grid);
		if (gridMaze.depthFirstSearch().equals(""))
		{
			System.out.println("No solution was found.");
		}
		else 
		{
			System.out.println(gridMaze.depthFirstSearch());
		}
	}
}