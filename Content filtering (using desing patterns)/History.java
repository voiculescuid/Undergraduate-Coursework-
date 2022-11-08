import java.util.ArrayList;
import java.util.List;

public class History {
	public List<Feed> History;
	public List<Feed> nr_of_changes;

	public History() {
		History = new ArrayList<Feed>();
		nr_of_changes = new ArrayList<Feed>();
	}

	public void updateChandes(Feed feed) {
		int ok = 0;
		for (Feed fid : nr_of_changes) {
			if (fid.name.equals(feed.name)) {
				fid.value++;
				ok = 1;
			}
		}
		if (ok == 0) {
			Feed ne = new Feed();
			ne.name = feed.name;
			ne.value = 1;
			this.nr_of_changes.add(ne);
		}
	}

	public void resetChanges(Feed feed) {
		for (Feed fid : nr_of_changes) {
			if (feed.name.equals(fid.name)) {
				this.nr_of_changes.remove(fid);
				break;
			}
		}
	}

	public int nrOfChanges(Feed feed) {
		for (Feed fid : nr_of_changes) {
			if (fid.name.equals(feed.name)) {
				return (int) fid.value;
			}
		}
		return 0;
	}

	public boolean isInHistory(Feed feed) {
		for (Feed fid : History) {
			if (fid.name.equals(feed.name))
				return true;
		}
		return false;
	}

	public Feed inHistory(Feed feed) {
		for (Feed fid : History) {
			if (fid.name.equals(feed.name))
				return fid;
		}
		return null;
	}

	public void addHistory(Feed feed) {
		int ok = 0;
		for (Feed fid : History) {
			if (fid.name.equals(feed.name)) {
				fid.value = feed.value;
				ok = 1;
			}
		}
		if (ok == 0) {
			Feed his = new Feed();
			his.name = feed.name;
			his.value = feed.value;
			History.add(his);
		}
	}

	public void actualizeOneFeed(Feed feed) {
		for (Feed fid : History) {
			if (fid.name.equals(feed.name))
				fid.value = feed.value;
		}
	}

	public double increse(Feed feed) {
		if (isInHistory(feed))
			return 100 * ((feed.value / inHistory(feed).value) - 1);
		return 0;
	}

}
