/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.ub.prog2.PrietoDehghanPourAstor.controlador;

import edu.ub.prog2.utils.*;

/**
 *
 * @author asterter5
 */
public class ExcepcioFitxerNoExisteix extends FitxerAudioErrorException {
    
    public ExcepcioFitxerNoExisteix() {
        super("Aquest fitxer no existeix.");
    }
    
}
