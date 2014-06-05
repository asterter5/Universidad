
package edu.ub.prog2.PrietoDehghanPourAstor.controlador;

import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.*;
import java.io.*;
import java.util.*;

/**
 * Clase per a controlar i gestionar els metodes de DadesReproductor.
 * @author Astor Prieto
 */
public class CtrlReproductor {
    DadesReproductor dr;
    
    /**
     * Constructor dels objectes CtrlReproductor.
     */
    public CtrlReproductor() {
        dr = new DadesReproductor();
    }
    
    /**
     * Metode per a retornar el parametre dr del tipus DadesReproductor.
     * @return DadesReproductor
     */
    public DadesReproductor getDades() {
        return this.dr;
    }
    
    /**
     * Metode que clona i retorna la biblioteca musical de DadesReproductor.
     * @return LlistaFitxers
     * @throws CloneNotSupportedException 
     */
    public LlistaFitxers getBiblioteca() throws CloneNotSupportedException {
        return dr.getBiblioteca().clone();
    }
    
    /**
     * Metode per a designar un conjunt de valors al objecte DadesReproductor.
     * @param x (DadesReproductor) 
     */
    public void setBiblioteca(DadesReproductor x) {
        this.dr = x;
    }
    
    /**
     * Metode que retorna una llista de strings amb el nom de les llistes de reproduccio existents.
     * @return String[]
     */
    public String[] getLlistesReproduccio() {
        String[] ret = new String[dr.getLlistes().size()];
        ArrayList<LlistaReproduccio> tmp = dr.getLlistes();
        Iterator itList = tmp.iterator();
        int i = 0;
        while (itList.hasNext()) {
            ret[i] = ((LlistaReproduccio)itList.next()).getNom(); 
            i++;
        } return ret;
    }
    
    /**
     * Metode per a retornar una llista de reproduccio a partir del seu nom.
     * @param nomLlista (String)
     * @return LlistaReproduccio
     */
    public LlistaReproduccio getLlistaReproduccio(String nomLlista) {
        Iterator<LlistaReproduccio> i = dr.getLlistes().iterator();
        while (i.hasNext()) {
            LlistaReproduccio tmp = i.next();
            if (tmp.getNom().equals(nomLlista)) {
                return tmp;
            }
        } return null;
    }
    
    /**
     * Metode que crida a afegirFitxerBiblioteca de la clase DadesReproductor.
     * @param f (FitxerAudio)
     */
    public void afegirFitxer(FitxerAudio f) {
        dr.afegirFitxerBiblioteca(f);
    }
    
    /**
     * Metode per a afegir un FitxerAudio a una LlistaReproduccio.
     * @param f (FitxerAudio)
     * @param llista (LlistaReproduccio)
     */
    public void afegirFitxer(FitxerAudio f, LlistaReproduccio llista) {
        if (dr.getLlistes().contains(llista)) {
            llista.add(f);
        }
    }
    
    /**
     * Metode per a eliminar un fitxer de audio de la biblioteca.
     * @param f (FitxerAudio)
     */
    public void eliminarFitxer(FitxerAudio f) {
        this.getDades().eliminarFitxerBiblioteca(f);
    }
    
    /**
     * Metode per a eliminar un FitxerAudio de una LlistaReproduccio donada.
     * @param f (FitxerAudio)
     * @param llista (LlistaReproduccio)
     */
    public void eliminarFitxer(FitxerAudio f, LlistaReproduccio llista) {
        if (dr.getLlistes().contains(llista)) {
            llista.remove(f);
        }
    }
    
    /**
     * Metode per a crear una llista de reproduccio.
     * @param nomLlista (String)
     */
    public void crearLlistaReproduccio(String nomLlista) {
        LlistaReproduccio lr = new LlistaReproduccio(nomLlista);
        if (dr.getLlistes().contains(this.getLlistaReproduccio(nomLlista))) {
            System.err.println("Ya existeix aquesta llista de Reproduccio.");
        } else {
            dr.getLlistes().add(lr);
            dr.setI(dr.getI() + 1);
        }
    }
    
    /**
     * Metode per a eliminar una llista de reproduccio.
     * @param llista (LlistaReproduccio)
     */
    public void eliminarLlistaReproduccio(LlistaReproduccio llista) {
        if (dr.getLlistes().contains(llista)) {
            dr.getLlistes().remove(llista);
            dr.setI(dr.getI() - 1);
        } else {
            System.err.println("No existeix la llista de Reproduccio.");
        }
    }
    
    /**
     * Metode per a guardar a un arxiu extern la biblioteca musical.
     * @param nomFitx (String)
     * @throws IOException 
     */
    public void guardarDades(String nomFitx) throws IOException {
        try {
            dr.guardarDades(nomFitx);
        } catch (FileNotFoundException e1) {
            System.err.println("File not Found/Not valid File.");
        }
    }
    
    /**
     * Metode per a importar una biblioteca musical externa.
     * @param nomFitx (String)
     * @return DadesReproductor
     * @throws IOException
     * @throws ClassNotFoundException 
     */
    public DadesReproductor recuperarDades(String nomFitx) throws IOException, ClassNotFoundException {
        try {
            return dr.recuperarDades(nomFitx);
        } catch (FileNotFoundException e1) {
            System.err.println("File not Found/Not valid File.");
            return null;
        }
    }
    
    /**
     * Metode que crida a demanaDadesTeclat de la clase FitxerAudio.
     * @param f (FitxerAudio)
     * @param sc (Scanner)
     */
    public void demanaDadesTeclat(FitxerAudio f, Scanner sc) {
        dr.getBiblioteca().demanaDadesTeclat(f, sc);
    }
    
    /**
     * Metode per a retornar un arxiu de audio a una posicio donada de la biblioteca.
     * @param i (Integer)
     * @return FitxerAudio
     */
    public FitxerAudio retornFitxer(int i) {
        FitxerAudio f = (FitxerAudio) dr.getBiblioteca().getBiblioteca().get(i-1);
        return f;
    }
    
    public void play(FitxerAudio f) throws FitxerAudioErrorException {
        //OPCIONAL
    }
    
}
