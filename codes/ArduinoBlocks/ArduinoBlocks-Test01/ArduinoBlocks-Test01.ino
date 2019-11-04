/* ArduinoBlocks.com */
/* Project: SIMON.ino Shield - Test01 */
/* Author: Carlos Hernández */

#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ABLocks_TimerFreeTone.h>

double LED_VERDE;
double LED_ROJO;
double BTN_VERDE;
double LED_AZUL;
double BTN_ROJO;
double LED_AMARILLO;
double BTN_AZUL;
double BUZZER;
double BTN_AMARILLO;
double SW_UP;
double SW_DOWN;
double SW_OK;
double LED_ON;

SoftwareSerial bt_serial(0,7);
Adafruit_SSD1306 oled_1(128,64, &Wire,-1);
static const uint8_t PROGMEM oled_data_0[] PROGMEM = {0xD5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xFD, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC6, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x42, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0E, 0x42, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x92, 0x00, 0x00, 0x06, 0x00, 0x78, 0x0D, 0xE3, 0x41, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x94, 0x92, 0x00, 0x00, 0x1A, 0x00, 0x48, 0x1B, 0xE1, 0xC1, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xDC, 0x00, 0x00, 0xE2, 0x1F, 0xC4, 0x37, 0xCE, 0xC1, 0x84, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0x01, 0x31, 0x84, 0x6F, 0xDE, 0xC0, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x03, 0x20, 0x86, 0x6F, 0xDE, 0xC0, 0x84, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xF8, 0x0C, 0x20, 0x02, 0xC3, 0xBE, 0xC0, 0x04, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x88, 0x10, 0x20, 0x02, 0xDC, 0x3E, 0xC2, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x60, 0x09, 0x90, 0x20, 0x01, 0xDE, 0x3C, 0xC2, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0E, 0x88, 0x20, 0x01, 0xDE, 0xC1, 0xC2, 0x04, 0x04, 0x7C, 0x38, 0x00, 0x01, 0x80, 0x00, 0x83, 0xFC, 0x88, 0x20, 0x00, 0xDE, 0xF1, 0x42, 0x04, 0x04, 0xC4, 0x44, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x88, 0x20, 0x00, 0xDD, 0xF3, 0x43, 0x04, 0x0C, 0x46, 0xC2, 0x00, 0x01, 0x80, 0x00, 0x88, 0x00, 0x88, 0x20, 0x90, 0xCD, 0xF6, 0x47, 0x04, 0x0C, 0x46, 0x82, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x48, 0x20, 0xF8, 0x63, 0xEC, 0x45, 0x04, 0x0C, 0x46, 0x82, 0x00, 0x01, 0x80, 0x00, 0x43, 0xC0, 0x48, 0x10, 0xA8, 0x63, 0xC8, 0x44, 0x84, 0x0C, 0x46, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x45, 0xF0, 0x88, 0x38, 0x30, 0x44, 0x84, 0xCC, 0x46, 0x44, 0x00, 0x01, 0x80, 0x00, 0x18, 0x06, 0x66, 0x30, 0x84, 0x2F, 0xC0, 0x7C, 0xFC, 0xCC, 0x46, 0x38, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x02, 0x60, 0x10, 0x84, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xF1, 0xE0, 0x1F, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xD1, 0x7D, 0xF4, 0x38, 0x01, 0x80, 0x00, 0x00, 0x79, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x11, 0x11, 0x04, 0x24, 0x00, 0x00, 0x00, 0x1F, 0xC1, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x11, 0x11, 0x04, 0x22, 0x01, 0x80, 0x00, 0x10, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xDF, 0x11, 0xE4, 0x22, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x11, 0x04, 0x22, 0x01, 0x80, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x11, 0x04, 0x24, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xD1, 0x7D, 0xF7, 0xB8, 0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void fnc_dynamic_digitalWrite(int _pin, int _e){
  pinMode(_pin,OUTPUT);
  digitalWrite(_pin,_e);
}

int fnc_dynamic_digitalRead(int _pin){
  pinMode(_pin,INPUT);
  return digitalRead(_pin);
}

void setup()
{
  Serial.begin(9600);

bt_serial.begin(9600);

  oled_1.begin(SSD1306_SWITCHCAPVCC,0x3C);

pinMode(6, OUTPUT);
    oled_1.clearDisplay(); oled_1.display();
    oled_1.clearDisplay(); oled_1.drawBitmap(0,0,&oled_data_0[2],oled_data_0[0], oled_data_0[1],WHITE); oled_1.display();
    Serial.println(String("Simon.ino Shield Test-01"));
    
  LED_VERDE = 2;
  LED_ROJO = 3;
  LED_AZUL = 4;
  LED_AMARILLO = 5;
  BUZZER = 6;
  BTN_VERDE = 8;
  BTN_ROJO = 9;
  BTN_AZUL = 10;
  BTN_AMARILLO = 11;
  LED_ON = 13;
  SW_UP = 0;
  SW_DOWN = 1;
  SW_OK = 2;
  
    fnc_dynamic_digitalWrite(LED_VERDE, HIGH);
    TimerFreeTone(6,500,500);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_VERDE, LOW);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_ROJO, HIGH);
    TimerFreeTone(6,800,500);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_ROJO, LOW);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_AZUL, HIGH);
    TimerFreeTone(6,1000,500);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_AZUL, LOW);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_AMARILLO, HIGH);
    TimerFreeTone(6,1200,500);
    delay(1000);
    fnc_dynamic_digitalWrite(LED_AMARILLO, LOW);
    delay(1000);

}


void loop()
{

    if (fnc_dynamic_digitalRead(BTN_VERDE)) {
      fnc_dynamic_digitalWrite(LED_VERDE, HIGH);
      Serial.println(String("Boton Verde"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton Verde")); oled_1.display();
      delay(1000);
      fnc_dynamic_digitalWrite(LED_VERDE, LOW);

    }
    if (fnc_dynamic_digitalRead(BTN_ROJO)) {
      fnc_dynamic_digitalWrite(LED_ROJO, HIGH);
      Serial.println(String("Boton Rojo"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton Rojo")); oled_1.display();
      delay(1000);
      fnc_dynamic_digitalWrite(LED_ROJO, LOW);

    }
    if (fnc_dynamic_digitalRead(BTN_AZUL)) {
      fnc_dynamic_digitalWrite(LED_AZUL, HIGH);
      Serial.println(String("Boton Azul"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton Azul")); oled_1.display();
      delay(1000);
      fnc_dynamic_digitalWrite(LED_AZUL, LOW);

    }
    if (fnc_dynamic_digitalRead(BTN_AMARILLO)) {
      fnc_dynamic_digitalWrite(LED_AMARILLO, HIGH);
      Serial.println(String("Boton Amarillo"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton Amarillo")); oled_1.display();
      delay(1000);
      fnc_dynamic_digitalWrite(LED_AMARILLO, LOW);

    }
/*    if (fnc_dynamic_digitalRead(SW_UP)) {
      fnc_dynamic_digitalWrite(LED_VERDE, HIGH);
      fnc_dynamic_digitalWrite(LED_ROJO, HIGH);
      Serial.println(String("Boton UP"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton UP")); oled_1.display();
      TimerFreeTone(6,1000,500);
      delay(1000);
      fnc_dynamic_digitalWrite(LED_VERDE, LOW);
      fnc_dynamic_digitalWrite(BTN_ROJO, LOW);

    }
    if (fnc_dynamic_digitalRead(SW_DOWN)) {
      fnc_dynamic_digitalWrite(LED_AMARILLO, HIGH);
      fnc_dynamic_digitalWrite(LED_AZUL, HIGH);
      Serial.println(String("Boton Down"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton DOWN")); oled_1.display();
      TimerFreeTone(6,1200,500);
      delay(1000);
      fnc_dynamic_digitalWrite(LED_AMARILLO, LOW);
      fnc_dynamic_digitalWrite(LED_AZUL, LOW);

    }
    if (fnc_dynamic_digitalRead(SW_OK)) {
      fnc_dynamic_digitalWrite(LED_ON, HIGH);
      Serial.println(String("Boton OK"));
      oled_1.clearDisplay(); oled_1.display();
      oled_1.setTextSize(1); oled_1.setTextColor(WHITE); oled_1.setCursor(0,32); oled_1.print(String("Boton OK")); oled_1.display();
      TimerFreeTone(6,1400,500);
      delay(1000);
      fnc_dynamic_digitalWrite(LED_ON, LOW);

    }
*/
}
  
    
