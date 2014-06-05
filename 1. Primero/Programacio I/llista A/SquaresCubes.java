import java.util.Scanner;

public class SquaresCubes {
	public static void main(String[] args) {
		int n, i;
		Scanner sc = new Scanner(System.in);
		i = 0;
		
		System.out.print("Quin cubito vols (n | n^2 | n^3)? ");
		n = sc.nextInt();
		
		while (i < 9) {
			System.out.println(n +"\t|\t"+ (n * n) +"\t|\t"+ (n * n * n));
			i = i + 1;
		}
	}
}
