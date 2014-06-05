import java.util.Scanner;

public class even {
	public static void main(String[] args) {
		int x;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa respon si un numero enter es parell o senar.");
		System.out.print("Introdueix el teu numero: ");
		x = sc.nextInt();
		if (x%2 == 0) System.out.println("Aquest numero es PARELL!");
		else System.out.println("Aquest numero es SENAR!");
	}
}
