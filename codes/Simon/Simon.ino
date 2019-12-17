/*
 * Project: SIMON.ino Shield - Simon v0.1
 * Author: Carlos Hernández
 * Programador: Agustín Gallego Ordoñez
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ABLocks_TimerFreeTone.h>


// Declara los pines
const byte GreLED_pin = 2;
const byte RedLED_pin = 3;
const byte BluLED_pin = 4;
const byte YelLED_pin = 5;
const byte StatusLED_pin = 13;

const byte GreSW_pin = 8;
const byte RedSW_pin = 9;
const byte BluSW_pin = 10;
const byte YelSW_pin = 11;
const byte UpSW_pin  = A0;
const byte DwSW_pin  = A1;
const byte OkSW_pin  = A2;

const byte Buzzer_pin = 6;

bool Sound = true;

byte GreSW_status = 0;
byte RedSW_status = 0;
byte BluSW_status = 0;
byte YelSW_status = 0;
byte UpSW_status  = 0;
byte DwSW_status  = 0;
byte OkSW_status  = 0;

int GreLED_status = 0;
int RedLED_status = 0;
int BluLED_status = 0;
int YelLED_status = 0;

const byte swPush = 100;
const byte swPressed = 110;
int turnOnLED  = 10000;
const int turnOffLED = 0;

byte sequence[256];
int level = 1;
int machinePulsations = 0;
int currentPulsation = 0;

const byte MACHINE = 0;
const byte USER = 1;
byte turn = MACHINE;

// Configura la pantalla OLED
Adafruit_SSD1306 oled_1(128,64, &Wire,-1);

// Declara el bitmap con el logotipo
static const uint8_t PROGMEM simonLogo[] PROGMEM = {128, 32, 0xD5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xFD, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC6, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x42, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0E, 0x42, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x92, 0x00, 0x00, 0x06, 0x00, 0x78, 0x0D, 0xE3, 0x41, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x94, 0x92, 0x00, 0x00, 0x1A, 0x00, 0x48, 0x1B, 0xE1, 0xC1, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xDC, 0x00, 0x00, 0xE2, 0x1F, 0xC4, 0x37, 0xCE, 0xC1, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0x01, 0x31, 0x84, 0x6F, 0xDE, 0xC0, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x03, 0x20, 0x86, 0x6F, 0xDE, 0xC0, 0x84, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xF8, 0x0C, 0x20, 0x02, 0xC3, 0xBE, 0xC0, 0x04, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x88, 0x10, 0x20, 0x02, 0xDC, 0x3E, 0xC2, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x60, 0x09, 0x90, 0x20, 0x01, 0xDE, 0x3C, 0xC2, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0E, 0x88, 0x20, 0x01, 0xDE, 0xC1, 0xC2, 0x04, 0x04, 0x7C, 0x38, 0x00, 0x01, 0x80, 0x00, 0x83, 0xFC, 0x88, 0x20, 0x00, 0xDE, 0xF1, 0x42, 0x04, 0x04, 0xC4, 0x44, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x88, 0x20, 0x00, 0xDD, 0xF3, 0x43, 0x04, 0x0C, 0x46, 0xC2, 0x00, 0x01, 0x80, 0x00, 0x88, 0x00, 0x88, 0x20, 0x90, 0xCD, 0xF6, 0x47, 0x04, 0x0C, 0x46, 0x82, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x48, 0x20, 0xF8, 0x63, 0xEC, 0x45, 0x04, 0x0C, 0x46, 0x82, 0x00, 0x01, 0x80, 0x00, 0x43, 0xC0, 0x48, 0x10, 0xA8, 0x63, 0xC8, 0x44, 0x84, 0x0C, 0x46, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x45, 0xF0, 0x88, 0x38, 0x30, 0x44, 0x84, 0xCC, 0x46, 0x44, 0x00, 0x01, 0x80, 0x00, 0x18, 0x06, 0x66, 0x30, 0x84, 0x2F, 0xC0, 0x7C, 0xFC, 0xCC, 0x46, 0x38, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x02, 0x60, 0x10, 0x84, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xF1, 0xE0, 0x1F, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xD1, 0x7D, 0xF4, 0x38, 0x01, 0x80, 0x00, 0x00, 0x79, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x11, 0x11, 0x04, 0x24, 0x00, 0x00, 0x00, 0x1F, 0xC1, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x11, 0x11, 0x04, 0x22, 0x01, 0x80, 0x00, 0x10, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xDF, 0x11, 0xE4, 0x22, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x11, 0x04, 0x22, 0x01, 0x80, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x11, 0x04, 0x24, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xD1, 0x7D, 0xF7, 0xB8, 0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*  **********************************************************
 *  ********************************** INICIALIZA EL JUEGO ***
 *  **********************************************************
 */
void setup()
{
  //Serial.begin(9600);
  oled_1.begin(SSD1306_SWITCHCAPVCC,0x3C);

  pinMode(GreLED_pin, OUTPUT);
  pinMode(RedLED_pin, OUTPUT);
  pinMode(BluLED_pin, OUTPUT);
  pinMode(YelLED_pin, OUTPUT);
  pinMode(StatusLED_pin, OUTPUT);
  
  pinMode(GreSW_pin, INPUT);
  pinMode(RedSW_pin, INPUT);
  pinMode(BluSW_pin, INPUT);
  pinMode(YelSW_pin, INPUT);
  pinMode(UpSW_pin, INPUT);
  pinMode(DwSW_pin, INPUT);
  pinMode(OkSW_pin, INPUT);
    
  oled_1.clearDisplay(); oled_1.display();
  oled_1.clearDisplay(); oled_1.drawBitmap(0,0,&simonLogo[2],simonLogo[0], simonLogo[1],WHITE); oled_1.display();

  // Muestra el mensaje de bienvenida
  showWelcome();

  // Genera la secuencia
  generateSequence();

}

/*  **********************************************************
 *  ************************************ FUNCIÓN PRINCIPAL ***
 *  **********************************************************
 */
void loop()
{
  // Muestra la puntuacion
  showScore();

  if (turn == MACHINE) turnMACHINE();
  if (turn == USER) turnUSER();
}


/*  **********************************************************
 *  ********************************* FUNCIONES AUXILIARES ***
 *  **********************************************************
 */
 
// Turno de la maquina
void turnMACHINE() {
  digitalWrite(StatusLED_pin,LOW);
  
  // Actualiza el estado de los botones
  updateSwitchStatus();
  
  // Actualiza el estado de las luces
  updateLedStatus();
    
  for (int i=0; i <= machinePulsations; i++) {   
    simPush(sequence[i]);
    waitPush();
    delay(100);
  }
  currentPulsation = 0;
  machinePulsations++;
  turn = USER;
}


// Turno del usuario
void turnUSER() {

  // Enciende el LED de turno de usuario
  digitalWrite(StatusLED_pin,HIGH);
  
  byte switchID = 0;
  do {
    // Actualiza el estado de los botones
    updateSwitchStatus();
  
    // Actualiza el estado de las luces
    updateLedStatus();

    switchID = 0;
    if (GreSW_status == swPush) switchID = GreSW_pin;
    if (RedSW_status == swPush) switchID = RedSW_pin;
    if (BluSW_status == swPush) switchID = BluSW_pin;
    if (YelSW_status == swPush) switchID = YelSW_pin;
    
    if (switchID) {
      clearPush();

      switch (switchID) {
        case GreSW_pin:
          GreLED_status = turnOnLED;
          if (Sound == true) tone(Buzzer_pin,500);
        break;

        case RedSW_pin:
          RedLED_status = turnOnLED;
          if (Sound == true) tone(Buzzer_pin,800);
        break;

        case BluSW_pin:
          BluLED_status = turnOnLED;
          if (Sound == true) tone(Buzzer_pin,1000);
        break;

        case YelSW_pin:
          YelLED_status = turnOnLED;
          if (Sound == true) tone(Buzzer_pin,1200);
        break;
      }
    

      /* Comprueba si la pulsacion es correcta y
       *  si no es correcta reinicia el juego
       */
      if (switchID == sequence[currentPulsation]) {
        currentPulsation++;
      } else {
        userFail();
  
        // Reinicia el juego
        digitalWrite(StatusLED_pin, LOW);
        machinePulsations = 0;
        generateSequence();
  
        // Muestra el mensaje de bienvenida
        showWelcome();
      } 
    }
  } while (currentPulsation < machinePulsations);

  digitalWrite(StatusLED_pin, LOW);
  currentPulsation = 0;
  waitPush();
  delay(500);
  turn = MACHINE;
}

// Muestra las puntuación
void showScore() {
  oled_1.writeFillRect(0, 40, 128, 24, BLACK); oled_1.display();
  char tmpString[3] = {0};
  char txtScore[20] = {0};

  

  sprintf(tmpString,"%d", machinePulsations);
  strcpy(txtScore, "Pulsaciones: ");
  strcat(txtScore, tmpString);
  
  oled_1.setCursor(0,48); oled_1.print(txtScore); 
  oled_1.display();
}

// Muestra aviso cuando el usuario falla
void userFail() {
  if (Sound == true) noTone(Buzzer_pin);
  clearPush();

  for (int i=0; i<10; i++) {
    if (Sound == true) tone(Buzzer_pin,50);
    digitalWrite(GreLED_pin,HIGH);
    digitalWrite(RedLED_pin,HIGH);
    digitalWrite(BluLED_pin,HIGH);
    digitalWrite(YelLED_pin,HIGH);
    delay(100);
    digitalWrite(GreLED_pin,LOW);
    digitalWrite(RedLED_pin,LOW);
    digitalWrite(BluLED_pin,LOW);
    digitalWrite(YelLED_pin,LOW);
    noTone(Buzzer_pin);
    delay(50);
  }
  delay (500);
}

// Muestra la bienvenida y tutorial
void showWelcome() {
  int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
  int duration[] = { 125, 75, 75, 125, 125, 125, 125, 125 };

  
  oled_1.writeFillRect(0, 40, 128, 24, BLACK);

  oled_1.setTextSize(1); 
  oled_1.setTextColor(WHITE); 
  oled_1.setCursor(14,40); oled_1.print("Bienvenido amigo!"); 
  oled_1.display();

  if (Sound == true) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      TimerFreeTone(Buzzer_pin, melody[thisNote], duration[thisNote]); 
    }
  }
  beep();

  // MSG: Bienvenida
  oled_1.setCursor(0,56); oled_1.print("Pulse OK..."); 
  oled_1.display();
  waitSwitch(OkSW_pin);
  beep();

  // MSG: Objetivo
  oled_1.clearDisplay(); oled_1.display();
  oled_1.setCursor(40,0); oled_1.print("OBJETIVO!"); 
  oled_1.setCursor(0,16); oled_1.print("Repetir la secuencia"); 
  oled_1.setCursor(0,24); oled_1.print("de colores en orden."); 
  oled_1.setCursor(0,56); oled_1.print("Pulse OK..."); 
  oled_1.display();
  waitSwitch(OkSW_pin);
  beep();

  // MSG: Tu turno
  oled_1.clearDisplay(); oled_1.display();
  oled_1.setCursor(40,0); oled_1.print("TU TURNO!"); 
  oled_1.setCursor(0,16); oled_1.print("Cuando se encienda el"); 
  oled_1.setCursor(0,24); oled_1.print("LED verde de status"); 
  oled_1.setCursor(0,32); oled_1.print("sera tu turno."); 
  oled_1.setCursor(0,56); oled_1.print("Pulse OK..."); 
  oled_1.display();
  waitSwitch(OkSW_pin);
  beep();

  // MSG: Comienza el juego
  oled_1.clearDisplay(); 
  oled_1.clearDisplay(); oled_1.drawBitmap(0,0,&simonLogo[2],simonLogo[0], simonLogo[1],WHITE); 
  oled_1.setCursor(8,40); oled_1.print("COMIENZA EL JUEGO!");
  oled_1.setCursor(0,56); oled_1.print("Pulse OK...");
  oled_1.display();
  waitSwitch(OkSW_pin);
  beep();

  oled_1.writeFillRect(0, 40, 128, 24, BLACK); 
  oled_1.display();
  delay(1000);
}

// Genera la secuencia
void generateSequence() {
  randomSeed(millis());
  for (int i=0; i<=255; i++) {
    sequence[i] = random(8,12);
  }
}

// Actualiza el estado de los LEDs
void updateLedStatus() {

  if (GreLED_status == turnOnLED) digitalWrite(GreLED_pin, HIGH);
  if (RedLED_status == turnOnLED) digitalWrite(RedLED_pin, HIGH);
  if (BluLED_status == turnOnLED) digitalWrite(BluLED_pin, HIGH);
  if (YelLED_status == turnOnLED) digitalWrite(YelLED_pin, HIGH);

  if (GreLED_status == turnOffLED) digitalWrite(GreLED_pin, LOW);
  if (RedLED_status == turnOffLED) digitalWrite(RedLED_pin, LOW);
  if (BluLED_status == turnOffLED) digitalWrite(BluLED_pin, LOW);
  if (YelLED_status == turnOffLED) digitalWrite(YelLED_pin, LOW);
  
  if (GreLED_status > turnOffLED) GreLED_status--;
  if (RedLED_status > turnOffLED) RedLED_status--;
  if (BluLED_status > turnOffLED) BluLED_status--;
  if (YelLED_status > turnOffLED) YelLED_status--;

  if (GreLED_status < 2 && RedLED_status < 2 && BluLED_status < 2 && YelLED_status < 2) noTone(Buzzer_pin);
}

// Emite un beep
void beep(){
  tone(Buzzer_pin,100);
  delay(20);
  noTone(Buzzer_pin);
}

// Reinicia todas las pulsaciones
void clearPush() {
  noTone(Buzzer_pin);
  digitalWrite(GreLED_pin, LOW);
  digitalWrite(RedLED_pin, LOW);
  digitalWrite(BluLED_pin, LOW);
  digitalWrite(YelLED_pin, LOW);

  GreLED_status = 0;
  RedLED_status = 0;
  BluLED_status = 0;
  YelLED_status = 0;
}

// Simula una pulsación (Para el turno de la máquina)
void simPush(byte sw) {
  switch (sw) {
    case GreSW_pin:
      GreLED_status = turnOnLED;
      if (Sound == true) tone(Buzzer_pin,500);
      break;
      
    case RedSW_pin:
      RedLED_status = turnOnLED;
      if (Sound == true) tone(Buzzer_pin,800);
      break;

    case BluSW_pin:
      BluLED_status = turnOnLED;
      if (Sound == true) tone(Buzzer_pin,1000);

      break;

    case YelSW_pin:
      YelLED_status = turnOnLED;
      if (Sound == true) tone(Buzzer_pin,1200);
      break;
  }     
}

// Espera a que terminen todas las pulsaciones
void waitPush() {
  byte exit = 0;
  do {
    updateLedStatus();
    exit = true;
    if (GreLED_status > 0) exit = false;
    if (RedLED_status > 0) exit = false;
    if (BluLED_status > 0) exit = false;
    if (YelLED_status > 0) exit = false;
    
  } while (!exit);
  updateLedStatus();
}

// Espera a que se presione un pulsador
void waitSwitch(byte sw) {
  byte switch_status = 0;
  
  do {
    updateSwitchStatus();  

    switch (sw) {
      case GreSW_pin:
        switch_status = GreSW_status;
        break;

      case RedSW_pin:
        switch_status = RedSW_status;
        break;

      case BluSW_pin:
        switch_status = BluSW_status;
        break;

      case YelSW_pin:
        switch_status = YelSW_status;
        break;

      case UpSW_pin:
        switch_status = UpSW_status;
        break;

      case DwSW_pin:
        switch_status = DwSW_status;
        break;

      case OkSW_pin:
        switch_status = OkSW_status;
        break;
     }
  } while (switch_status != swPush);
}

// Actualiza el estado de los botones
void updateSwitchStatus(){
  if (digitalRead(GreSW_pin) && GreSW_status < swPressed) GreSW_status++;
  if (digitalRead(RedSW_pin) && RedSW_status < swPressed) RedSW_status++;
  if (digitalRead(BluSW_pin) && BluSW_status < swPressed) BluSW_status++;
  if (digitalRead(YelSW_pin) && YelSW_status < swPressed) YelSW_status++;
  if (digitalRead(UpSW_pin) && UpSW_status < swPressed) UpSW_status++;
  if (digitalRead(DwSW_pin) && DwSW_status < swPressed) DwSW_status++;
  if (digitalRead(OkSW_pin) && OkSW_status < swPressed) OkSW_status++;

  if (!digitalRead(GreSW_pin)) GreSW_status = 0;
  if (!digitalRead(RedSW_pin)) RedSW_status = 0;
  if (!digitalRead(BluSW_pin)) BluSW_status = 0;
  if (!digitalRead(YelSW_pin)) YelSW_status = 0;
  if (!digitalRead(UpSW_pin)) UpSW_status = 0;
  if (!digitalRead(DwSW_pin)) DwSW_status = 0;
  if (!digitalRead(OkSW_pin)) OkSW_status = 0;
}







    
