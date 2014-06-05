
package edu.ub.prog2.PrietoDehghanPourAstor.model;

import java.io.*;
import java.util.*;

/**
 * Clase que defineix un tipus concret de LlistaFitxers.
 * @author Astor Prieto
 */
public class LlistaReproduccio extends LlistaFitxers implements Serializable{
    
    private String nom;
    private ArrayList<FitxerAudio> lRepro;
    
    /**
     * Constructor de la classe, inicialitza el ArrayList a 10 per default.
     * @param string 
     */
    public LlistaReproduccio(String string) {
        nom = string;
        lRepro = new ArrayList<>(10);
    }
    
    /**
     * Metode que retorna una LlistaReproduccio.
     * @return ArrayList<FitxerAudio>
     */
    public ArrayList getListaRepro() {
        return this.lRepro;
    }
    
    /**
     * Metode que retorna el nom de una LlistaReproduccio.
     * @return String
     */
    public String getNom() {
        return this.nom;
    }
    
    /**
     * Metode per a afegir un element a la llista de reproduccio.
     * @param f (FitxerAudio)
     */
    public void add(FitxerAudio f) {
        this.lRepro.add(f);
    }
    
    /**
     * Metode per a eliminar un element a la llista de reproduccio.
     * @param f (FitxerAudio)
     */
    public void remove(FitxerAudio f) {
        this.lRepro.remove(f);
    }
    
    /**
     * Metode per a imprimir una LlistaReproduccio.
     * @return String
     */
    public String toString() {
        String s = "";
        int i = 1;
        Iterator itrLR = lRepro.iterator();
        
        while (itrLR.hasNext()) {
            s += "["+i+"] "+ itrLR.next().toString() +"\n";
            i++;
        } 
        return s;
    }
    
}
