 
package edu.ub.prog2.PrietoDehghanPourAstor.controlador;

import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.*;
import java.io.*;
import java.util.*;

/**
 * Clase que implementa els metodes per a reproduir pistes de audio.
 * @author Astor Prieto
 */
public class ReproductorAudio extends ReproductorBasic implements Serializable{
    
    private boolean rCiclic;
    private boolean rAleatori;
    private boolean endSong;
    private int index;
    private LlistaFitxers tmp;
    private boolean [] tab;
    
    /**
     * Constructor per defecte de la classe ReproductorAudio.
     */
    public ReproductorAudio() {
        rCiclic = false;
        rAleatori = false;
        endSong = false;
        index = 0;
        tmp = new LlistaFitxers();
        
    }
    
    /**
     * Setter de les opcions de reproduccio "ciclic" i "aleatori".
     * @param ciclic (boolean)
     * @param aleatori (boolean)
     */
    public void setCtrlFlags(boolean ciclic, boolean aleatori) {
        this.rCiclic = ciclic;
        this.rAleatori = aleatori;
    }
    
    /**
     * Setter del flag de reproduccio "ciclic".
     * @param ciclic (boolean)
     */
    public void setCiclic(boolean ciclic) {
        rCiclic = ciclic;
    }
    
    /**
     * Setter del flag de reproduccio "aleatori".
     * @param aleatori (boolean)
     */
    public void setAleatori(boolean aleatori) {
        rAleatori = aleatori;
    }
    
    /**
     * Getter del estat del flag de reproduccio "ciclic".
     * @return int
     */
    public int getCiclic() {
        if (rCiclic == true) {
            return 1;
        } else {
            return 0;
        }
    }
    
    /**
     * Getter del estat del flag de reproduccio "aleatori".
     * @return int
     */
    public int getAleatori() {
        if (rAleatori == true) {
            return 1;
        } else {
            return 0;
        }
    }
    
    /**
     * Metode per a reproduir un fitxer de audio.
     * @param fAudio (FitxerAudio)
     * @throws FitxerAudioErrorException 
     */
    public void playAudioFile(FitxerAudio fAudio) throws FitxerAudioErrorException {
        openAudioFile(fAudio.getPath());
        play();
        System.out.println("Reproduint >>>\n"+ fAudio.toString());
    }
    
    /**
     * Metode per a reproduir una llista de fitxers de audio.
     * @param llista (LlistaFitxers)
     * @throws FitxerAudioErrorException
     * @throws CloneNotSupportedException 
     */
    public void playFilesList(LlistaFitxers llista) throws FitxerAudioErrorException, CloneNotSupportedException {
        tmp = llista.clone();
        tab = new boolean[tmp.getBiblioteca().size()];
        this.iniciarReproduccio();
        this.playAudioFile(tmp.getElement(index));
        tab[0] = true;
        
    }
    /**
     * Metode per a reproduir una llista de reproduccio.
     * @param llista (LlistaReproduccio)
     * @throws FitxerAudioErrorException
     * @throws CloneNotSupportedException 
     */
    public void playFilesList(LlistaReproduccio llista) throws FitxerAudioErrorException, CloneNotSupportedException {
        tmp = llista.clone();
        tab = new boolean[tmp.getBiblioteca().size()];
        this.iniciarReproduccio();
        this.playAudioFile(tmp.getElement(index));
        tab[0] = true;
        
    }
    
    /**
     * Metode per a tornar a reproduir un fitxer de audio.
     * @param f (FitxerAudio)
     */
    public void resumeAudioFile() {
        play();
    }
    
    /**
     * Metode per a pausar un fitxer en reproduccio.
     * @param f (FitxerAudio)
     */
    public void pauseAudioFile() {
        pause();
    }
    
    /**
     * Metode per a parar un fitxer en reproduccio.
     * @param f (FitxerAudio)
     */
    public void stopAudioFile() {
        stop();
    }
    
    public boolean hasEnd() {
        return endSong;
    }
    
    /**
     * Sobreescritura del metode onEndFile per a que reprodueixi la pista seguent.
     * @param re (ReproductorEvent)
     */
    public void onEndFile(ReproductorEvent re) {
        super.onEndFile(re);
        try {
            seguent();
        } catch (FitxerAudioErrorException ex) {
            System.err.println("No such fitxer.");
        }
    }
    
    /**
     * Metode que crida la seguent pista per a reproduir, tenint en compte els flags de reproduccio.
     * @throws FitxerAudioErrorException 
     */
    public void seguent() throws FitxerAudioErrorException {
        
        switch (this.getCiclic()) {
            
            case 1: //TRUE
                
                if (this.tabFull()) {
                    this.iniciarReproduccio();
                    index--;
                }
                
                if (!(rAleatori)) {
                    index++;
                    if (index < tmp.getBiblioteca().size()) {
                        this.playAudioFile(tmp.getElement(index));
                        tab[index] = true;
                        System.out.print("Entra una opcio >> ");
                    }
                } else {
                    Random ran = new Random();
                    int tem = ran.nextInt((tmp.getBiblioteca().size()));
                    while (tem > (tab.length-1)) {
                        tem = ran.nextInt((tmp.getBiblioteca().size()));
                    } index = tem;
                    if (tab[index] == false) {
                        this.playAudioFile(tmp.getElement(index));
                        tab[index] = true;
                        System.out.print("Entra una opcio >> ");
                    }
                } break;
                
            case 0: //FALSE
                
                if (!(rAleatori)) {
                    index++;
                    if (index < tmp.getBiblioteca().size()) {
                        this.playAudioFile(tmp.getElement(index));
                        tab[index] = true;
                        System.out.print("Entra una opcio >> ");
                    }
                } else {
                    Random ran = new Random();
                    int tem = ran.nextInt((tmp.getBiblioteca().size()));
                    while (tem > (tab.length-1)) {
                        tem = ran.nextInt((tmp.getBiblioteca().size()));
                    } index = tem;
                    if (tab[index] == false) {
                        this.playAudioFile(tmp.getElement(index));
                        tab[index] = true;
                        System.out.print("Entra una opcio >> ");
                    }
                } break;
        }
    }
    
    /**
     * Metode que reseteja els comptadors per a tornar a començar la reproduccio.
     */
    private void iniciarReproduccio() {
        index = 0;
        for (int i = 0; i < tmp.getBiblioteca().size(); i++) {
            tab[i] = false;
        }
    }
    
    /**
     * Metode que comprova si ja han sigut reproduits tots els fitxers de la llista.
     * @return boolean
     */
    private boolean tabFull() {
        boolean vdd = true;
        for (int i = 0; i < (tab.length); i++) {
            vdd = (vdd)&&(tab[i]);
        } return vdd;
    }
    
}
