import java.util.Scanner;

public class NumbersInterval {
	public static void main(String[] args) {
		int x1, x2;
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Introdueix un interval per a imprimir (x1 <= x2): ");
		x1 = sc.nextInt();
		x2 = sc.nextInt();
		
		while (x1 <= x2) {
			System.out.print(x1 +" ");
			x1 = x1 + 1;
		}
		System.out.println();
	}
}
