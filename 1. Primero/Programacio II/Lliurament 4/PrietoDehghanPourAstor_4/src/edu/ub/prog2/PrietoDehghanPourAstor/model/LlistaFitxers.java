
package edu.ub.prog2.PrietoDehghanPourAstor.model;

import edu.ub.prog2.PrietoDehghanPourAstor.controlador.*;
import java.io.*;
import java.util.*;

/**
 * Clase que defineix com es una llista de FitxerAudio
 * @author Astor Prieto
 */
public class LlistaFitxers implements Cloneable, Serializable {

    private ArrayList<FitxerAudio> lf;
    
    /**
     * Constructor de la classe, crea un ArrayList buit.
     */
    public LlistaFitxers() {
         lf = new ArrayList<>();
    }
    
    /**
     * Override del metode add de la classe ArrayList.
     * @param f (FitxerAudio)
     * @throws ExcepcioFitxerRepetit
     */
    public void add(FitxerAudio f) throws ExcepcioFitxerRepetit, ExcepcioFitxerNoExisteix {
        if (f.exists()) {
            if (this.lf.contains(f)) {
                throw new ExcepcioFitxerRepetit();
            } else {
                this.lf.add(f);
            }
        } else {
            throw new ExcepcioFitxerNoExisteix();
        }
        
    }
    
    /**
     * Override del metode remove de la clase ArrayList.
     * @param f (FitxerAudio)
     */
    public void remove(FitxerAudio f) {
        if (this.lf.contains(f)) {
            this.lf.remove(f);
        } else {
            System.err.println("No existeix la Pista.");
        }
    }
    
    /**
     * Metode que retorna la llista de arxius de audio.
     * @return ArrayList<FitxerAudio>
     */
    public ArrayList getBiblioteca() {
        return this.lf;
    }
    
    public FitxerAudio getElement(int index) {
        return lf.get(index);
    }
    
    public int size() {
        return lf.size();
    }
    
    /**
     * Metode per a introduir tota la informacio necessaria de un FitxerAudio.
     * @param f (FitxerAudio)
     * @param sc (Scanner)
     */
    public void demanaDadesTeclat(FitxerAudio f, Scanner sc) {
        FitxerAudio tmp = f;
        System.out.println("Introdueix camps (Nom de la canco):");
        tmp.setName(sc.nextLine());
        System.out.println("Introdueix camps (Nom del artista):");
        tmp.setAutor(sc.nextLine());
        System.out.println("Introdueix camps (Nom del disc):");
        tmp.setDisc(sc.nextLine());
        System.out.println("Introdueix camps (Discografica):");
        tmp.setDiscografica(sc.nextLine());
        System.out.println("Introdueix camps (Any de edicio):");
        tmp.setAny(sc.nextInt());
        System.out.println("Introdueix camps (Cancons del disc):");
        tmp.setNum(sc.nextInt());
        System.out.println("Introdueix camps (Duracio de la canco):");
        tmp.setLength(sc.nextFloat());
        
    }
    
    /**
     * Metode per a clonar un objecte, crida al de la classe ArrayList.
     * @return LlistaFitxers
     * @throws CloneNotSupportedException 
     */
    public LlistaFitxers clone() throws CloneNotSupportedException {
        return (LlistaFitxers) super.clone();
    }
    
    /**
     * Metode toString per a imprimir una llista de FitxerAudio.
     * @return String
     */
    public String toString() {
        String s = "";
        int i = 1;
        Iterator itrLF = lf.iterator();
        
        while (itrLF.hasNext()) {
            s += "["+i+"] "+ itrLF.next().toString() +"\n";
            i++;
        } 
        return s;
    }
}
