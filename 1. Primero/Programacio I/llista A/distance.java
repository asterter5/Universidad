import java.util.Scanner;

public class distance {
	public static void main(String[] args) {
		int x1, y1, x2, y2;
		double d;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa calcula la distancia euclidiana entre dos punts.");
		System.out.print("Introdueix un punt X del pla: ");
		x1 = sc.nextInt();
		System.out.print("Introdueix un punt Y del pla: ");
		y1 = sc.nextInt();
		System.out.print("Introdueix un segon punt X del pla: ");
		x2 = sc.nextInt();
		System.out.print("Introdueix un segon punt Y del pla: ");
		y2 = sc.nextInt();
		d = Math.sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
		System.out.println("La distancia euclidiana entre els dos punts es: "+ d);
	}
}
