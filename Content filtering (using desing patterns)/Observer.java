import java.util.List;

public abstract class Observer {

	protected Bursa bursa;

	public abstract void update(List<Feed> feed);

}
