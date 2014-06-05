import java.util.Scanner;

public class maxof3 {
	public static void main(String[] args) {
		double x, y, z, max;
		max = 0;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa calcula el maxim de tres nombres reals.");
		System.out.print("Introdueix el primer nombre: ");
		x = sc.nextDouble();
		System.out.print("Introdueix el segon nombre: ");
		y = sc.nextDouble();
		System.out.print("Introdueix el tercer nombre: ");
		z = sc.nextDouble();
		if ((x >= y) && ( x >= z)) max = x;
		else if (y >= z) max = y;
		else max = z;
		System.out.println("El numero mes gran es "+ max);
	}
}
