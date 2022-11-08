//package poo;

import java.util.Random;

public class Schedulers {
	String file;
	HomeworkWriter WR;

	public int whichScheduler(ProblemData PD, String file) {
		/**
		 * Apeleaza planificatorul corespunzator
		 * instructiunii oferite.
		 */
		WR = new HomeworkWriter(file);
		if (PD.getSchedulerType().equals("RandomScheduler")) {
			RandomScheduler(PD);
		}

		if (PD.getSchedulerType().equals("RoundRobinScheduler")) {
			RoundRobinScheduler(PD);
		}

		if (PD.getSchedulerType().equals("WeightedScheduler")) {
			WeightedScheduler(PD);
		}
		return 1;
	}

	public int RandomScheduler(ProblemData PD) {
		/**
		 * Selecteaza, aleator, un proces pentru rulare
		 * dintre procesele existente in sistem.
		 */
		int i, n, rez, ok;
		Tasks T = new Tasks();

		Cache C = null;
		if (PD.getCacheType().equals("LruCache")) {
			C = new LruCache();
			C.Builder(PD.getCacheCapacity());
		} else if (PD.getCacheType().equals("LfuCache")) {
			C = new LfuCache();
			C.Builder(PD.getCacheCapacity());
		}

		for (i = 0; i < PD.getNumbersToBeProcessed().length; i++) {
			Random rand = new Random();
			n = rand.nextInt(PD.getProcesses().length);
			ProcessStructure PS[] = PD.getProcesses();
			if (PD.getCacheType().equals("NoCache"))
				ok = 0;
			else
				ok = C.check(PS[n], PD.getNumbersToBeProcessed()[i]);

			if (ok == 1) {
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[n].getType() + " "
						+ C.getAns(PS[n], PD.getNumbersToBeProcessed()[i]) + " " + "FromCache");
			} else {
				rez = T.Process(PS[n].getType(), PD.getNumbersToBeProcessed()[i]);
				if (!PD.getCacheType().equals("NoCache"))
					C.add(PS[n], rez, PD.getNumbersToBeProcessed()[i]);
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[n].getType() + " " + rez + " " + "Computed");
			}

		}
		return 1;
	}

	public int RoundRobinScheduler(ProblemData PD) {
		/**
		 * Selecteaza un process astfel incat, in orice moment de timp
		 * sa existe o diferenta de maxim o unitate
		 * intre numarul de rulari ale oricaror doua procese.
		 */
		int n, i, rez, ok;
		Tasks T = new Tasks();

		Cache C = null;
		if (PD.getCacheType().equals("LruCache")) {
			C = new LruCache();
			C.Builder(PD.getCacheCapacity());
		} else if (PD.getCacheType().equals("LfuCache")) {
			C = new LfuCache();
			C.Builder(PD.getCacheCapacity());
		}

		for (i = 0; i < PD.getNumbersToBeProcessed().length; i++) {
			n = i % PD.getProcesses().length;
			ProcessStructure PS[] = PD.getProcesses();

			if (PD.getCacheType().equals("NoCache"))
				ok = 0;
			else
				ok = C.check(PS[n], PD.getNumbersToBeProcessed()[i]);
			if (ok == 1) {
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[n].getType() + " "
						+ C.getAns(PS[n], PD.getNumbersToBeProcessed()[i]) + " " + "FromCache");
			} else {
				rez = T.Process(PS[n].getType(), PD.getNumbersToBeProcessed()[i]);
				if (!PD.getCacheType().equals("NoCache"))
					C.add(PS[n], rez, PD.getNumbersToBeProcessed()[i]);
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[n].getType() + " " + rez + " " + "Computed");
			}
		}
		return 1;
	}

	public int WeightedScheduler(ProblemData PD) {
		/**
		 * Acest planificator va selecta un proces astfel incat, la momente de timp
		 * multiplu de t, unde t = suma(cote)/cmmdc(cote), sa asigure respectarea 
		 * cotelor inpuse initial de catre administrator.
		 */
		int gcd, n = 0, i, rez, first, sec, th, nr = -1, sum = PD.getProcesses()[0].getWeight(), ok;
		Tasks T = new Tasks();
		first = PD.getProcesses()[0].getWeight();
		for (i = 1; i < PD.getProcesses().length; i++) {
			sum = sum + PD.getProcesses()[i].getWeight();
			sec = PD.getProcesses()[i].getWeight();
			while (first != 0 && sec != 0) {
				th = sec;
				sec = first % sec;
				first = th;
			}
			first = first + sec;
		}
		gcd = first;

		Cache C = null;
		if (PD.getCacheType().equals("LruCache")) {
			C = new LruCache();
			C.Builder(PD.getCacheCapacity());
		} else if (PD.getCacheType().equals("LfuCache")) {
			C = new LfuCache();
			C.Builder(PD.getCacheCapacity());
		}

		for (i = 0; i < PD.getNumbersToBeProcessed().length; i++) {
			ProcessStructure PS[] = PD.getProcesses();
			if (n == 0) {
				nr++;
				nr = nr % PD.getProcesses().length;
				n = PD.getProcesses()[nr].getWeight() / gcd;
			}

			if (PD.getCacheType().equals("NoCache"))
				ok = 0;
			else
				ok = C.check(PS[nr], PD.getNumbersToBeProcessed()[i]);

			if (ok == 1) {
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[nr].getType() + " "
						+ C.getAns(PS[nr], PD.getNumbersToBeProcessed()[i]) + " " + "FromCache");
			} else {
				rez = T.Process(PS[nr].getType(), PD.getNumbersToBeProcessed()[i]);
				if (!PD.getCacheType().equals("NoCache"))
					C.add(PS[nr], rez, PD.getNumbersToBeProcessed()[i]);
				WR.println(PD.getNumbersToBeProcessed()[i] + " " + PS[nr].getType() + " " + rez + " " + "Computed");
			}
			n--;
		}

		return 0;
	}

}
