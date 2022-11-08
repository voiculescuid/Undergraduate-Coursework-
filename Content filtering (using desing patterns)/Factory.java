/**
 * Factory design pattern + Singleton design pattern
 *
 */
public class Factory {

	private static Factory factory = null;

	private Factory() {
	}

	public static Factory getInstance() {
		if (factory == null) {
			factory = new Factory();
		}
		return factory;
	}

	public void createObserver(int id, Bursa bursa, String filtru) {
		Observator l = new Observator();
		l.Builder(id, bursa, filtru);
	}

	public Node createNode() {
		Node n = new Node();
		return n;
	}

	public OPERANDnode createOPERANDnode(String op, double value) {
		OPERANDnode n = new OPERANDnode(value, op);
		return n;
	}

	public OPERANDnode createOPERANDnode(String op, String name) {
		OPERANDnode n = new OPERANDnode(name, op);
		return n;
	}

	public ORnode createORnode(Node a, Node b) {
		ORnode or = new ORnode(a, b);
		return or;
	}

	public ANDnode createANDnode(Node a, Node b) {
		ANDnode and = new ANDnode(a, b);
		return and;
	}

}
