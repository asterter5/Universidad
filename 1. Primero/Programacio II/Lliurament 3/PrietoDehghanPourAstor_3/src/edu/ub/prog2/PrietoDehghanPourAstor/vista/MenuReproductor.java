
package edu.ub.prog2.PrietoDehghanPourAstor.vista;

import edu.ub.prog2.PrietoDehghanPourAstor.controlador.*;
import edu.ub.prog2.PrietoDehghanPourAstor.model.*;
import edu.ub.prog2.utils.*;
import java.io.*;
import java.util.*;

/**
 * Classe per al menu del reproductor B, implementada amb ArrayList.
 * 
 * @author Astor Prieto
 */
public class MenuReproductor implements Serializable{
    
    /**
     * FitxerAudio per a la gestio del menu.
     */
    private FitxerAudio f;
    /**
     * Scanner per a la gestio del menu.
     */
    private Scanner sc = new Scanner(System.in);
    /**
     * Objetcte del tipus CtrlReproductor per a la gestio del menu.
     */
    private CtrlReproductor control = new CtrlReproductor();
    
    static private enum OpcionsMenu {OPCIO1, OPCIO2, OPCIO3, OPCIO4, OPCIO5, SORTIR};
    static private enum OpcionsSubmenu1 {SUBOP11, SUBOP12, SUBOP13, ANTERIOR1};
    static private enum OpcionsSubmenu2 {SUBOP21, SUBOP22, SUBOP23, SUBOP24, ANTERIOR2};
    static private enum OpcionsSubmenu3 {SUBOP31, SUBOP32, SUBOP33, SUBOP34, SUBOP35, SUBOP36, ANTERIOR3};
    static private enum OpcionsSubSubmenu {SUBSUB1, SUBSUB2, SUBSUB3, ANTANTERIOR};
    static private enum OpcionsSubRepro {SUB1, SUB2, SUB3, SUB4, ANT};
    
    static private String[] descOpcionsMenu = {"Gestio Biblioteca: ", "Gestio Llistes Reproduccio: ","Control Reproduccio: ", "Guardar Dades: ", "Recuperar Dades: ", "SORTIR"};
    static private String[] descOpcionsSubmenu1 = {"Afegir Fitxer Audio: ", "Mostrar Biblioteca: ", "Eliminar Fitxer: ", "Menu Anterior."};
    static private String[] descOpcionsSubmenu2 = {"Afegir Llista: ", "Mostrar Llistes: ", "Eliminar Llista: ", "Gestionar Llista: ", "Menu Anterior."};
    static private String[] descOpcionsSubmenu3 = {"Reproduir pista: ", "Reproduir biblioteca: ", "Reproduir llista reproduccio: ", "Activar/Desactivar Reproduccio aleatoria: ", "Activar/Desactivar Reproduccio ciclica: ", "Gestio Reproduccio: ", "Menu Anterior."};
    static private String[] descOpcionsSubSub = {"Afegir Fitxer Audio: ", "Mostrar Llista: ", "Eliminar Fitxer: ", "Menu Anterior."};
    static private String[] descOpcionsSubRepro = {"Play: ", "Pause: ", "Next: ", "Stop: ", "Sortir."};
    
    public void gestioReproductorUB() throws FileNotFoundException, ClassNotFoundException, IOException, CloneNotSupportedException, FitxerAudioErrorException {
        Scanner sc = new Scanner(System.in);
        
        MenuReproductor repro = new MenuReproductor();
        repro.gestioMenuReproductor(sc);
    }
    
    private void gestioMenuReproductor(Scanner sc) throws FileNotFoundException, ClassNotFoundException, IOException, CloneNotSupportedException, FitxerAudioErrorException {
        Menu<OpcionsMenu> menu = new Menu<OpcionsMenu>("Reproductor UB3", OpcionsMenu.values());
        menu.setDescripcions(descOpcionsMenu);
        
        OpcionsMenu opcio = null;
        while (opcio != OpcionsMenu.SORTIR) {
            
            menu.mostrarMenu();
            opcio = menu.getOpcio(sc);
            
            switch(opcio) {
                case OPCIO1:
                    gestioSubmenu1(sc);
                    break;
                    
                case OPCIO2:
                    gestioSubmenu2(sc);
                    break;
                    
                case OPCIO3:
                    gestioSubmenu3(sc);
                    break;
                    
                case OPCIO4:
                    System.out.println("Opcio 4...");
                    System.out.println("Nom per a guardar el fitxer: ");
                    String nomSav = sc.nextLine();
                    control.guardarDades(nomSav);
                    break;
                    
                case OPCIO5:
                    System.out.println("Opcio 5...");
                    System.out.println("Nom del fitxer a recuperar: ");
                    String nomRec = sc.nextLine();
                    control = control.recuperarDades(nomRec);
                    break;
                    
                case SORTIR:
                    System.out.println("Fins Aviat!");
                    break;
                    
            }
        }
    }
    
    private void gestioSubmenu1(Scanner sc) throws ClassNotFoundException, IOException, CloneNotSupportedException {
        Menu<OpcionsSubmenu1> menu = new Menu<OpcionsSubmenu1>("1. Gestio Biblioteca: ", OpcionsSubmenu1.values());
        menu.setDescripcions(descOpcionsSubmenu1);
        
        OpcionsSubmenu1 opcio = null;
            
        menu.mostrarMenu();
        opcio = menu.getOpcio(sc);
            
        switch(opcio) {
            case SUBOP11:
                System.out.println("Opcio 1...");
                System.out.print("PATH: ");
                String path = sc.nextLine();
                FitxerAudio f = new FitxerAudio(path);
                control.demanaDadesTeclat(f, sc);
                control.afegirFitxer(f);
                break;
                    
            case SUBOP12:
                System.out.println("Opcio 2...");
                System.out.println(control.getBiblioteca().toString());
                break;
                
            case SUBOP13:
                System.out.println("Opcio 3...");
                System.out.println("Path del fitxer a eliminar: ");
                FitxerAudio elim = new FitxerAudio(sc.nextLine());
                control.eliminarFitxer(elim);
                break;
                    
            case ANTERIOR1:
                break;
                
        }
        
    }
    
    private void gestioSubmenu2(Scanner sc) throws ClassNotFoundException, IOException {
        Menu<OpcionsSubmenu2> menu = new Menu<OpcionsSubmenu2>("2. Gestio Llistes Reproduccio: ", OpcionsSubmenu2.values());
        menu.setDescripcions(descOpcionsSubmenu2);
        
        OpcionsSubmenu2 opcio = null;
            
        menu.mostrarMenu();
        opcio = menu.getOpcio(sc);
            
        switch(opcio) {
            case SUBOP21:
                System.out.println("Opcio 1...");
                System.out.println("Nom de la llista: ");
                String nomList = sc.nextLine();
                control.crearLlistaReproduccio(nomList);
                break;
                    
            case SUBOP22:
                System.out.println("Opcio 2...");
                System.out.println("--- LLISTES REPRODUCCIO ---");
                String[] tmp = control.getLlistesReproduccio();
                for (int i = 0; i < control.getDades().getI(); i++) {
                    System.out.println((i+1) +" - "+ tmp[i]);
                } 
                break;
                    
            case SUBOP23:
                System.out.println("Opcio 3...");
                System.out.print("Llista a eliminar: ");
                LlistaReproduccio elm = control.getLlistaReproduccio(sc.nextLine());
                control.eliminarLlistaReproduccio(elm);
                break;
                    
            case SUBOP24:
                System.out.println("Nom de la llista a Gestionar: ");
                String gList = sc.next();
                if (control.getLlistaReproduccio(gList) != null) {
                    gestioSubSubmenu(sc, gList);
                } else {
                    System.err.println("Llista de reproduccio inexistent.");
                }
                break;
                   
            case ANTERIOR2:
                break;
               
        }
        
    }
    
    private void gestioSubmenu3(Scanner sc) throws ClassNotFoundException, IOException, FitxerAudioErrorException, CloneNotSupportedException {
        Menu<OpcionsSubmenu3> menu = new Menu<OpcionsSubmenu3>("3. Control Reproduccio: ", OpcionsSubmenu3.values());
        menu.setDescripcions(descOpcionsSubmenu3);
        
        OpcionsSubmenu3 opcio = null;
            
        menu.mostrarMenu();
        opcio = menu.getOpcio(sc);
            
        switch(opcio) {
            case SUBOP31:
                System.out.println("Opcio 1...");
                System.out.println("Introdueix el index de la pista a reproduir: ");
                int pos = sc.nextInt();
                control.playFitxer(pos);
                break;
                    
            case SUBOP32:
                System.out.println("Opcio 2..."); 
                System.out.println("Reproduint Biblioteca.");
                control.playLlista();
                break;
                    
            case SUBOP33:
                System.out.println("Opcio 3...");
                System.out.println("Llista a Reproduir: ");
                String nom = sc.nextLine();
                control.playLlista(control.getLlistaReproduccio(nom));
                System.out.println("Reproduint '"+ nom +"'.");
                break;
                    
            case SUBOP34:
                System.out.println("Opcio 4...");
                switch (control.getAleatori()) {
                    case 0:
                        control.setAleatori(true);
                        System.out.println("ALEATORI [ACTIVAT]");
                        break;
                        
                    case 1:
                        control.setAleatori(false);
                        System.out.println("ALEATORI [DESACTIVAT]");
                        break;
                }
                break;
                
                   
            case SUBOP35:
                System.out.println("Opcio 5...");
                switch (control.getCiclic()) {
                    case 0:
                        control.setCiclic(true);
                        System.out.println("CICLIC [ACTIVAT]");
                        break;
                        
                    case 1:
                        control.setCiclic(false);
                        System.out.println("CICLIC [DESACTIVAT]");
                        break;
                }
                break;
                
            case SUBOP36:
                gestioSubRepro(sc);
                break;
                
            case ANTERIOR3:
                break;
               
        }
        
    }
    
    private void gestioSubSubmenu(Scanner sc, String nomLista) throws ClassNotFoundException, IOException {
        Menu<OpcionsSubSubmenu> menu = new Menu<OpcionsSubSubmenu>("2.4. Gestionar Llista: ", OpcionsSubSubmenu.values());
        menu.setDescripcions(descOpcionsSubSub);
        
        OpcionsSubSubmenu opcio = null;
            
        menu.mostrarMenu();
        opcio = menu.getOpcio(sc);
           
        switch(opcio) {
            case SUBSUB1:
                System.out.println("Opcio 1...");
                System.out.println("Selecciona index a intoduir: ");
                int i = sc.nextInt();
                control.getLlistaReproduccio(nomLista).add(control.retornFitxer(i));
                break;
                    
            case SUBSUB2:
                System.out.println("Opcio 2...");
                System.out.println(control.getLlistaReproduccio(nomLista).toString());
                break;
                
            case SUBSUB3:
                System.out.println("Opcio 3...");
                System.out.println("Selecciona index a eliminar: ");
                int y = sc.nextInt();
                control.getLlistaReproduccio(nomLista).remove(control.retornFitxer(y));
                break;
                    
            case ANTANTERIOR:
                break;
                
        }
        
    }
    
    private void gestioSubRepro(Scanner sc) throws ClassNotFoundException, IOException, FitxerAudioErrorException {
        Menu<OpcionsSubRepro> menu = new Menu<OpcionsSubRepro>("3.6. Gestionar Reproduccio: ", OpcionsSubRepro.values());
        menu.setDescripcions(descOpcionsSubRepro);
        
        OpcionsSubRepro opcio = null;
            
        menu.mostrarMenu();
        opcio = menu.getOpcio(sc);
           
        switch(opcio) {
            case SUB1:
                System.out.println("1. [PLAY]");
                control.resumeFitxer(f);
                break;
                    
            case SUB2:
                System.out.println("2. [PAUSE]");
                control.pauseFitxer(f);
                break;
                
            case SUB3:
                System.out.println("3. [NEXT]");
                control.stopFitxer(f);
                control.nextFitxer();
                break;
                  
            case SUB4:
                System.out.println("3. [STOP]");
                control.stopFitxer(f);
                break;
                
            case ANT:
                break;
                
        }
        
    }
}

