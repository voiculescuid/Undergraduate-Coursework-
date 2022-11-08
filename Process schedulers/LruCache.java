//package poo;

public class LruCache extends Cache {
	int[] cacheAns;
	int[] cacheTime;
	int[] cacheNR;
	int cacheCapacity;
	ProcessStructure[] cachePS;

	public void Builder(int cacheCapacity) {
		this.cacheCapacity = cacheCapacity;
		cachePS = new ProcessStructure[cacheCapacity];
		cacheAns = new int[cacheCapacity];
		cacheTime = new int[cacheCapacity];
		cacheNR = new int[cacheCapacity];

		int i;

		for (i = 0; i < cacheCapacity; i++) {
			cacheAns[i] = -1;
			cacheTime[i] = -1;
			cachePS[i] = null;
			cacheNR[i] = 0;

		}
	}

	public void remove() {
		int i, min = cacheTime[0], pos = 0;

		for (i = 0; i < cacheCapacity; i++) {
			if (cacheTime[i] < min) {
				min = cacheTime[i];
				pos = i;
			}
		}

		cacheAns[pos] = -1;
		cacheTime[pos] = -1;
		cachePS[pos] = null;
		cacheNR[pos] = 0;

	}

	public void add(ProcessStructure PS, int rez, int NR) {
		int i, time = 1, pos = cacheCapacity + 1;

		for (i = 0; i < cacheCapacity; i++) {
			if (time < cacheTime[i])
				time = cacheTime[i];
		}

		for (i = 0; i < cacheCapacity; i++) {
			if (cacheTime[i] == -1) {
				pos = i;
				break;
			}
		}

		if (pos == cacheCapacity + 1) {
			remove();
			add(PS, rez, NR);
			return;
		}

		cacheAns[pos] = rez;
		cacheTime[pos] = time + 1;
		cachePS[pos] = PS;
		cacheNR[pos] = NR;
	}

	public int check(ProcessStructure PS, int NR) {
		int i;
		for (i = 0; i < cacheCapacity; i++) {
			if (cacheNR[i] == NR && PS.getType().equals(cachePS[i].getType())) {
				return 1;
			}

		}
		return 0;

	}

	public int getAns(ProcessStructure PS, int NR) {
		int i, time = 1;

		for (i = 0; i < cacheCapacity; i++) {
			if (time < cacheTime[i])
				time = cacheTime[i];
		}

		for (i = 0; i < cacheCapacity; i++) {
			if (cacheNR[i] == NR && PS.getType().equals(cachePS[i].getType())) {
				cacheTime[i] = time + 1;
				return cacheAns[i];
			}

		}
		return 0;
	}

}
