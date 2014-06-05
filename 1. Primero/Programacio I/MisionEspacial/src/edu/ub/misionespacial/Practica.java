package edu.ub.misionespacial;

import edu.ub.misionespacial.actors.ForatNegre;
import edu.ub.misionespacial.actors.Heroi;
import edu.ub.misionespacial.actors.Oxigen;
import edu.ub.misionespacial.actors.Arma;
import edu.ub.misionespacial.actors.Sorpresa;
import edu.ub.misionespacial.actors.Soldat;

/**
 * Demo.
 * 
 */
public class Practica {

    private Joc joc;
    private Fortalesa fortalesa;
    private Heroi heroi;

    private static final int MAX_OXIGEN_PER_HABITACIO = 3;
    private static final int MAX_SOLDATS_PER_HABITACIO = 2;
    private static final int MAX_FORATS_PER_HABITACIO = 1;
    
    private Practica() {
        
        fortalesa = new Fortalesa(3, 3);
        fortalesa.addHabitacio(0, 0, crearHabitacio0Planta0());
        fortalesa.addHabitacio(0, 1, crearHabitacio1Planta0());
        fortalesa.addHabitacio(0, 2, crearHabitacio2Planta0());  
	fortalesa.addHabitacio(1, 0, crearHabitacio0Planta1());  
	fortalesa.addHabitacio(1, 1, crearHabitacio1Planta1());                            
        fortalesa.addHabitacio(1, 2, crearHabitacio2Planta1());  
	fortalesa.addHabitacio(2, 0, crearHabitacio0Planta2());  
	fortalesa.addHabitacio(2, 1, crearHabitacio1Planta2());  
	fortalesa.addHabitacio(2, 2, crearHabitacio2Planta2());
	
        heroi = new Heroi();
        Habitacio h = fortalesa.getHabitacio(0, 0);
        int[] p = h.getPosicioCela(10, 10);
        heroi.setPosicioInicial(p[0], p[1]);

        distribuirOxigen();
	distribuirArma();
	distribuirSorpresa();
        distribuirSoldats();
        distribuirForatsNegres();
               
        //initialitzacio del joc
        joc = new Joc(fortalesa, heroi);
        Jack jda = new Jack(joc);      
    }
    
        
    private Habitacio crearHabitacio0Planta0() {
        Habitacio h = Util.carregarHabitacio("h0_0.txt");
        
        Porta porta = h.getPorta(14, 24);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(1);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(1, 1));

        porta = h.getPorta(0, 10);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(2);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(14, 10));        
        
        return h;
    }
   
    private Habitacio crearHabitacio1Planta0() {
        Habitacio h = Util.carregarHabitacio("h0_1.txt");

        Porta porta = h.getPorta(1, 0);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(13, 22));
       
	porta = h.getPorta(0, 6);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(14, 15));

        return h;
    }

    private Habitacio crearHabitacio2Planta0() {
        Habitacio h = Util.carregarHabitacio("h0_2.txt");

        Porta porta = h.getPorta(16, 10);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(1, 10));
        
        return h;
    }

    private Habitacio crearHabitacio0Planta1() {
        Habitacio h = Util.carregarHabitacio("h1_0.txt");

        Porta porta = h.getPorta(9, 0);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(1);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(8, 23));
        
	porta = h.getPorta(3, 24);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(2);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(5, 1));

	porta = h.getPorta(16, 15);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(1);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(1, 6));

        return h;
    }

    private Habitacio crearHabitacio1Planta1() {
        Habitacio h = Util.carregarHabitacio("h1_1.txt");

        Porta porta = h.getPorta(8, 24);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(9, 2));
        
        return h;
    }

    private Habitacio crearHabitacio2Planta1() {
        Habitacio h = Util.carregarHabitacio("h1_2.txt");

        Porta porta = h.getPorta(0, 20);
        porta.setNumPlantaDesti(2);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(14, 10));

	porta = h.getPorta(5, 0);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(3, 23));
        
        return h;
    }

    private Habitacio crearHabitacio0Planta2() {
        Habitacio h = Util.carregarHabitacio("h2_0.txt");

        Porta porta = h.getPorta(0, 21);
        porta.setNumPlantaDesti(2);
        porta.setNumHabitacioDesti(1);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(14, 11));
        
	porta = h.getPorta(16, 10);
        porta.setNumPlantaDesti(1);
        porta.setNumHabitacioDesti(2);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(1, 21));

        return h;
    }

    private Habitacio crearHabitacio1Planta2() {
        Habitacio h = Util.carregarHabitacio("h2_1.txt");

        Porta porta = h.getPorta(0, 12);
        porta.setNumPlantaDesti(2);
        porta.setNumHabitacioDesti(2);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(14, 11));
        
        return h;
    }

    private Habitacio crearHabitacio2Planta2() {
        Habitacio h = Util.carregarHabitacio("h2_2.txt");

        Porta porta = h.getPorta(16, 12);
        porta.setNumPlantaDesti(0);
        porta.setNumHabitacioDesti(0);
        porta.setPosicioHabitacioDesti(h.getPosicioCela(13, 11));
        
        return h;
    }

    private void distribuirOxigen() {
        
        int[] dades = {25,50,75}; //quantitat de oxygen
        
        for (int i = 0; i < fortalesa.getNumPlantes(); i++) {
            
            for (int j = 0; j < fortalesa.getNumHabitacions(i); j++) {
                Habitacio h = fortalesa.getHabitacio(i, j);
                int numOxigen = (int)(Math.random() * (MAX_OXIGEN_PER_HABITACIO) + 1);
                
                for (int k = 0; k < numOxigen; k++) {
                    int[] cela = obtenirCelaLliure(h);

                    int quantitat = dades[(int)(Math.random() * 3)];
                    Oxigen m = new Oxigen(quantitat);
                    
                    int[] posicio = h.getPosicioCela(cela[0], cela[1]);
                    m.setPosicioInicial(posicio[0], posicio[1]);
                    h.addActor(m);                     
                }
            }
            
        }
    }
    
    private void distribuirArma() {
        
            int i = 0;//(int)(Math.random() * 3);
            int j = 0;//(int)(Math.random() * 3);
            
            Habitacio h = fortalesa.getHabitacio(i, j);
            int numArma = 1; //(int)(Math.random() * (MAX_OXIGEN_PER_HABITACIO) + 1);
                
            for (int k = 0; k < numArma; k++) {
                int[] cela = obtenirCelaLliure(h);

                int quantitat = 1;
                Arma m = new Arma(quantitat);
                    
                int[] posicio = h.getPosicioCela(cela[0], cela[1]);
                m.setPosicioInicial(posicio[0], posicio[1]);
                h.addActor(m);                     
                }
    }

    private void distribuirSorpresa() {
        
            int i = (int)(Math.random() * 3);
            int j = (int)(Math.random() * 3);
            
            Habitacio h = fortalesa.getHabitacio(i, j);
            int numSorpresa= 1; //(int)(Math.random() * (MAX_OXIGEN_PER_HABITACIO) + 1);
                
            for (int k = 0; k < numSorpresa; k++) {
                int[] cela = obtenirCelaLliure(h);

                int quantitat = 50;
                Sorpresa m = new Sorpresa(quantitat);
                    
                int[] posicio = h.getPosicioCela(cela[0], cela[1]);
                m.setPosicioInicial(posicio[0], posicio[1]);
                h.addActor(m);                     
                }
    }
    
    private void distribuirSoldats() {
      
        for (int i = 0; i < fortalesa.getNumPlantes(); i++) {
            
            for (int j = 0; j < fortalesa.getNumHabitacions(i); j++) {
                Habitacio h = fortalesa.getHabitacio(i, j);
                int numSoldats = (int)(Math.random() * (MAX_SOLDATS_PER_HABITACIO)  + 1);
                
                for (int k = 0; k < numSoldats; k++) {
                    int[] cela = obtenirCelaLliure(h);
   
                    Soldat s = new Soldat();
                    
                    int[] posicio = h.getPosicioCela(cela[0], cela[1]);
                    s.setPosicioInicial(posicio[0], posicio[1]);
                    h.addActor(s);                     
                }
            }
            
        }
    }
    
    
     private void distribuirForatsNegres() {
      
        for (int i = 0; i < fortalesa.getNumPlantes(); i++) {
            
            for (int j = 0; j < fortalesa.getNumHabitacions(i); j++) {
                Habitacio h = fortalesa.getHabitacio(i, j);
                int numForats = (int)(Math.random() * (MAX_FORATS_PER_HABITACIO)  + 1);
                
                for (int k = 0; k < numForats; k++) {
                    int[] cela = obtenirCelaLliure(h);
   
                    ForatNegre f = new ForatNegre();
                    int[] posicio = h.getPosicioCela(cela[0], cela[1]);
                    f.setPosicioInicial(posicio[0], posicio[1]);
                    h.addActor(f);                    
                }
            }
            
        }
    }
    
   
    private int[] obtenirCelaLliure(Habitacio h) {
        int fila = 0;
        int col = 0;
        int cela[] = null;
        boolean trobada = false;
        boolean terra = false;
        
        while (!trobada) {            
            terra = false;
            while (!terra) {
                 fila = (int)Math.max(0,(Math.random() * Constants.NUM_CELES_VERTICALS-2));
                col = (int)Math.max(0,(Math.random() * Constants.NUM_CELES_HORIZONTALS-2));
                terra = (h.getValor(fila, col) == Constants.SIMBOL_TERRA &&
                        h.getValor(fila+1, col) == Constants.SIMBOL_TERRA &&
                        h.getValor(fila, col+1) == Constants.SIMBOL_TERRA &&
                        h.getValor(fila+1, col+1) == Constants.SIMBOL_TERRA );
            }
            
            // comprovar que cap actor este dins la cela
            Actor[] actors = h.getActorsAsArray();
            int i = 0;
            boolean lliure = true;
            while (i < actors.length && lliure) {
                cela = h.getCela(actors[i].getPosicioInicial()[0], 
                        actors[i].getPosicioInicial()[1]);
                lliure = fila != cela[0] || col != cela[1];            
                i++;
            }
            
            //comprovar que el heroi no este dins la cela
            if (lliure) {
	            cela = h.getCela(heroi.getPosicioInicial()[0], 
	                    heroi.getPosicioInicial()[1]);
	            lliure = fila != cela[0] || col != cela[1];
            }

            trobada = lliure;
        }
        return new int[] { fila, col };
    }
    

    /**
     * Principal.
     * 
     * @param args
     */
    public static void main(String[] args) {
        new Practica();
    }
    
}
