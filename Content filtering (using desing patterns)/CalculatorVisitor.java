/**
 * Visitor design pattern
 *
 */
public class CalculatorVisitor implements IVisitor {

	Feed feed;

	public CalculatorVisitor(Feed feed) {
		this.feed = feed;
	}

	@Override
	public boolean visit(ANDnode operatorNode) {
		return (operatorNode.Left.accept(this) & operatorNode.Right.accept(this));
	}

	@Override
	public boolean visit(ORnode operatorNode) {
		return (operatorNode.Left.accept(this) | operatorNode.Right.accept(this));
	}

	@Override
	public boolean visit(OPERANDnode operatorNode) {
		operatorNode.examinateFEED(feed);
		return operatorNode.bool;
	}

	@Override
	public boolean visit(Node Node) {
		return true;
	}

}
