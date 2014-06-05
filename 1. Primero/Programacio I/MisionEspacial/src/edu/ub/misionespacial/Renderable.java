
package edu.ub.misionespacial;

import java.awt.Graphics2D;

/**
 * Tots els objectes que es puguin dibuixar (fer el render) per pantalla han
 * d'implementar aquesta interficie.
 * 
 * @author danieldelrio@ub.edu
 */
public interface Renderable {
    
    public void render(Graphics2D g);
        
}
