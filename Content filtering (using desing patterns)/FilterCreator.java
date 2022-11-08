import java.util.Stack;
import java.util.StringTokenizer;

public class FilterCreator {

	public Node Filter(String buffer) {
		String token, bust, tip, name;
		double value;
		buffer = buffer + " end";

		StringTokenizer Tok = new StringTokenizer(buffer);
		token = Tok.nextToken();
		Stack<Node> NodeStack = new Stack<Node>();
		Stack<String> Op = new Stack<String>();
		Factory factory = Factory.getInstance();

		if (token.equals("nil")) {
			Node k = new Node();
			return k;
		}

		while (Tok.hasMoreTokens()) {

			if (token.equals("(")) {
				Node n = new Node();
				NodeStack.push(n);
			}

			if (token.equals("&&") || token.equals("||")) {
				String op = token;
				Op.push(op);
			}

			if (token.equals(")") && !(Op.isEmpty())) {

				Node n1 = NodeStack.pop();
				Node n2 = NodeStack.pop();
				Node n3;

				if ((n1 instanceof ORnode || n1 instanceof ANDnode || n1 instanceof OPERANDnode)
						&& (n2 instanceof ORnode || n2 instanceof ANDnode || n2 instanceof OPERANDnode)) {

					if (NodeStack.isEmpty() || (NodeStack.peek() instanceof ORnode
							|| NodeStack.peek() instanceof ANDnode || NodeStack.peek() instanceof OPERANDnode))
						n3 = new Node();
					else
						n3 = NodeStack.pop();

					String ANDor = Op.pop();
					if (ANDor.equals("&&"))
						n3 = factory.createANDnode(n2, n1);
					else
						n3 = factory.createORnode(n2, n1);
					NodeStack.push(n3);
				} else {
					NodeStack.push(n2);
					NodeStack.push(n1);
				}

			}

			if (!(token.equals(")")) && !(token.equals("(")) && !(token.equals("&&")) && !(token.equals("||"))) {
				Node o = NodeStack.pop();
				bust = token;
				tip = Tok.nextToken();
				if (tip.equals("name")) {
					name = Tok.nextToken();
					o = factory.createOPERANDnode(bust, name);
				} else {
					value = Double.parseDouble(Tok.nextToken());
					o = factory.createOPERANDnode(bust, value);
				}
				NodeStack.push(o);
			}

			token = Tok.nextToken();
		}
		Node root = NodeStack.pop();
		return root;
	}
}
