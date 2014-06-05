import java.util.Scanner;

public class MixedUpSum {
	public static void main(String[] args) {
		int x, y, z;
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Aquest programa calcula entre tres enters si\ncualssevol de ells es una suma dels altres dos.");
		System.out.print("Introdueix els teus tres enters: ");
		x = sc.nextInt();
		y = sc.nextInt();
		z = sc.nextInt();
		
		if (x == y + z) {
			System.out.println("La igualtat: "+x+" = "+y+" + "+z);
		} if (y == x + z) {
			System.out.println("La igualtat: "+y+" = "+x+" + "+z);
		} if (z == x + y) {
			System.out.println("La igualtat: "+z+" = "+x+" + "+y);
		}
	}
}
