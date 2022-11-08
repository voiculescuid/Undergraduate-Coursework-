public class ANDnode extends Node implements IVisitable {
	public ANDnode(Node left, Node right) {
		super(left, right);
	}

	@Override
	public boolean accept(IVisitor visitor) {
		return visitor.visit(this);
	}
}
