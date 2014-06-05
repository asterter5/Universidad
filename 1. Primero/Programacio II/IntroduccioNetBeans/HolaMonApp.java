/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package holamonapp;

import java.util.Scanner;
/**
 *
 * @author aprietde10.alumnes
 */
public class HolaMonApp {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        //Demanem les dades
        System.out.print("Introdueix el teu nom:");
        String nom = sc.nextLine();
        System.out.println("Hola, "+nom+"!");
    }
}
