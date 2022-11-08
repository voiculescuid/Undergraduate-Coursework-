import java.io.*;
import java.util.*;

public class Disjcnt {

	public class Edge {
		int x;
		int y;

		Edge(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}

	public class Graph {
		private static final int NMAX = 100005;
		int n;
		boolean visited[];

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];

		Graph(int n) throws IOException {
			this.n = n;
			for (int i = 1; i <= n; i++)
				adj[i] = new ArrayList<>();

			visited = new boolean[n + 1];
		}

		public void edge(int x, int y) {
			adj[x].add(y);
			adj[y].add(x);
		}

		
		private int depth[];
		private int low[];
		private void DFSTarjan(int x, int f, ArrayList<Edge> sol) {
			depth[x] = depth[f] + 1;
			low[x] = depth[x];
			for (int y : adj[x]) {
				if (y == f)
					continue;
				if (depth[y] == 0) {
					DFSTarjan(y, x, sol);
					if (low[y] > depth[x]) {
						sol.add(new Edge(x, y));
					}
					low[x] = Math.min(low[x], low[y]);
				} else {
					low[x] = Math.min(low[x], depth[y]);
				}
			}
		}

		private ArrayList<Edge> Tarjan() {
			ArrayList<Edge> sol = new ArrayList<>();
			depth = new int[n + 1];
			low = new int[n + 1];
			for (int i = 0; i <= n; i++)
				depth[i] = 0;
			for (int i = 1; i <= n; i++) {
				if (depth[i] != 0)
					continue;
				DFSTarjan(i, 0, sol);
			}
			return sol;
		}

		int DFS(int v, boolean visited[]) {
			int count = 0;
			visited[v] = true;
			count++;
			
			Iterator<Integer> i = adj[v].iterator();
			while (i.hasNext()) {
				int n = i.next();
				if (!visited[n])
					count += DFS(n, visited);
			}
			return count;
		}

		void deletEdge(ArrayList<Edge> edd) {
			for (Edge e : edd) {
				Iterator<Integer> i = adj[e.x].iterator();
				while (i.hasNext()) {
					int del = i.next();
					if (del == e.y) {
						i.remove();
						break;
					}
				}

				i = adj[e.y].iterator();
				while (i.hasNext()) {
					int del = i.next();
					if (del == e.x) {
						i.remove();
						break;
					}
				}
			}
		}
		
	}

	public static void main(String[] argv) throws IOException {
		int n, m;
		int x, y;
		Graph g;
		Disjcnt d = new Disjcnt();
		BufferedReader bufferedReader = new BufferedReader(new FileReader("disjcnt.in"));

		String line = bufferedReader.readLine();
		String[] split;
		split = line.split("\\s");

		n = Integer.parseInt(split[0]);
		m = Integer.parseInt(split[1]);
		g = d.new Graph(n);

		for (int i = 0; i < m; i++) {
			line = bufferedReader.readLine();
			split = line.split("\\s");
			x = Integer.parseInt(split[0]);
			y = Integer.parseInt(split[1]);
			g.edge(x, y);
		}
		bufferedReader.close();

		ArrayList<Edge> edd = g.Tarjan();
		g.deletEdge(edd);

		int ok;
		long count = 0;
		for (int i = 1; i <= n; i++) {
			ok = g.DFS(i, g.visited);
			count += (1l * ok * (ok - 1)) / 2;
		}

		FileWriter fw;
		BufferedWriter bw;
		fw = new FileWriter("disjcnt.out");
		bw = new BufferedWriter(fw);
		bw.write(count + " ");
		bw.close();
	}
}

