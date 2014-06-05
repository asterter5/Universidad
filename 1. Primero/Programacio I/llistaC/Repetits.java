import java.util.Scanner;

class Enters {
	private int x;

	public void setEnt(Scanner sc) {
		x = sc.nextInt();
	}
	public int getEnt() {
		return x;
	}
}

public class Repetits {
	public static void main(String[] args) {
		int n;
		int a = -1;
		int [] ent, rep;
		Enters tEnters = new Enters();
		Scanner sc = new Scanner(System.in);
		
		System.out.print("n = ");
		n = sc.nextInt();
		ent = new int[n];
		rep = new int[n];
		
		System.out.println("Entra els "+n+" enters.");
		for (int o = 0; o < n; o++) {
			tEnters.setEnt(sc);
			ent[o] = tEnters.getEnt();
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ent[j] == ent[i]) {
					a++;
				}
			}
			if (a>0 && i>0) {
				rep[i] = ent[i];
				ent[i] = ent[i-a];
				System.out.println(rep[i]);
			}
			a = -1;
		}
	}
}

