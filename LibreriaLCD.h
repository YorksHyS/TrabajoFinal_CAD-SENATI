
#include <xc.h>
#define _XTAL_FREQ 10000000

//Definición de comandos básicos
#define lin2_4b_5x7 0x28  //2lin-4bit-Matriz5x7
#define DonCoff 0x0C    //display on cursor off
#define CursorIncr 0x06 //incrementa cursor
#define limpiar 0x01    //limpiar pantalla

// Display ON/OFF Define controles 
#define DON         0b00001111  // Display on      
#define DOFF        0b00001011  // Display off     
#define CURSOR_ON   0b00001110  // Cursor on       
#define CURSOR_OFF  0b00001100  // Cursor off      
#define BLINK_ON    0b00001101  // Cursor Blink    
#define BLINK_OFF   0b00001100  // Cursor No Blink 

// Cursor or Display Define desplazamientos 
#define SHIFT_CUR_LEFT    0b00010000  // Cursor shifts to the left   
#define SHIFT_CUR_RIGHT   0b00010100  // Cursor shifts to the right  
#define SHIFT_DISP_LEFT   0b00011000  // Display shifts to the left  
#define SHIFT_DISP_RIGHT  0b00011100  // Desplazam palabra a derecha 

//comandos disponibles
#define      LCD_FIRST_ROW           128 //ubica el cursor en el primer renglón
#define      LCD_SECOND_ROW          192 //ubica el cursor en el segundo renglón
#define      LCD_THIRD_ROW           148 //ubica el cursor en el tercer renglón
#define      LCD_FOURTH_ROW          212 //ubica el cursor en el cuarto renglón
#define      LCD_CLEAR               1   //Limpia la pantalla
#define      LCD_RETURN_HOME         2   //Regreso del cursor al inicio
#define      LCD_CURSOR_OFF          12  // apaga el cursor
#define      LCD_UNDERLINE_ON        14  //Selección de subrayado
#define      LCD_BLINK_CURSOR_ON     15  // parpadeo del cursor
#define      LCD_MOVE_CURSOR_LEFT    16  //cursor se mueve a la izquierda
#define      LCD_MOVE_CURSOR_RIGHT   20  //cursor se mueve a la derecha
#define      LCD_TURN_OFF            0   //apaga el lcd
#define      LCD_TURN_ON             8   //enciende la lcd
#define      LCD_SHIFT_LEFT          24  //Desplazamiento a la izquierda
  
/***********************************/
/* Pines de conexionado para el LCD*/
/***********************************/
#define E_PIN PORTBbits.RB2
#define TRIS_E TRISBbits.TRISB2

#define RS_PIN PORTBbits.RB3
#define TRIS_RS TRISBbits.TRISB3

#define DATA_PORT PORTB
#define TRIS_DATA_PORT TRISB


unsigned char cmd, car, datlcd, comandLCD;

/**********************************/
/* Enviar un comando al LCD       */
/**********************************/
void lcd_cmd(unsigned char cmd) {
    DATA_PORT&=0x0F;
    DATA_PORT|=cmd&0xF0;
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_ms(5);
    DATA_PORT&=0x0F;
    DATA_PORT|=(cmd<<4)&0xF0;    
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_ms(5);
    return;
}

/**********************************/
/* Clear and home the LCD         */
/**********************************/
void lcd_Clear(void)
{
    lcd_cmd(0x01);
    __delay_ms(2);
}

/*********************************/
/* Escribir un dato en el lcd    */
/*********************************/
void lcd_Data(unsigned char car) {
    DATA_PORT&=0x0F;
    DATA_PORT|=(car&0xF0);
    RS_PIN = 1;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_ms(5);
    DATA_PORT&=0x0F;
    DATA_PORT|=((car<<4)&0xF0);    
    RS_PIN = 1;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_ms(5);
    return;
}

/***********************************/
/* Cusor en fila y columna del lcd */
/***********************************/
void lcd_cursor_xy(char row,char column)
{
    unsigned char direccion;
    if (row != 1)
        direccion = 0x40;
    else
        direccion = 0x00;
    direccion += column - 1;
    lcd_cmd(0x80 | direccion);

}

/******************************************/
/* Escribe una cadena de caracteres en LCD*/
/******************************************/
void lcd_Putrs(char row, char column, const char * s)
{
    char direccion;
    if (row != 1)
        direccion = 0x40;
    else
        direccion = 0;
    direccion += column - 1;
    lcd_cmd(0x80 | direccion);
    while (*s)
        lcd_Data(*s++);
}

void lcd_Puts(char row, char column, char * s)
{
    unsigned char direccion;
    if (row != 1)
        direccion = 0x40;
    else
        direccion = 0;
    direccion += column - 1;
    lcd_cmd(0x80 | direccion);
    while (*s)
        lcd_Data(*s++);
}

/*************************************************/
/* Escribe caracter en LCD dado la fila y columna*/
/*************************************************/
void lcd_PutchDir(char row, char column, char c)
{
    char direccion;
    if (row != 1)
        direccion = 0x40;
    else
        direccion = 0;
    direccion += column - 1;
    lcd_cmd(0x80 | direccion);
    lcd_Data(c);
}

/********************************/
/*Escribe un cartacter en LCD en*/
/*posición actual del cursor    */
/********************************/
void lcd_Putch(char c)
{
    lcd_Data(c);
}

/**********************************/
/* Inicializa el LCD - modo 4 bits*/
/**********************************/
void lcd_Init() {

    //-- Configurar el lcd
    char x = 0;
    char init_value;

    init_value = 0x30;
    TRIS_DATA_PORT = 0x03;
    
    __delay_ms(15);
    DATA_PORT = init_value;
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_ms(5);

    DATA_PORT = init_value;
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_us(200);
    DATA_PORT = init_value;
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_us(200);
    DATA_PORT = 0x20; 
    RS_PIN = 0;
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
    __delay_us(40);
 
    lcd_cmd(lin2_4b_5x7);
    lcd_cmd(DonCoff);
    lcd_cmd(CursorIncr);
    lcd_cmd(limpiar);
    //lcd_cmd(0x02);
    return;
}
