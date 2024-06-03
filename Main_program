
//#pragma config FOSC = HS 

#include <xc.h>
//#include "BITS.h"
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 10000000

#define SELECT RA0
#define ST_SP RA1
#define BUTTON RA2

int contador = 0;
char numero[10];

int TOPE = 999; // CON ESTA VARIABLE CONTROLAS HASTA CUANTO PUEDE LLEGAR EL CONTADOR


// FUNCION QUE CONVIERTE UYN ENTERO EN UN STRING
void int_to_string(int num, char* buffer) {
    int i = 0;
    do {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    } while (num != 0);
    buffer[i] = '\0';

    // Invertir la cadena
    int j = 0;
    char temp;
    for (j = 0; j < i / 2; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

void pulsos(void) {
    // Realiza la acción deseada
    RA3 = 1; // Activa RA0
    __delay_ms(1000); // Espera 1 segundo
    RA3 = 0; // Desactiva RA0
    __delay_ms(100); // Espera 1 segundo
}

void mostrar_contador(void) {

    if (contador >= TOPE) {
        contador = 0;
        lcd_Putrs(2, 1, "    REINICIO    ");
        __delay_ms(10);
        lcd_Clear();

    } else {
        int_to_string(contador, numero);
        lcd_Putrs(2, 1, numero);
        __delay_ms(100);
    }

}

void main(void) {

    //LCD
    TRISBbits.TRISB0 = 0; // 
    TRISBbits.TRISB1 = 0; // 
    TRISBbits.TRISB2 = 0; // RS
    TRISBbits.TRISB3 = 0; // E
    TRISBbits.TRISB4 = 0; // D4
    TRISBbits.TRISB5 = 0; // D5
    TRISBbits.TRISB6 = 0; // D6
    TRISBbits.TRISB7 = 0; // D7

    // CONFIGURACIONES GLOBALES    
    OPTION_REGbits.T0CS = 0; // Fuente de reloj interna para TMR0
    OPTION_REGbits.PSA = 0; // Prescaler asignado a TMR0
    OPTION_REGbits.PS = 0b111; // Configura el preescalar a 1:256l

    //CONFIGURACION DE PINES DE CONTROL
    TRISAbits.TRISA0 = 1; // Configura RA0 como salida
    TRISAbits.TRISA1 = 1; // ST_SP
    TRISAbits.TRISA3 = 0; // LE
    TRISAbits.TRISA2 = 1; // button
    TRISAbits.TRISA4 = 1; // Configura RA4 como entrada

    //INICIACION DE PUERTOS
    PORTA = 0;
    PORTB = 0;

    lcd_Init();

    lcd_Putrs(1, 1, " ---CONTADOR--- ");
    __delay_ms(1000);
    lcd_Clear();

    while (1) {

        if (ST_SP == 1) {
            while (1) {
                lcd_Putrs(2, 1, "                ");
                lcd_Putrs(1, 7, "          ");
                lcd_Putrs(1, 1, "MODO: ");

                if (SELECT == 1) { //Automatico
                    lcd_Putrs(1, 7, "AUTO");
                    if (RA4 == 1) { // Si se detecta un flanco de subida en RA4
                        pulsos();
                        contador++;
                    }
                } else { // manual
                    lcd_Putrs(1, 7, "MANUAL");
                    if (BUTTON == 1) {
                        pulsos();
                        contador++;
                        __delay_ms(10);
                    }
                }
                mostrar_contador();
                if (ST_SP == 0) {
                    break;
                }
            }

        } else {
            while (1) {
                __delay_ms(50);
                if (ST_SP == 1) {
                    break;
                }
            }
        }
    }
    return;
}

