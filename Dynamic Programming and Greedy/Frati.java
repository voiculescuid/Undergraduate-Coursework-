import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Frati {
	public static void main(String[] argv) throws IOException {
		File file = new File("frati.in");
		Scanner scan = new Scanner(file);
		String text;
		Frati fr = new Frati();
		Bd in;
		scan.useDelimiter("\\Z");
		text = scan.next();
		scan.close();
		int N;
		String[] elem = text.split("\\W");
		N = Integer.parseInt(elem[0]);
		ArrayList<Bd> score = new ArrayList<Bd>();

		for (int i = 0; i < N; i++) {
			in = fr.new Bd();
			in.game = Integer.parseInt(elem[2 * i + 1]);
			in.manga = Integer.parseInt(elem[2 * i + 2]);
			score.add(in);
		}
		Collections.sort(score, new Comparator<Bd>() {
			@Override
			public int compare(Bd o1, Bd o2) {
				if (o1.game + o1.manga > o2.game + o2.manga) {
					return -1;
				}
				if (o1.game + o1.manga < o2.game + o2.manga) {
					return 1;
				} else {
					return 0;
				}
			}
		});

		Jon Jon = fr.new Jon();
		Sam Sam = fr.new Sam();

		for (int i = 0; i < N; i++) {

			if (i % 2 == 0) {
				Jon.choose(score, N - i);
			} else {
				Sam.choose(score, N - i);
			}

		}
		PrintWriter writer = new PrintWriter("frati.out", "UTF-8");
		writer.print(Jon.total + " " + Sam.total);
		writer.close();
	}

	public class Bd {
		int game;
		int manga;

		public Bd() {
			this.game = 0;
			this.manga = 0;
		}

	}

	public class Sam {
		public int total;

		public Sam() {
			this.total = 0;
		}

		public void choose(ArrayList<Bd> score, int N) {
			int sum = 0, check = 0, pos = 0, i = 0;
			sum = score.get(i).game + score.get(i).manga;
			pos = i;

			check = sum;
			while (i < N - 1) {
				i++;
				check = score.get(i).game + score.get(i).manga;
				if (check != sum) {
					break;
				}
				if (score.get(i).manga > score.get(pos).manga) {
					pos = i;
				}

			}
			this.total += score.get(pos).manga;
			score.remove(pos);
		}
	}

	public class Jon {
		public int total;

		public Jon() {
			this.total = 0;
		}

		public void choose(ArrayList<Bd> score, int N) {
			int sum = 0, check = 0, pos = 0, i = 0;
			sum = score.get(i).game + score.get(i).manga;
			pos = i;

			check = sum;
			while (i < N - 1) {
				i++;
				check = score.get(i).game + score.get(i).manga;
				if (check != sum) {
					break;
				}
				if (score.get(i).game > score.get(pos).game) {
					pos = i;
				}
			}
			this.total += score.get(pos).game;
			score.remove(pos);

		}

	}

}
