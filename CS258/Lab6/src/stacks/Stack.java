package stacks;

public class Stack<D>
{     
  private class Node
  {   private D data;
      private Node next;
      
      public Node (D value, Node link)
      {
    	  data = value;
    	  next = link;
      }
  }
  private Node top;
 
  public Stack()
  {
	  top = null;
  }
  public void push(D value)
  {
	  Node newNode = new Node(value,top);
	  top = newNode;
  }
  public D pop () throws StackException
  { 
	  D value = look();
	  Node nNode = top;
	  top = top.next;
	  return nNode.data;
  }
  public D look() throws StackException
  { 
	  if (isEmpty()) {throw new StackException();}
	  return top.data;
  }
  public boolean isEmpty()
  {
	  return top == null;
  }
  public String toString()
  {
	  Node nNode = top;
	  String output = "";
	  while(nNode != null)
	  {
		  nNode = nNode.next;
		  output += nNode.data;
	  }
	  return output;
  }  // Print all items in the stack
}