
package edu.ub.misionespacial.actors;

import edu.ub.misionespacial.Constants;
import edu.ub.misionespacial.Colisio;
import edu.ub.misionespacial.Actor;
import edu.ub.misionespacial.Context;
import edu.ub.misionespacial.Habitacio;
import edu.ub.misionespacial.Util;
import edu.ub.misionespacial.Fortalesa;

import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;

/**
 *  Forat Negre, traslada a nuestro heroi a otra habitacio
 */
public class ForatNegre extends AbstractActor {

    private Image icona;
    private boolean canviarHabitacio = false;
    
    private static final Rectangle DIMENSIONS_ICONA = new Rectangle(0, 0, 52, 52);
    
    
    public ForatNegre() {
        init();
    }
    
    public void tractarColisio(Colisio colisio) {
        Actor actor = colisio.getActor();
        if (actor instanceof Heroi) {
            canviarHabitacio = true;
        }
   }

    public Rectangle getLimits() {
        return new Rectangle(getX(), getY(), DIMENSIONS_ICONA.width, 
                DIMENSIONS_ICONA.height);
    }

    public void render(Graphics2D g) {
        g.drawImage(icona, getX(), getY(), observer);
    }

    public void actualitzar(Context context) {
        if (canviarHabitacio) {          
            ((Heroi)context.getJoc().getHeroi()).randomTeleport(context);
            canviarHabitacio = false;
        }
    }
    
    // private methods *********************************************************
    
    private void init() {
        icona = Util.carregarImatge("blackhole.png", 
                DIMENSIONS_ICONA.x, DIMENSIONS_ICONA.y, 
                DIMENSIONS_ICONA.width, DIMENSIONS_ICONA.height);        
    }
    
    private void incrementarVida(Heroi heroi, int vida) {
        heroi.setVida(heroi.getVida() + vida);
    }
        
}
