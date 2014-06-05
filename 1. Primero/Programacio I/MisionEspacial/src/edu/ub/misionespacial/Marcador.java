
package edu.ub.misionespacial;

import java.awt.Color;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Graphics2D;
import java.awt.Rectangle;

/**
 * Representa el marcador de vida, punts i painitas encontrades (no implementat)
 * 
 * @author danieldelrio@ub.edu
 */
public class Marcador {

    private int y = 0;
    
    private Font fontNormal = new Font("Dialog", Font.PLAIN, 12);
    private Font fontPetita = new Font("Dialog", Font.BOLD, 10);
    
    public Marcador() {
        y = Constants.ALCADA_FINESTRA - 30;        
    }
   
    /**
     * Dibuixa el seu contingut.
     * 
     * @param ctx context del joc
     * @param g grafics de sortida
     */
    public void render(Context ctx, Graphics2D g) {
        pintarFons(g);
        pintarNivellVida(ctx, g);
        pintarSala(ctx, g);
    }
        
    
    // private methods *********************************************************
    
    private void pintarFons(Graphics2D g) {
        g.setPaint(new GradientPaint(
                Constants.AMPLADA_FINESTRA / 2.f, y, Color.DARK_GRAY, 
                Constants.AMPLADA_FINESTRA / 2.f, y + 40.f, Color.BLACK));
        
        Rectangle  r = new Rectangle(0, y, 
                Constants.AMPLADA_FINESTRA, Constants.ALCADA_FINESTRA - y);
        g.fill(r);        
    }

    private void pintarNivellVida(Context ctx, Graphics2D g) {
        g.setPaint(Color.white);
        g.setFont(fontNormal);
        g.drawString("Vida: ", 5, y + 15);
        
        Rectangle r = new Rectangle(40, y + 5, 100, 12);
        g.setColor(Color.BLACK);
        g.fill(r);
                
        Rectangle t = new Rectangle();
        t.setRect(r.getX(), r.getY(), ctx.getJoc().getHeroi().getVida(), (int)r.getHeight());
        
        int nivell = (int)(ctx.getJoc().getHeroi().getVida());

        g.setColor(nivell < 50 ? Color.RED : Color.BLUE);        
        g.fill(t);                   
        g.setColor(Color.white);
        g.draw(r);
        g.setFont(fontPetita);
                
        g.drawString(nivell + "%" , 60, y + 15);
    }
    
    
    private void pintarSala(Context ctx, Graphics2D g) {
        g.setColor(Color.white);
        g.setFont(fontNormal);
        int planta = ctx.getJoc().getFortalesa().getPlanta();
        int sala = ctx.getJoc().getFortalesa().getNumHabitacio();
        g.drawString("Planta: " + planta + " - Sala: " + sala, 200, y + 15);
    }
}
