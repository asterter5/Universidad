/*
* Repetits_Control.java
*
* Autor: Astor Prieto (aprietde10)
*/

import java.util.Scanner;

class Enters { //aquesta clase implementa els setters i getters de la variable privada X
	private int x; 

	public void setEnt(Scanner sc) { //setter
		x = sc.nextInt();
	}
	public int getEnt() { //getter
		return x;
	}
}

public class Repetits_Control {
	public static void main(String[] args) {
		int n; //variable per a crear la llista de "n" elements
		int a = 1; //comptador per als int repetits
		int [] ent, rep; //listes de int i repetits
		Enters tEnters = new Enters(); //inicialitzem la taula de enters
		Scanner sc = new Scanner(System.in);
		
		System.out.print("n = ");
		n = sc.nextInt();
		ent = new int[n]; //demanem al usuari "n"
		rep = new int[n]; //i creem les taules de "n" elem.
		
		/*
		Primer elem.: o = 0;
		Seguent elem.: o++;
		Final seq.: o == n;
		*/
		System.out.println("Entra els "+n+" enters.");
		for (int o = 0; o < n; o++) { //Aquest bucle for ens permet entrar la llista de int
			tEnters.setEnt(sc); //i guardar-la en la taula de enters
			ent[o] = tEnters.getEnt();
		}
		
		/*
		Primer elem.(i): i = 0;
		Seguent elem.: i++;
			Primer elem.(j): j = 0;
			Seguent elem.: j++:
			Final seq.: j == n;
		Final seq.: i == n;
		*/
		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) { //Aquest doble bucle for ens 
							//permet iterar per a comparar els valors de la mateixa taula.
				if (((ent[j] == ent[i]) && (i != j)) && (ent[i] != -999)) {
					ent[j] = -999; // si el num de la pos. "i" i el num de la pos. "j" son iguals
					a++; //i alhora, la "i" i la "j" son diferents, sumem el contador i canviem per un 
				}            //nombre que no entra a la llista de rep.
			}
			if (a>1) { //en cas de que el comptador hagi contat mes de un num repetit, el passem a rep.
				rep[i] = ent[i]; //i imprimim el element amb el nombre de cops que apareix.
				System.out.println(rep[i]+" es repeteix, "+a+" cops.");
			} 
			a = 1;
		}
	}
}

