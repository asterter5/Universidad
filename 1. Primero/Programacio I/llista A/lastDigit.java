import java.util.Scanner;

public class lastDigit {
	public static void main(String[] args) {
		int x;
		int y;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa mostra a pantalla el ultim digit de un nombre.");
		System.out.print("Introdueix un nombre enter: ");
		x = sc.nextInt();
		y = x % 10;
		System.out.println("El ultim digit del teu enter es: "+ y);
	}
}
