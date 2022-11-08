public class Feed implements Comparable<Feed> {
	public String name;
	public double value;

	public void setter() {
		name = "NaN";
		value = 0;
	}

	public void Builder(double value, String name) {
		this.value = value;
		this.name = name;
	}

	@Override
	public int compareTo(Feed o) {
		String one = o.name;
		return this.name.compareTo(one);
	}
}
