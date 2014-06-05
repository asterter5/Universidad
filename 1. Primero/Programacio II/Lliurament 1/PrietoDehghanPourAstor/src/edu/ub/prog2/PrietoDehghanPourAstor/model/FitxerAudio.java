
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
    private String any;
    /**
     * Numero de pista.
     */
    private String numsong;
    /**
     * Discografica.
     */
    private String discog;
    /**
     * Duracio de la pista.
     */
    private String songlen;
    
    /**
     * Constructor de la clase, crida al constructor de la superclase.
     * 
     * @param string 
     */
    public FitxerAudio(String string) {
        super(string);
    }
    
    /**
     * Metode per a introduir totes les dades de un FitxerAudio.
     * 
     * @return boolean
     */
    public boolean demanaDadesTeclat() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Introdueix camps (Nom de la canco):");
        songname = sc.nextLine();
        System.out.println("Introdueix camps (Nom del artista):");
        autor = sc.nextLine();
        System.out.println("Introdueix camps (Nom del disc):");
        disc = sc.nextLine();
        System.out.println("Introdueix camps (Any de edicio):");
        any = sc.nextLine();
        System.out.println("Introdueix camps (Cancons del disc):");
        numsong = sc.nextLine();
        System.out.println("Introdueix camps (Discografica):");
        discog = sc.nextLine();
        System.out.println("Introdueix camps (Duracio de la canco):");
        songlen = sc.nextLine();
        
        return true;
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
