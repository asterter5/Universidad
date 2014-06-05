import java.util.Scanner;

public class Numbers {
	public static void main(String[] args) {
		int x, i = 0;
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Aquest programa mostra els rang des de 1 a N.");
		System.out.print("Introdueix la teva N: ");
		x = sc.nextInt();
		
		while (i < x) {
			i = i + 1;
			System.out.print(i+" ");
		} System.out.println();
	}
}
