
package edu.ub.misionespacial;

import java.awt.Graphics2D;

/**
 * La fortalesa conte les habitacions distribuides per plantes on es succeeix l'accio,
 * tambe mante el numero de planta i habitacio actuals on es troba el
 * jugador.
 * 
 * @author danieldelrio@ub.edu
 */
public class Fortalesa implements Renderable {

    private int numPlanta;
    private int numHabitacio;
    
    private Habitacio[][] habitacions;
    
    /**
     * Numero de plantes de la fortalesa.
     */
    public static final int NUM_PLANTES = 3;
    
    /**
     * Numero d'habitacions per cada planta.
     */
    public static final int NUM_HABITACIONS_PER_PLANTA = 4;
    
    /**
     * Constructor.
     */
    public Fortalesa(int numPlantes, int numHabitacionsPerPlanta) {
        habitacions = new Habitacio[numPlantes][numHabitacionsPerPlanta];
    }

    /**
     * Incialitzacions.
     */
    public void inicialitzar() {
        numPlanta = 0;
        numHabitacio = 0;
    }
    
    /***
     * Afegeix una habitacio.
     * 
     * @param planta numero de planta
     * @param numHabitacio numero d'habitacio
     * @param habitacio habitacio
     */
    public void addHabitacio(int planta, int numHabitacio, Habitacio habitacio) {
        habitacions[planta][numHabitacio] = habitacio;
    }
        
    /**
     * Obte el numero de plantes.
     * 
     * @return el numero de plantes que te la fortalesa
     */
    public int getNumPlantes() {
        return habitacions.length;
    }
    
    /**
     * Obte el numero d'habitacions.
     * 
     * @param planta la planta
     * @return el numero d'habitacions que te la planta
     */
    public int getNumHabitacions(int planta) {
        return habitacions[planta].length;
    }
    
    /**
     * Estableix la planta actual.
     * 
     * @param planta el numero de planta
     */
    public void setPlanta(int planta) {
        this.numPlanta = planta;
    }
    
    public int getPlanta() {
        return numPlanta;
    }

    /**
     * Estableix la habitacio actual.
     * 
     * @param habitacio el numero d'habitacio
     */
    public void setNumHabitacio(int habitacio) {
        this.numHabitacio = habitacio;
    }
    
    public int getNumHabitacio() {
        return numHabitacio;
    }
    
    /**
     * Dibuixa l'habitacio actual.
     * 
     * @param g
     */
    public void render(Graphics2D g) {        
        getHabitacio().render(g);
    }    

    /**
     * Obte l'habitacio actual.
     * 
     * @return l'habitacio
     */
    public Habitacio getHabitacio() {
        return habitacions[numPlanta][numHabitacio];
    }
    
    /**
     * Obte una habitacio determinada.
     * 
     * @param numPlanta el numero de planta
     * @param numHabitacio el numero d'habitacio dins de la planta
     * 
     */
    public Habitacio getHabitacio(int numPlanta, int numHabitacio) {
        return habitacions[numPlanta][numHabitacio];
    }
    
    /**
     * Obte totes les habitacions d'una planta.
     * 
     * @param numPlanta el numero de planta
     * @return el array d'habitacions
     */
    public Habitacio[] getHabitacions(int numPlanta) {
        return habitacions[numPlanta];
    }
        
}
