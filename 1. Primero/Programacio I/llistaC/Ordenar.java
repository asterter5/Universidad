import java.util.Scanner;

public class Ordenar {
	public static void main(String[] args) {
		int n = 0;
		int x;
		int y = n;
		int [] taula;
		Scanner sc = new Scanner(System.in);
		
		System.out.print("n = ");
		n = sc.nextInt();
		taula = new int[n];
		
		System.out.print("Introdueix els "+ n +" enters: ");
		for (int i = 0; i<n; i++) {
			x = sc.nextInt();
			if (x <= y) {
				y = x;
				taula[i] = y;
			} System.out.println(taula[i]);
		} 
	}
}