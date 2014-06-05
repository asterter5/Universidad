import java.util.Scanner;

public class Asterisks {
	public static void main(String[] args) {
		int n, i;
		String atx;
		Scanner sc = new Scanner(System.in);
		i = 0;
		atx = "";

		System.out.print("Cuants asteriscs (*) vols? ");
		n = sc.nextInt();
		
		while (i < n) {
			atx = atx + "* ";
			i = i + 1;
		} System.out.println(atx);
	}
}
