
package edu.ub.prog2.PrietoDehghanPourAstor.model;

import java.util.*;
import java.io.*;

/**
 * Classe que guarda totes les dades del reproductor UB2.
 * @author Astor Prieto
 */
public class DadesReproductor implements Serializable {
    private LlistaFitxers biblioteca;
    private ArrayList<LlistaReproduccio> lRepro;
    private int i = 0;
    
    /**
     * Constructor de la clase DadesReproductor.
     * Crea una LlistaFitxers buida i un ArrayList de LlistesReproduccio.
     */
    public DadesReproductor() {
        biblioteca = new LlistaFitxers();
        lRepro = new ArrayList<>();
    }
    
    /**
     * Metode que guarda a un arxiu extern la biblioteca musical.
     * @param nomFitxer (String)
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public void guardarDades(String nomFitxer) throws FileNotFoundException, IOException {
        File f = new File(nomFitxer);
        FileOutputStream fout = new FileOutputStream(f);
        try {
            ObjectOutputStream oos = new ObjectOutputStream(fout);
            oos.writeObject(this);
        } finally {
            fout.close();
        }
    }
    
    /**
     * Metode que recupera una biblioteca musical de un arxiu extern.
     * @param nomFitxer (String)
     * @return DadesReproductor
     * @throws FileNotFoundException
     * @throws IOException
     * @throws ClassNotFoundException 
     */
    public DadesReproductor recuperarDades(String nomFitxer) throws FileNotFoundException, IOException, ClassNotFoundException {
        File f = new File(nomFitxer);
        FileInputStream fin = new FileInputStream(f);
        try {
            ObjectInputStream ois = new ObjectInputStream(fin);
            DadesReproductor tmp = (DadesReproductor)ois.readObject();
            return tmp;
        } finally {
            fin.close();
        } 
    }
    
    /**
     * Metode que crida a add(FitxerAudio f) de la clase LlistaFitxers.
     * @param f (FitxerAudio)
     */
    public void afegirFitxerBiblioteca(FitxerAudio f) {
        this.biblioteca.add(f);
    }
    
    /**
     * Metode que crida a remove(FitxerAudio f) de la clase LlistaFitxers.
     * @param f (FitxerAudio)
     */
    public void eliminarFitxerBiblioteca(FitxerAudio f) {
        this.biblioteca.remove(f);
        Iterator<LlistaReproduccio> itrL = lRepro.iterator();
        while (itrL.hasNext()) {
            (itrL.next()).remove(f);
        }
    }
    
    /**
     * Metode que crida a demanaDadesTeclat(FitxerAudio f, Scanner sc) de la classe FitxerAudio.
     * @param f (FitxerAudio)
     * @param sc (Scanner)
     */
    public void demanaDadesTeclat(FitxerAudio f, Scanner sc) {
        biblioteca.demanaDadesTeclat(f, sc);
    }
    
    /**
     * Metode intern de control del nombre de llistes de reproduccio.
     * @return Integer
     */
    public int getI() {
        return this.i;
    }
    
    /**
     * Metode intern de control del nombre de llistes de reproduccio.
     * @return Integer
     */
    public void setI(int val) {
        this.i = val;
    }
    
    /**
     * Retorna la biblioteca musical.
     * @return LlistaFitxers
     */
    public LlistaFitxers getBiblioteca() {
        return this.biblioteca;
    }
    
    /**
     * Retorna la llista de Llistes de reproduccio.
     * @return ArrayList<LlistaReproduccio>
     */
    public ArrayList<LlistaReproduccio> getLlistes() {
        return this.lRepro;
    }
    
    /**
     * Metode toString per a imprimir la biblioteca musical.
     * @return String
     */
    public String toString() {
        String tmp = "\n-- Llistes de reproduccio ---------------------------";
        tmp += lRepro.toString();
        tmp += "\n-- Biblioteca Musical --------------------------------------";
        tmp += biblioteca.toString();
        return tmp;
    }
    
}
