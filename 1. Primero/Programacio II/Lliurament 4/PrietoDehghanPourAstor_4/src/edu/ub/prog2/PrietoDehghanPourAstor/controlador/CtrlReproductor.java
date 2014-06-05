
package edu.ub.prog2.PrietoDehghanPourAstor.controlador;

import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.*;
import java.io.*;
import java.util.*;

/**
 * Clase per a controlar i gestionar els metodes de DadesReproductor.
 * @author Astor Prieto
 */
public class CtrlReproductor implements Serializable {
    DadesReproductor dr;
    ReproductorAudio ra;
    
    /**
     * Constructor dels objectes CtrlReproductor.
     */
    public CtrlReproductor() {
        dr = new DadesReproductor();
        ra = new ReproductorAudio();
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
        try {
            dr.afegirFitxerBiblioteca(f);
        } catch(ExcepcioFitxerRepetit ex) {
            System.err.println("\n"+ex.getMessage());
        } catch(ExcepcioFitxerNoExisteix ex) {
            System.err.println("\n"+ex.getMessage());
        }
        
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
    
    public void eliminarFitxer(int index, LlistaReproduccio llista) {
        if (dr.getLlistes().contains(llista)) {
            llista.remove(index);
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
    public void guardarDades(String nomFitxer) throws IOException {
        File f = new File(nomFitxer);
        FileOutputStream fout = new FileOutputStream(f);
        try {
            ObjectOutputStream oos = new ObjectOutputStream(fout);
            oos.writeObject(this);
        } catch (FileNotFoundException ex) {
            System.err.println("\n"+ex.getMessage());
        } finally {
            fout.close();
        }
    }
    
    /**
     * Metode per a importar una biblioteca musical externa.
     * @param nomFitx (String)
     * @return CtrlReproductor
     * @throws IOException
     */
    public CtrlReproductor recuperarDades(String nomFitxer) throws IOException {
        File f = new File(nomFitxer);
        FileInputStream fin = new FileInputStream(f);
        try {
            ObjectInputStream ois = new ObjectInputStream(fin);
            CtrlReproductor tmp = (CtrlReproductor)ois.readObject();
            return tmp;
        } catch (FileNotFoundException ex1) {
            System.err.println("\n"+ex1.getMessage());
            return null;
        } catch (ClassNotFoundException ex2) {
            System.err.println("\n"+ex2.getMessage());
            return null;
        } finally {
            fin.close();
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
        FitxerAudio f = (FitxerAudio) dr.getBiblioteca().getBiblioteca().get(i);
        return f;
    }
    
    public FitxerAudio retornFitxer(int i, LlistaReproduccio lr) {
        FitxerAudio f = (FitxerAudio) lr.getBiblioteca().get(i);
        return f;
    }
    
    /**
     * Metode per a guardar les opcions de reproduccio.
     * @param ciclic (boolean)
     * @param aleatori (boolean)
     */
    public void setCtrlRepro(boolean ciclic, boolean aleatori) {
        ra.setCtrlFlags(ciclic, aleatori);
    }
    
    /**
     * Metode per a activar la reproduccio ciclica.
     * @param ciclic (boolean)
     */
    public void setCiclic(boolean ciclic) {
        ra.setCiclic(ciclic);
    }
    
    /**
     * Metode per a activar la reproduccio aleatoria.
     * @param aleatori (boolean)
     */
    public void setAleatori(boolean aleatori) {
        ra.setAleatori(aleatori);
    }
    
    /**
     * Metode que retorna el estat del flag "ciclic".
     * @return ciclic (int)
     */
    public int getCiclic() {
        return ra.getCiclic();
    }
    
    /**
     * Metode que retorna el estat del flag "aleatori".
     * @return  aleatori (int)
     */
    public int getAleatori() {
        return ra.getAleatori();
    }
    
    /**
     * Metode que reprodueix un arxiu de audio des de un index.
     * @param pos (int)
     * @throws FitxerAudioErrorException 
     */
    public void playFitxer(int pos) throws FitxerAudioErrorException {
        ra.playAudioFile(this.retornFitxer(pos));
    }
    
    public void playFitxer(int pos, LlistaReproduccio lr) throws FitxerAudioErrorException {
        ra.playAudioFile(this.retornFitxer(pos, lr));
    }
    
    /**
     * Metode que reprodueix un fitxer de audio per parametre.
     * @param f (FitxerAudio)
     * @throws FitxerAudioErrorException 
     */
    public void playFitxer(FitxerAudio f) throws FitxerAudioErrorException {
        ra.playAudioFile(f);
    }
    
    /**
     * Metode que reprodueix la biblioteca musical sencera.
     * @throws FitxerAudioErrorException
     * @throws CloneNotSupportedException 
     */
    public void playLlista() throws FitxerAudioErrorException, CloneNotSupportedException{
        ra.playFilesList(dr.getBiblioteca());
    }
    
    /**
     * Metode que reprodueix una llista de audio passada.
     * @param llista (LlistaReproduccio)
     * @throws FitxerAudioErrorException
     * @throws CloneNotSupportedException 
     */
    public void playLlista(LlistaReproduccio llista) throws FitxerAudioErrorException, CloneNotSupportedException {
        ra.playFilesList(llista);
    }
    
    /**
     * Metode per a tornar a reproduir un fitxer.
     * @param fa (FitxerAudio)
     */
    public void resumeFitxer() {
        ra.resumeAudioFile();
    }
    
    /**
     * Metode per a pausar un fitxer de audio.
     * @param fa (FitxerAudio)
     */
    public void pauseFitxer() {
        ra.pauseAudioFile();
    }
    
    /**
     * Metode per a parar un fitxer de audio.
     * @param fa (FitxerAudio)
     */
    public void stopFitxer() {
        ra.stopAudioFile();
    }
    
    /**
     * Metode per a saltar un fitxer de audio.
     * @throws FitxerAudioErrorException 
     */
    public void nextFitxer() throws FitxerAudioErrorException {
        ra.stopAudioFile();
        ra.seguent();
    }
    
}
