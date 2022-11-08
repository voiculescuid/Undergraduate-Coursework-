public class OPERANDnode extends Node implements IVisitable {
	double Value = -1, ValueCMP = -1;
	String Name = null, NameCMP = null;
	String OP = null;
	public boolean bool;

	public OPERANDnode(double Value, String OP) {
		super(null, null);
		this.OP = OP;
		this.Value = Value;
	}

	public OPERANDnode(String Name, String OP) {
		super(null, null);
		this.OP = OP;
		this.Name = Name;
	}

	public void examinateFEED(Feed feed) {
		if (Value != -1)
			ValueCMP = feed.value;
		else
			NameCMP = feed.name;

		if (OP.equals("eq"))
			eq();
		else if (OP.equals("ne"))
			ne();
		else if (OP.equals("gt"))
			gt();
		else if (OP.equals("ge"))
			ge();
		else if (OP.equals("lt"))
			lt();
		else if (OP.equals("le"))
			le();
	}

	public void eq() {
		if (Name != null && NameCMP != null) {
			bool = Name.equals(NameCMP);
		} else if (Value != -1 && ValueCMP != -1) {
			if (Value == ValueCMP) {
				bool = true;
			} else {
				bool = false;
			}
		}

	}

	public void ne() {
		if (Name != null && NameCMP != null) {
			bool = !(Name.equals(NameCMP));
		} else if (Value != -1 && ValueCMP != -1) {

			if (Value == ValueCMP)
				bool = false;
			else
				bool = true;
		}

	}

	public void gt() {
		if (ValueCMP > Value)
			bool = true;
		else
			bool = false;
	}

	public void ge() {
		if (ValueCMP >= Value)
			bool = true;
		else
			bool = false;
	}

	public void lt() {
		if (ValueCMP < Value)
			bool = true;
		else
			bool = false;
	}

	public void le() {
		if (ValueCMP <= Value)
			bool = true;
		else
			bool = false;
	}

	@Override
	public boolean accept(IVisitor visitor) {
		return visitor.visit(this);
	}
}
