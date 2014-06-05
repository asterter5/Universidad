import java.util.Scanner;

public class digit {
	public static void main(String[] args) {
		int x;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa mostra si un numero natural es un digit o mes d'un");
		System.out.print("Introdueix aqui el teu numero: ");
		x = sc.nextInt();
		if ((x >= 0) & (x <= 9)) System.out.println("Aquest numero es UN SOL digit.");	
		else System.out.println("Aquest numero es MES DE un digit.");
	}
}
