import java.io.*;
import java.util.*;

public class Revedges {
	public class Graph {

		private static final int NMAX = 100005;
		private int n;
		int num[][];
		
		@SuppressWarnings("unchecked")
		private ArrayList<Integer> adj[] = new ArrayList[NMAX];

		Graph(int n) throws IOException {
			this.n = n;
			this.visited = new boolean[n+1];
			
			for (int i = 1; i <= n; i++)
				adj[i] = new ArrayList<>();

			num = new int[n + 1][n + 1];
			for (int i = 1; i <= n; i++) {
				Arrays.fill(num[i], Integer.MAX_VALUE);
				num[i][i] = 0;
			}

		}

		public void edge(int x, int y) {
			adj[x].add(y);
			num[x][y] = 0;
		}

		public void goup(int node, int x) {
			for (int i = 1; i <= n; i++) {
				if (num[i][node] != Integer.MAX_VALUE && num[i][x] != 0) {
					num[i][x] = 0;
					goup(i, x);
				}
			}
		}

		public int BFS() {
			int s;
			boolean visited[] = new boolean[n + 1];
			LinkedList<Integer> queue = new LinkedList<Integer>();

			visited[1] = true;
			queue.add(1);

			while (queue.size() != 0) {
				s = queue.poll();
				Iterator<Integer> i = adj[s].iterator();
				while (i.hasNext()) {
					int n = i.next();
					goup(s, n);
					if (!visited[n]) {
						visited[n] = true;
						queue.add(n);
					}
				}
			}

			return 0;
		}

		boolean visited[];

		public int setnum(int x, int y, boolean[] visited) {
			int min = 1000;
			int foo = 1000;
			visited[x] = true;

			if (num[x][y] == Integer.MAX_VALUE) {
				for (int j = 1; j <= n; j++) {
					if (j == x)
						continue;
					Iterator<Integer> it = adj[j].iterator();
					while (it.hasNext()) {
						int n = it.next();
						if (n == x && !(visited[j])) {
							foo = setnum(j, y, visited) + 1;
							if (foo < min) {
								num[x][y] = foo;
								min = foo;
							}
						}
					}
				}
			}
			if(num[x][y] == Integer.MAX_VALUE)
				return 1000;
			return num[x][y];
		}


	}

	public static void main(String[] argv) throws IOException {
		int n, m, q;
		int x, y;
		Graph g;
		Revedges r = new Revedges();

		BufferedReader bufferedReader = new BufferedReader(new FileReader("revedges.in"));

		String line = bufferedReader.readLine();
		String[] split;
		split = line.split("\\s");

		n = Integer.parseInt(split[0]);
		m = Integer.parseInt(split[1]);
		q = Integer.parseInt(split[2]);
		g = r.new Graph(n);

		for (int i = 0; i < m; i++) {
			line = bufferedReader.readLine();
			split = line.split("\\s");
			x = Integer.parseInt(split[0]);
			y = Integer.parseInt(split[1]);
			g.edge(x, y);
		}
		g.BFS();
		FileWriter fw;
		BufferedWriter bw;
		fw = new FileWriter("revedges.out");
		bw = new BufferedWriter(fw);

		for (int i = 0; i < q; i++) {
			line = bufferedReader.readLine();
			split = line.split("\\s");
			x = Integer.parseInt(split[0]);
			y = Integer.parseInt(split[1]);
			Arrays.fill(g.visited, false);
			g.setnum(x, y, g.visited);
			bw.write(g.num[x][y] + "\n");
		}
		
		bw.close();
		bufferedReader.close();
	}

}

