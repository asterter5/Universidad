
package edu.ub.prog2.PrietoDehghanPourAstor.vista;
import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.Menu;
import java.io.*;
import java.util.Scanner;

/**
 * Clase que gestiona el menu del Reproductor i les seves opcions.
 * 
 * @author asterter5
 */
public class MenuReproductor {
    
    /**
     * FitxerAudio per a la gestio del menu.
     */
    private FitxerAudio f;
    /**
     * TaulaFitxers per a la gestio del menu.
     */
    private TaulaFitxers tf = new TaulaFitxers();
    
    /**
     * Llista de les opcions del menu.
     */
    static private enum OpcionsMenu {OPCIO1, OPCIO2, OPCIO3, OPCIO4, OPCIO5, SORTIR};
    
    /**
     * Descripcio de les opcions del menu.
     */
    static private String [] descOpcionsMenu = {"Afegir Fitxer: ", "Mostrar Llista: ", "Eliminar Fitxer: ", "Guardar Llista: ", "Recuperar Llista: ", "SORTIR"};
    
    /**
     * Metode que gestiona tot el menu, incloent les opcions.
     * 
     * @throws FileNotFoundException
     * @throws ClassNotFoundException
     * @throws IOException 
     */
    public void gestioReproductorUB1A() throws FileNotFoundException, ClassNotFoundException, IOException {
        Scanner sc = new Scanner(System.in);
        
        /**
         * Creem el objecte repro, i cridem el metode de gestio.
         */
        MenuReproductor repro = new MenuReproductor();
        repro.gestioMenuReproductor(sc);
    }
    
    /**
     * Metode que gestiona les opcions del reproductor.
     * 
     * @param Scanner
     * 
     * @throws FileNotFoundException
     * @throws ClassNotFoundException
     * @throws IOException 
     */
    private void gestioMenuReproductor(Scanner sc) throws FileNotFoundException, ClassNotFoundException, IOException {
        /**
         * Header del menu.
         */
        Menu<OpcionsMenu> menu = new Menu<OpcionsMenu>("Reproductor UB1 - A", OpcionsMenu.values());
        menu.setDescripcions(descOpcionsMenu);
        
        OpcionsMenu opcio = null;
        while (opcio != OpcionsMenu.SORTIR) {
            
            menu.mostrarMenu();
            opcio = menu.getOpcio(sc);
            
            switch(opcio) {
                /**
                 * Opcio per afegir fitxer.
                 */
                case OPCIO1:
                    System.out.println("Opcio 1...");
                    System.out.println("Fitxer a Afegir: ");
                    f = new FitxerAudio(sc.next());
                    f.demanaDadesTeclat();
                    tf.afegirFitxer(f);
                    break;
                
                /**
                 * Opcio per a veure la llista.
                 */
                case OPCIO2:
                    System.out.println("Opcio 2...");
                    System.out.println(tf.toString());
                    break;
                    
                /**
                 * Opcio per a eliminar un fitxer.
                 */
                case OPCIO3:
                    System.out.println("Opcio 3...");
                    System.out.println("Fitxer a Eliminar: ");
                    f = new FitxerAudio(sc.next());
                    tf.eliminarFitxer(f);
                    break;
                
                /**
                 * Opcio per a guardar la llista.
                 */
                case OPCIO4:
                    System.out.println("Opcio 4...");
                    tf.guardarLlista();
                    System.out.println("Llista guardada a 'listaReproUB1A.dat', comproba.");
                    break;
                
                /**
                 * Opcio per a carregar una llista.
                 */
                case OPCIO5:
                    System.out.println("Opcio 5...");
                    tf = tf.recuperarLlista();
                    System.out.println("Llista recuperada!");
                    break;
                    
                /**
                 * SORTIDA
                 */
                case SORTIR:
                    System.out.println("Fins Aviat!");
                    break;
                    
            }
        }
    }
}
