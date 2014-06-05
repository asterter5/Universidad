import java.util.Scanner;

public class sumof3 {
	public static void main (String[] args) {
		int x;
		int y;
		int z;
		int sum;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa suma tres nombres enters.");
		System.out.print("Introdueix el teu primer nombre: ");
		x = sc.nextInt();
		System.out.print("Introdueix el teu segon nombre: ");
		y = sc.nextInt();
		System.out.print("Introdueix el teu tercer nombre: ");
		z = sc.nextInt();
		sum = x + y + z;
		System.out.println("La suma es: "+ sum);
	}
}

