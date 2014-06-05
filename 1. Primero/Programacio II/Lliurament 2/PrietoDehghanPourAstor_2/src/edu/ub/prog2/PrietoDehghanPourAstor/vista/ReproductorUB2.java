
package edu.ub.prog2.PrietoDehghanPourAstor.vista;
import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import java.io.*;
import java.util.Scanner;

/**
 * Clase Main del Reproductor UB2.
 * 
 * @author Astor Prieto
 */
public class ReproductorUB2 {
    
    public static void main(String[] args) throws ClassNotFoundException, IOException, FileNotFoundException, CloneNotSupportedException {
        // TODO code application logic here
        //Scanner sc = new Scanner(System.in);
        MenuReproductor menu = new MenuReproductor();
        menu.gestioReproductorUB();
    }
}
