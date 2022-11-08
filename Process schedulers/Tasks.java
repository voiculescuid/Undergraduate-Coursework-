//package poo;

import java.math.BigInteger;

public class Tasks {

	public int Process(String s, int n) {
		/**
		 * Ruleaza procesul corespunzator, transmis prin stringul "s".
		 */

		if (s.equals("CheckPrime")) {
			return CheckPrime(n);
		}

		if (s.equals("NextPrime")) {
			return NextPrime(n);
		}

		if (s.equals("Fibonacci")) {
			return Fibonacci(n);
		}
		if (s.equals("Sqrt")) {
			return Sqrt(n);
		}

		if (s.equals("Cube")) {
			return Cube(n);
		}

		if (s.equals("Factorial")) {
			return Factorial(n);
		}

		if (s.equals("Square")) {
			return Square(n);
		}

		return 0;
	}

	public int CheckPrime(int n) {
		/**
		 * Returneaza 1, daca numarul este prim si 0 altfel.
		 */
		int i;

		if (n <= 1)
			return 0;

		for (i = 2; i <= n / 2; i++) {
			if (n % i == 0)
				return 0;
		}

		return 1;
	}

	public int NextPrime(int n) {
		/**
		 * Returneaza urmatorul numar prim.
		 */
		int j;

		if (n <= 1)
			return 2;

		while (n != 0) {
			n = n + 1;
			j = CheckPrime(n);
			if (j == 1)
				return n;

		}
		return 1;
	}

	public int Fibonacci(int n) {
		/**
		 * Returneaza modulul celui de-al n numar din sirlul lui Fibonacci.
		 */

		int k = n;
		BigInteger ans = null;
		BigInteger modul = new BigInteger("9973");

		if (n < 0)
			return -1;
		if (k == 0) {
			ans = new BigInteger("0");
		} else if (Math.abs(k) <= 2) {
			ans = new BigInteger("1");
		} else {
			BigInteger km1 = new BigInteger("1");
			BigInteger km2 = new BigInteger("1");

			for (int i = 3; i <= Math.abs(k); ++i) {
				ans = km1.add(km2);
				km2 = km1;
				km1 = ans;
			}
		}

		ans = ans.mod(modul);
		return ans.intValue();
	}

	public int Sqrt(int n) {
		/**
		 * Returneaza radicalul modulului lui n.
		 */
		return (int) (Math.sqrt(Math.abs((double) (n))));

	}

	public int Square(int n) {
		/**
		 * Returneaza patratul lui n.
		 */
		return n * n;
	}

	public int Cube(int n) {
		/**
		 * Returneaza cubul lui n.
		 */
		return n * n * n;
	}

	public int Factorial(int n) {
		/**
		 * Returneaza factorial(n);
		 */
		if (n < 0)
			return 0;

		if (n == 0)
			return 1;

		if (n > 10000)
			return 0;

		BigInteger fact = BigInteger.ONE;
		BigInteger modul = new BigInteger("9973");

		for (int i = 2; i <= n; i++) {
			fact = fact.multiply(new BigInteger(String.valueOf(i)));
		}

		fact = fact.mod(modul);

		return fact.intValue();
	}

}
