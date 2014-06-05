
package edu.ub.prog2.PrietoDehghanPourAstor.vista;

import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.*;
import java.io.*;
import java.util.*;

/**
 * Clase Main del Reproductor UB2.
 * 
 * @author Astor Prieto
 */
public class ReproductorUB3 {
    
    public static void main(String[] args) throws ClassNotFoundException, IOException, FileNotFoundException, CloneNotSupportedException, FitxerAudioErrorException {
        // TODO code application logic here
        //Scanner sc = new Scanner(System.in);
        MenuReproductor menu = new MenuReproductor();
        menu.gestioReproductorUB();
    }
}
