public interface IVisitor {
	public boolean visit(Node Node);

	public boolean visit(ANDnode operatorNode);

	public boolean visit(ORnode operatorNode);

	public boolean visit(OPERANDnode operatorNode);
}
