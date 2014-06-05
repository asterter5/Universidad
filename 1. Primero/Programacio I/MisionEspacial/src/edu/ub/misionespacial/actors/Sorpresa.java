package edu.ub.misionespacial.actors;

import edu.ub.misionespacial.Actor;
import edu.ub.misionespacial.Colisio;
import edu.ub.misionespacial.Constants;
import edu.ub.misionespacial.Context;
import edu.ub.misionespacial.Util;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;

/**
 * La sorpresa dona vida a l'actor que 
 * col.lisiona amb ella, o el teleporta random.
 * 
 */
public class Sorpresa extends AbstractActor {

    private float quantitat;
    private Image image;
    private int amplada = 30;
    private int alcada = 45;
    private boolean canviarHabitacio = false;
    
    /**
     * Crea un nou objecte del tipus Sorpresa amb l'imatge del fitxer
     * <code>surprise.png</code>,  i la quantitat proporcionada.
     */
    public Sorpresa(float quantitatSorpresa) {
        this.quantitat = quantitatSorpresa;
        this.image = Util.carregarImatge("surprise.png", 
                0, 0, this.amplada, this.alcada);
        setEstat(Constants.ESTAT_ACTIU);
    }
        
    
    public float getQuantitat() {
        return quantitat;
    }
    
  
    public void setQuantitat(float quantitat) {
        this.quantitat = quantitat;
    }

    public Rectangle getLimits() {
    	// es important per tractar les colisions des de la classe Jack al metode actualizarJoc
        return new Rectangle(getX(), getY(), amplada, alcada);
    }
    
    public void tractarColisio(Colisio colisio) {
    	// a cada iteracio del joc es crida a actualizar desde la classe Jack al metode actualizarJoc
        Actor actor = colisio.getActor();
        // Cal explicar el que es instanceof
        if (actor instanceof Heroi) {
		Heroi heroi = (Heroi)actor;
		int k = (int)(Math.random() * 2);
		switch (k) {
			case 0:
				heroi.setVida(Math.min(100.0f, heroi.getVida() + quantitat));
				break;
			case 1:
				canviarHabitacio = true;
				break;
		}
		setEstat(Constants.ESTAT_INACTIU);
	}
    }
    
    public void actualitzar(Context context) {
        if (canviarHabitacio) {          
            ((Heroi)context.getJoc().getHeroi()).randomTeleport(context);
            canviarHabitacio = false;
        }
    }
    
    public void render(Graphics2D g) {
    	//Com dibuixar a la pantalla principal
        g.drawImage(image, getX(), getY(), observer);
    }
}
