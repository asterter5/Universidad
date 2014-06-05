
package edu.ub.prog2.PrietoDehghanPourAstor.vista;
import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.Menu;
import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

/**
 * Classe per al menu del reproductor B, implementada amb ArrayList.
 * 
 * @author asterter5
 */
public class MenuReproductorB implements Serializable{
    
    /**
     * FitxerAudio per a la gestio del menu.
     */
    private FitxerAudio f;
    /**
     * ArrayList per a la gestio del menu.
     */
    private ArrayList<FitxerAudio> tf = new ArrayList<>();
    
    static private enum OpcionsMenu {OPCIO1, OPCIO2, OPCIO3, OPCIO4, OPCIO5, SORTIR};
    
    static private String [] descOpcionsMenu = {"Afegir Fitxer: ", "Mostrar Llista: ", "Eliminar Fitxer: ", "Guardar Llista: ", "Recuperar Llista: ", "SORTIR"};
    
    public void gestioReproductorUB1B() throws FileNotFoundException, ClassNotFoundException, IOException {
        Scanner sc = new Scanner(System.in);
        
        MenuReproductorB repro = new MenuReproductorB();
        repro.gestioMenuReproductorB(sc);
    }
    
    /**
     * Metode intern de la clase per a guardar la llista de fitxers.
     * 
     * @param ArrayList<FitxerAudio>
     * 
     * @throws FileNotFoundException
     * @throws IOException 
     */
    private void guardarLlista(ArrayList<FitxerAudio> tf) throws FileNotFoundException, IOException {
        File f = new File("listaReproUB1B.dat");
        FileOutputStream fout = new FileOutputStream(f);
        try {
            
            ObjectOutputStream oos = new ObjectOutputStream(fout);
            oos.writeObject(tf);
            
        } finally {
            fout.close();
        }
        
    }
    
    /**
     * Metode intern de la classe per a carregar una llista de fitxers.
     * 
     * @return ArrayList<FitxerAudio>
     * 
     * @throws FileNotFoundException
     * @throws IOException
     * @throws ClassNotFoundException 
     */
    private ArrayList<FitxerAudio> recuperarLlista() throws FileNotFoundException, IOException, ClassNotFoundException {
        File f = new File("listaReproUB1B.dat");
        FileInputStream fin = new FileInputStream(f);
        try {
            
            ObjectInputStream ois = new ObjectInputStream(fin);
            ArrayList<FitxerAudio> temp = (ArrayList<FitxerAudio>)ois.readObject();
            return temp;
            
        } finally {
            fin.close();
        }
    }
    
    private void gestioMenuReproductorB(Scanner sc) throws FileNotFoundException, ClassNotFoundException, IOException {
        Menu<OpcionsMenu> menu = new Menu<OpcionsMenu>("Reproductor UB1 - B", OpcionsMenu.values());
        menu.setDescripcions(descOpcionsMenu);
        
        OpcionsMenu opcio = null;
        while (opcio != OpcionsMenu.SORTIR) {
            
            menu.mostrarMenu();
            opcio = menu.getOpcio(sc);
            
            switch(opcio) {
                case OPCIO1:
                    System.out.println("Opcio 1...");
                    System.out.println("Fitxer a Afegir: ");
                    f = new FitxerAudio(sc.next());
                    f.demanaDadesTeclat();
                    tf.add(f);
                    break;
                    
                case OPCIO2:
                    System.out.println("Opcio 2...");
                    Iterator itrTf = tf.iterator();
                    int i = 1;
                    while (itrTf.hasNext()) {
                        System.out.println("["+ i +"] "+ (itrTf.next()).toString());
                        i++;
                    }
                    break;
                    
                case OPCIO3:
                    System.out.println("Opcio 3...");
                    System.out.println("Index a Eliminar: ");
                    int f = sc.nextInt();
                    tf.remove(f);
                    break;
                    
                case OPCIO4:
                    System.out.println("Opcio 4...");
                    guardarLlista(tf);
                    System.out.println("Llista guardada a 'listaReproUB1B.dat', comproba.");
                    break;
                    
                case OPCIO5:
                    System.out.println("Opcio 5...");
                    tf = recuperarLlista();
                    System.out.println("Llista recuperada!");
                    break;
                    
                case SORTIR:
                    System.out.println("Fins Aviat!");
                    break;
                    
            }
        }
    }
}

