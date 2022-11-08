//package poo;

public class Main {
	public static void main(String[] args) {

		HomeworkReader HR = new HomeworkReader(args[0]);
		ProblemData PD = HR.readData();
		Schedulers S = new Schedulers();
		S.whichScheduler(PD, args[1]);
		S.WR.close();
	}
}
