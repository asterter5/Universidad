import java.util.Scanner;

class Pacient {
	public String nom;
	public String cognom1;
	public String cognom2;
	public float pes;
	public float altura;
}

public class ImcPacient {
	public static void main(String[] args) {
		int n;
		Scanner sc = new Scanner(System.in);
		float imc, imcMax = 0;
		Pacient p = new Pacient();
		Pacient Max = new Pacient();
		
		System.out.print("n = "); 
		n = sc.nextInt();
		
		System.out.println("Entra nom, cognom1, cognom2, pes(kg), altura(m) dels "+n+" pacients:");
		for (int i=0; i<n; i++) {
			p.nom = sc.next();
			p.cognom1 = sc.next();
			p.cognom2 = sc.next();
			p.pes = sc.nextFloat();
			p.altura = sc.nextFloat();
			
			imc = p.pes / (p.altura * p.altura);
			
			if (imc > imcMax) {
				Max.nom = p.nom;
				Max.cognom1 = p.cognom1;
				Max.cognom2 = p.cognom2;
				Max.pes = p.pes;
				Max.altura = p.altura;
				imcMax = imc;
			}
		}
		System.out.println("El pacient Maxim es: ");
		System.out.println(Max.nom+" "+Max.cognom1+" "+Max.cognom2+", "+Max.pes+"kg, "+Max.altura+"m.");
		System.out.println("Amb un IMC de: "+imcMax);
	}
}