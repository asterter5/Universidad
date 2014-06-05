/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.ub.prog2.PrietoDehghanPourAstor.controlador;

import edu.ub.prog2.utils.*;

/**
 * Excepcio propia per a controlar els fitxers introduits a la biblioteca.
 * 
 * @author Astor Prieto
 */
public class ExcepcioFitxerRepetit extends FitxerAudioErrorException {
    
    public ExcepcioFitxerRepetit() {
        super("Fitxer ja existent a la Biblioteca.");
    }
}
