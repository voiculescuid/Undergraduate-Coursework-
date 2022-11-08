import java.util.Scanner;

public class Main {

	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		String ins = new String();
		int n = 0, id = 0;
		double value;
		String name, buffer;
		Bursa bursa = new Bursa();
		Factory factory = Factory.getInstance();
		ins = scanner.next();

		while (!(ins.equals("end"))) {

			if (ins.equals("begin")) {
				n = 1;
			} else if (ins.equals("create_obs")) {
				n = 2;
			} else if (ins.equals("delete_obs")) {
				n = 3;
			} else if (ins.equals("print")) {
				n = 4;
			} else if (ins.equals("feed")) {
				n = 5;
			} else
				n = 6;

			switch (n) {

			case 1:
				break;

			case 2:
				id = scanner.nextInt();
				buffer = scanner.nextLine();
				factory.createObserver(id, bursa, buffer);
				break;

			case 3:
				id = scanner.nextInt();
				bursa.remove(id);
				break;

			case 4:

				id = scanner.nextInt();
				bursa.printObs(id);
				break;

			case 5:
				Feed nou = new Feed();
				name = scanner.next();
				value = scanner.nextDouble();
				nou.Builder(value, name);
				bursa.addFeed(nou);
				break;

			default:
				System.out.println("Invalid command");
				break;
			}

			ins = scanner.next();
		}

		scanner.close();
	}

}
