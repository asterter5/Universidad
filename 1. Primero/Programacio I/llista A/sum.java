import java.util.Scanner;

public class sum {
	public static void main (String[] args) {
		int x;
		int y;
		int sum;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa suma dos nombres enters.");
		System.out.print("Introdueix el teu primer nombre: ");
		x = sc.nextInt();
		System.out.print("Introdueix el teu segon nombre: ");
		y = sc.nextInt();
		sum = x + y;
		System.out.println("La suma es: "+ sum);
	}
}

