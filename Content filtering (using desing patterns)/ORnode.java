public class ORnode extends Node implements IVisitable {
	public ORnode(Node left, Node right) {
		super(left, right);
	}

	@Override
	public boolean accept(IVisitor visitor) {
		return visitor.visit(this);
	}
}
