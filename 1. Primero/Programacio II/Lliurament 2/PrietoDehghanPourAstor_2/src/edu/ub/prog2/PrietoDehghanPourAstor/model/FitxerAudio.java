
package edu.ub.prog2.PrietoDehghanPourAstor.model;
import java.io.File;
import java.io.Serializable;
import java.util.Scanner;

/**
 * Clase per guardar els fitxers de audio.
 * 
 * @author Astor Prieto
 */
 
public class FitxerAudio extends File implements Serializable {
    
    /**
     * Nom de la pista.
     */
    private String songname;
    /**
     * Nom del Autor.
     */
    private String autor;
    /**
     * Nom del Disc.
     */
    private String disc;
    /**
     * Any de edicio.
     */
    private int any;
    /**
     * Numero de pista.
     */
    private int numsong;
    /**
     * Discografica.
     */
    private String discog;
    /**
     * Duracio de la pista.
     */
    private float songlen;
    
    /**
     * Constructor de la clase, crida al constructor de la superclase.
     * 
     * @param string 
     */
    public FitxerAudio(String string) {
        super(string);
    }
    
    public void setName(String name) {
        songname = name;
    }
    
    public void setAutor(String author) {
        autor = author;
    }
    
    public void setDisc(String disco) {
        disc = disco;
    }
    
    public void setAny(int ano) {
        any = ano;
    }
    
    public void setNum(int num) {
        numsong = num;
    }
    
    public void setDiscografica(String discu) {
        discog = discu;
    }
    
    public void setLength(float length) {
        songlen = length;
    }
    
    /**
     * Metode que crida al equals de la superclase per a un FitxerAudio.
     * 
     * @param FitxerAudio
     * 
     * @return boolean
     */
    public boolean equals(Object fitxerAudio) {
        return super.equals(fitxerAudio);
    }
    
    /**
     * Metode per a imprimir i mostrar un FitxerAudio.
     * 
     * @return String
     */
    public String toString() {
        String sng = "| Titol: "+ this.songname +" | Autor: "+ this.autor +" | Disc: "+ this.disc +" | Pista: "+ this.numsong +" | Dicografica: "+ this.discog +" | Duracio: "+ this.songlen +" | Any: "+ this.any +" | Fitxer: <"+ this.getPath() +"> |";
        return sng;
    }
}
