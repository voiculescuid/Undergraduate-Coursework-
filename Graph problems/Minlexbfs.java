import java.io.*;
import java.util.*;

public class Minlexbfs {
	public class Graph {
		private static final int NMAX = 100005;
		FileWriter fw;
		BufferedWriter bw;
		int n;

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];

		Graph(int n) throws IOException {
			this.n = n;
			for (int i = 1; i <= n; i++)
				adj[i] = new ArrayList<>();

			fw = new FileWriter("minlexbfs.out");
			bw = new BufferedWriter(fw);

		}

		public void edge(int x, int y) {
			adj[x].add(y);
			adj[y].add(x);
		}

		public void sortadj() {
			for (int i = 1; i <= n; i++)
				Collections.sort(adj[i]);
		}

		void BFS() throws IOException {
			int s;
			boolean visited[] = new boolean[n + 1];
			LinkedList<Integer> queue = new LinkedList<Integer>();

			visited[1] = true;
			queue.add(1);

			while (queue.size() != 0) {
				s = queue.poll();
				bw.write(s + " ");
				Iterator<Integer> i = adj[s].iterator();
				while (i.hasNext()) {
					int n = i.next();
					if (!visited[n]) {
						visited[n] = true;
						queue.add(n);
					}
				}
			}
		}

		void closebw() throws IOException {
			bw.close();
		}
	}

	public static void main(String[] argv) throws IOException {
		Minlexbfs mbfs = new Minlexbfs();
		int n, m;
		int x, y;
		Graph g;
		BufferedReader bufferedReader = new BufferedReader(new FileReader("minlexbfs.in"));

		String line = bufferedReader.readLine();
		String[] split;
		split = line.split("\\s");

		n = Integer.parseInt(split[0]);
		m = Integer.parseInt(split[1]);
		g = mbfs.new Graph(n);

		for (int i = 0; i < m; i++) {
			line = bufferedReader.readLine();
			split = line.split("\\s");
			x = Integer.parseInt(split[0]);
			y = Integer.parseInt(split[1]);
			g.edge(x, y);
		}
		bufferedReader.close();

		g.sortadj();
		g.BFS();
		g.closebw();
	}

}

