import java.util.Scanner;
import java.util.ArrayList;

public class Jugada {
	public static void main(String[] args) {
		int count = 0; //Comptador per als punts de les cartes
		int i = 0; //Iterador per a comptar les 5 cartes de la ma
		String ma; //Variable on introduim les cartes
		Scanner sc = new Scanner(System.in);
		ArrayList<String> cartas = new ArrayList<String>(); //LLista on afegim la nostra ma
		
		System.out.println("\nAquest programa calcula la puntuacio de una ma de 5 cartes.");
		System.out.println("\nEls pals: 'C' = Cors, 'D' = Diamants, 'P' = Piques, 'T' = Trebols.");
		System.out.println("Aixi sumen: 'As' = 20p, 'Rey' = 15p, 'Reina' = 10p, 'Jota' = 5p.");
		System.out.println("La resta de cartes no compten i son ignorades a la puntuacio.\n");
		System.out.print("Introdueix la teva ma de 5 cartes (separades per espais): ");
		while (i < 5) { //Mentre el iterador ho digui, seguim afegint cartes.
			ma = sc.next();
			cartas.add(ma);
			i = i + 1;
		} for (String card : cartas) { //Un for que evalua cada carta de la ma.
			String value = card.substring(1); //A partir del seu valor, ignorant el pal
			if (value.equals("A")) { //Si el valor es de 'A', 'K', 'Q' o 'J', sumem els punts
				count = count + 20;
			} if (value.equals("K")) {
				count = count + 15;
			} if (value.equals("Q")) {
				count = count + 10;
			} if (value.equals("J")) {
				count = count + 5;
			} else { //Sino, no conten res les cartes
				count = count + 0;
			} 
		} System.out.println("La teva ma es "+cartas+" amb puntuacio: "+count+"p.\n");
	}
}
