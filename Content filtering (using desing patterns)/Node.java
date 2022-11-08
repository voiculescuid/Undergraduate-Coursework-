public class Node implements IVisitable {
	public Node Left;
	public Node Right;

	public Node(Node left, Node right) {
		Left = left;
		Right = right;
	}

	public Node() {
		Left = null;
		Right = null;
	}

	@Override
	public boolean accept(IVisitor visitor) {
		return true;
	}

}
