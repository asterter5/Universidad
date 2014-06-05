import java.util.Scanner;

public class age {
	public static void main(String[] args) {
		int x, y, z;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa la edat de una persona al dia 31 de Desembre de 2013.");
		System.out.print("Introdueix la teva edat: ");
		x = sc.nextInt();
		y = 2013 - x;
		z = 2013 + x;
		System.out.println("Vas neixer al any "+ y +" i al any "+ z +" tindras "+ 2*x +" anys, el doble de la teva edat.");
	}
}
