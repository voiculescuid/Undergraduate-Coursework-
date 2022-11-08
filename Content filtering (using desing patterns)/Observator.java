import java.util.List;

public class Observator extends Observer {

	private int ID;
	History Istoric;
	Node n;
	FilterCreator f = new FilterCreator();

	public void Build() {
		ID = 0;
	}

	public void Builder(int ID, Bursa bursa, String filtru) {
		this.bursa = bursa;
		this.bursa.attach(this);
		this.ID = ID;
		this.Istoric = new History();
		n = f.Filter(filtru);
	}

	public int getID() {
		return ID;
	}

	public void printFeed() {
		for (Feed fid : bursa.feed) {
			if (n.accept((new CalculatorVisitor(fid)))) {
				System.out.print("obs " + this.ID + ": " + fid.name + " " + String.format("%.2f", fid.value) + " "
						+ String.format("%.2f", Istoric.increse(fid)) + "% " + this.Istoric.nrOfChanges(fid) + "\n");
				Istoric.addHistory(fid);
				Istoric.resetChanges(fid);
			}
		}
	}

	public void updateCHG(Feed feed) {
		Istoric.updateChandes(feed);
	}

	@Override
	public void update(List<Feed> feed) {
		bursa.resetFeed(feed);
	}

}
