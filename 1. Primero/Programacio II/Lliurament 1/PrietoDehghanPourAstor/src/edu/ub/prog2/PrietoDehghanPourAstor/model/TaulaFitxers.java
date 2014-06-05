
package edu.ub.prog2.PrietoDehghanPourAstor.model;
import java.io.*;
import java.util.Scanner;

/**
 * Clase que guarda i gestiona una taula de FitxerAudio. 
 * 
 * @author asterter5
 */
public class TaulaFitxers implements Serializable {
    
    /**
     * Variable per a guardar la taula de FitxerAudio.
     */
    private FitxerAudio[] taula;
    /**
     * Int per a guardar el index de elements de la taula.
     */
    private int numFitx;
    
    /**
     * Constructor de la clase TaulaFitxers, que crea una taula de tamany 100, i posa el index a 0.
     */
    public TaulaFitxers() {
        taula = new FitxerAudio[100];
        numFitx = 0;
    }
    
    /**
     * Metode per a retornar el nombre de elements de la taula de FitxerAudio.
     * 
     * @return int
     */
    public int tamany() {
        return numFitx;
    }
    
    /**
     * Metode per a afegir un element a la taula de FitxerAudio.
     * 
     * @param FitxerAudio 
     */
    public void afegirFitxer(FitxerAudio fitxer) {
        if (numFitx <= 100) {
            taula[numFitx] = fitxer;
            numFitx += 1;
        }
        else {
            System.out.println("Error, taula plena!");
        }
    }
    
    /**
     * Metode per a eliminar un element de la taula de FitxerAudio.
     * 
     * @param FitxerAudio 
     */
    public void eliminarFitxer(FitxerAudio fitxer) {
        int pos = 0;
        
        while (!(fitxer.equals(taula[pos]))) {
            pos += 1;
        }
        
        for (int i = pos; i <= numFitx; i++) {
            taula[i] = taula[i+1];
        }
        
        taula[numFitx] = null;
        numFitx -= 1;
    }
    
    /**
     * Metode per a trobar un element de la taula donat un index.
     * 
     * @param index
     * 
     * @return FitxerAudio[]
     */
    public FitxerAudio getAt(int position) {
        
        if (position >= 0 && position <= 100) {
            return taula[position];
        }
        return taula[position];
    }
    
    /**
     * Metode per a borrar tots els elements de la taula.
     */
    public void clear() {
        
        for (int i = 0; i <= 100; i++) {
            taula[i] = null;
        }
    }
    
    /**
     * Metode per a comprobar si la taula esta plena.
     * 
     * @return boolean
     */
    protected boolean isFull() {
        if (numFitx == taula.length) {
            return true;
        }
        return false;
    }
    
    /**
     * Metode per a guardar a un arxiu la taula de FitxerAudio.
     * 
     * @throws FileNotFoundException
     * @throws ClassNotFoundException
     * @throws IOException 
     */
    public void guardarLlista() throws FileNotFoundException, ClassNotFoundException, IOException {
        File f = new File("listaReproUB1A.dat");
        FileOutputStream fout = new FileOutputStream(f);
        try {
            
            ObjectOutputStream oos = new ObjectOutputStream(fout);
            oos.writeObject(this);
            
        } finally {
            fout.close();
        }
    }
    
    /**
     * Metode per a recuperar des de un arxiu, una taula de FitxerAudio.
     * 
     * @return TaulaFitxers
     * @throws FileNotFoundException
     * @throws ClassNotFoundException
     * @throws IOException 
     */
    public TaulaFitxers recuperarLlista() throws FileNotFoundException, ClassNotFoundException, IOException {
        File f = new File("listaReproUB1A.dat");
        FileInputStream fin = new FileInputStream(f);
        try {
            
            ObjectInputStream ois = new ObjectInputStream(fin);
            TaulaFitxers temp = (TaulaFitxers)ois.readObject();
            return temp;
            
        } finally {
            fin.close();
        }
    }
    
    /**
     * Metode per a imprimir la taula de fitxers.
     * 
     * @return String
     */
    public String toString() {
        String tbl = "";
        for (int x = 0; x < numFitx; x++) {
            tbl += ("["+ (x+1) +"] " + taula[x].toString() + "\n");
        }
        return tbl;
    }
}
