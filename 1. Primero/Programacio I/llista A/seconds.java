import java.util.Scanner;

public class seconds {
	public static void main(String[] args) {
		long input, sec, min, hr, day;
		Scanner sc = new Scanner(System.in);
		System.out.println("Aquest programa transforma una cuantitat donada de segons a hores, minuts i segons.");
		System.out.print("Donam una quantitat de segons: ");
		input = sc.nextLong();
		day = input / 86400;
		input = input - day*86400;
		hr = input / 3600;
		input = input - hr*3600;
		min = input / 60;
		input = input - min*60;
		sec = input;
		System.out.println("La equivalencia dels teus segons son "+ day +" dies, "+ hr +" hores, "+ min +" minuts i "+ sec +" segons.");
	}
}
		
