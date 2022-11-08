import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Observer design pattern
 *
 */
public class Bursa {

	private List<Observator> observers = new ArrayList<Observator>();
	public List<Feed> feed = new ArrayList<Feed>();

	public List<Feed> getFeed() {
		return feed;
	}

	public void addFeed(Feed nou) {
		int ok = 0;
		for (Feed fid : feed) {
			if (fid.name.equals(nou.name)) {
				fid.value = nou.value;
				ok = 1;
			}
		}
		if (ok == 0)
			this.feed.add(nou);

		for (Observator observer : observers) {
			observer.updateCHG(nou);
		}

		Collections.sort(feed);
		notifyAllObservers();
	}

	public void resetFeed(List<Feed> one) {
		this.feed = one;
	}

	public void attach(Observator observator) {
		observers.add(observator);
	}

	public void remove(int id) {
		for (Observator observator : observers) {
			if (observator.getID() == id) {
				this.observers.remove(observator);
				break;
			}
		}
	}

	public void notifyAllObservers() {
		for (Observator observer : observers) {
			observer.update(feed);
		}
	}

	public void printFeed() {
		for (Feed fid : feed) {
			System.out.print(fid.name + " " + fid.value + "\n");
		}
	}

	public void printObs(int id) {
		for (Observator observer : observers) {
			if (observer.getID() == id)
				observer.printFeed();
		}
	}

}
