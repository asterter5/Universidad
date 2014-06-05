import java.util.Scanner;

public class division {
	public static void main(String[] args) {
		int x, y, div, res;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa fa la divisio entera de dos nombres.");
		System.out.print("Introdueix el primer nombre: ");
		x = sc.nextInt();
		System.out.print("Introdueix el segon nombre: ");
		y = sc.nextInt();
		div = x / y;
		res = x % y;
		System.out.println("El resultat de la teva divisio entera es: "+ x +" = "+ div +" * "+ y +" + "+ res);
	}
}
