//package poo;

public class ProblemData {

	private String cacheType;
	private int cacheCapacity;
	private String schedulerType;
	private ProcessStructure[] processes;
	private int[] numbersToBeProcessed;

	public ProblemData(String cacheType, int cacheCapacity, String schedulerType, ProcessStructure[] processes,
			int[] numbersToBeProcessed) {
		this.cacheType = cacheType;
		this.cacheCapacity = cacheCapacity;
		this.schedulerType = schedulerType;
		this.processes = processes;
		this.numbersToBeProcessed = numbersToBeProcessed;
	}

	/**
	 * @return the cacheType
	 */
	public String getCacheType() {
		return cacheType;
	}

	/**
	 * @return the cacheCapacity
	 */
	public int getCacheCapacity() {
		return cacheCapacity;
	}

	/**
	 * @return the schedulerType
	 */
	public String getSchedulerType() {
		return schedulerType;
	}

	/**
	 * @return the processes
	 */
	public ProcessStructure[] getProcesses() {
		return processes;
	}

	/**
	 * @return the numbersToBeProcessed
	 */
	public int[] getNumbersToBeProcessed() {
		return numbersToBeProcessed;
	}

}
