
package edu.ub.misionespacial;


/**
 * Mante les dades del joc. la fortalesa i l'heroi.
 * 
 * @author danieldelrio@ub.edu
 */
public class Joc {

    private Fortalesa fortalesa;
    private Actor heroi;

    
    /**
     * Constructor.
     */    
    public Joc() {        
    }
    
    public Joc(Fortalesa fortalesa, Actor heroi) {
        this.fortalesa = fortalesa;
        this.heroi = heroi;
    }
    
    public void iniciar() {
        fortalesa.setPlanta(0);
        fortalesa.setNumHabitacio(0);
                
        // inicialitzar actors
        heroi.inicialitzar();
        for (int i = 0; i < fortalesa.getNumPlantes(); i++) {
            Habitacio[] arr = fortalesa.getHabitacions(i);
            if (arr != null) {
                for (Habitacio h : arr) {
                    if (h != null) {
                        for (Actor actor : h.getActors()) {
                            actor.inicialitzar();
                        }
                    }
                }
            }
        }        
    }
            
    /**
     * Estableix la fortalesa de los Morc.
     * 
     * @param fortalesa la fortalesa
     */
    public void setFortalesa(Fortalesa fortalesa) {
        this.fortalesa = fortalesa;
    }
    
    public Fortalesa getFortalesa() {
        return fortalesa;
    }
    
    /**
     * Estableix l'heroi.
     * 
     * @param heroi
     */
    public void setHeroi(Actor heroi) {
        this.heroi = heroi;
    }
    
    public Actor getHeroi() {
        return heroi;
    }
                    
    
}
