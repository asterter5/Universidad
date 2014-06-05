package edu.ub.misionespacial.actors;

import edu.ub.misionespacial.Constants;
import edu.ub.misionespacial.Colisio;
import edu.ub.misionespacial.Context;
import edu.ub.misionespacial.Actor;
import edu.ub.misionespacial.Habitacio;
import edu.ub.misionespacial.Util;
import edu.ub.misionespacial.actors.AbstractActor;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;

/**
 * Soldats que vigilen la fortalesa, decrementan la vida de Jack
 * 
 */
public class Soldat extends AbstractActor {

    private Image[] icones;
    private int currentIcona = 0;
    private int[] direccio = DIRECCIONS[0];
    
    private static final int DANY = 1;
    private static final int INCREMENT_POSX = 1;
    private static final int INCREMENT_POSY = 1;
    
    private int targetX =0;
    private int targetY =0;
    private boolean hasTarget=false;
    
    private boolean aturat = false;
    
    private static final int[][] DIRECCIONS = {
        { 1, 0 },   // EST
        { -1, 0 },  // OEST
        { 0, 1 },   // SUD
        { 0, -1 }   // NORD
    };
            
    private static final Rectangle DIMENSIONS_ICONA = new Rectangle(0, 0, 60, 30);
    
    public Soldat() {
        init();
    }
    
    /**
     * Sobreescriu el metode per canviar de direccio cada cop que xoca amb un
     * mur.
     * 
     * @param context
     */
    public void actualitzar(Context context) {
        
        if(isAturat()) return;
        
        Rectangle limits = new Rectangle(getX(), getY(), DIMENSIONS_ICONA.width, DIMENSIONS_ICONA.height);
        
        //establece el target si no lo tiene o lo ha alcanzado
        if(!hasTarget || hasReachedTarget(limits, targetX, targetY))
        {
            targetX = context.getJoc().getHeroi().getPosicio()[0];
            targetY = context.getJoc().getHeroi().getPosicio()[1];
            hasTarget = true;
        }
        
        int posX = getX();
        int posY = getY();
        
        //de esta manera no se quedan totalmente parados cuando no pueden avanzar en diagonal
        int aleatori = (int)(Math.random() * 2);
        
        if (aleatori == 0) {
	        if(getX() > targetX)
	            posX -= INCREMENT_POSX;
	        else if(getX() < targetX)
	            posX += INCREMENT_POSX;
	        else if(getY() > targetY)
	            posY -= INCREMENT_POSY;
	        else if(getY() < targetY)
	            posY += INCREMENT_POSY;
        } else {
	        if(getY() > targetY)
	            posY -= INCREMENT_POSY;
	        else if(getY() < targetY)
	            posY += INCREMENT_POSY;
	        else if(getX() > targetX)
	            posX -= INCREMENT_POSX;
	        else if(getX() < targetX)
	            posX += INCREMENT_POSX;
        }
        
  
        Habitacio h = context.getHabitacio();
        limits = new Rectangle(posX, posY, DIMENSIONS_ICONA.width, DIMENSIONS_ICONA.height);
        
        if (getXocaContraMurs(limits, h))
        {
            hasTarget = false;
        }
        else if (!getXocaContraMurs(limits, h)) {
            setPosicio(posX, posY);
        }
        
    }
        
    public boolean hasReachedTarget(Rectangle limits, int targetX, int targetY)
    {
        return limits.getX() <= targetX && limits.getX()+limits.width >= targetX &&
                limits.getY() <= targetY && limits.getY() + limits.height >= targetY;
    }
    
    public Rectangle getLimits() {
        return new Rectangle(getX(), getY(), DIMENSIONS_ICONA.width, 
                DIMENSIONS_ICONA.height);
    }

	public void tractarColisio(Colisio colisio) {
	    Actor actor = colisio.getActor();
	    if (actor instanceof Heroi) {
	        Heroi heroi = (Heroi)actor;
	        heroi.setVida(actor.getVida() - DANY);       
	    }
	}

    public void render(Graphics2D g) {
        g.drawImage(icones[currentIcona], getX(), getY(), observer);
    }

    // private methods *********************************************************
    
    private void init() {
    	icones = new Image [2];
    	BufferedImage iTmp = Util.carregarImatge("alien.png", 
                DIMENSIONS_ICONA.x, DIMENSIONS_ICONA.y, 
                DIMENSIONS_ICONA.width, DIMENSIONS_ICONA.height); 
    	icones[0] = Util.flipImatgeHor(iTmp);
    	icones[1] = iTmp;
        
    }
    
    private boolean getXocaContraMurs(Rectangle limits, Habitacio h) {
        boolean xoca = false;
        int[][] celes = h.getCelesIntersectades(limits);
        int i = 0;
        while (i < celes.length && !xoca) {
            if (h.getValor(celes[i][0], celes[i][1]) == Constants.SIMBOL_MUR)
                xoca = true;
            i++;
        }
        return xoca;
    }
    
    public void setAturat(boolean aturat)
    {
        this.aturat = aturat;
    }
    
    public boolean isAturat()
    {
        return this.aturat;
    }
    
}
