#include <LiquidCrystal.h>
#include <EEPROM.h>
int fsrPin = A0;
int fsrValue = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int addr = 0;
byte value;

int sensorPin = A1;
double alpha = 0.75;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Heartbeat measurement!");
  Serial.begin(9600);
}

void loop() {
  fsrValue = analogRead(fsrPin);
  if (fsrValue > 20){
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        byte value = EEPROM.read(i);                //read EEPROM data at address i
        if(value != 0) {
            float temp = value;
            lcd.clear();
            lcd.setCursor(0,1);
            Serial.println(temp);
            lcd.print(temp);
            lcd.setCursor(0,0);
            lcd.print("Printing heartbeat!");
        }
        delay(1000);
      }
  } else{
    int rawValue = analogRead(sensorPin);
    Serial.println(rawValue);
    EEPROM.write(addr, rawValue);
    addr = addr + 1;
    if (addr == EEPROM.length()){
      addr = 0;
    } 
    delay(1000);
  }
}
