#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define coinSlot 6
#define coinSlotRGBFrame 2
#define buzzer 13
#define button 4
#define pumpMotor 3

int coinSlotStatus;
int pulse;

boolean userBalance = false;
boolean noCoin = false;

char lcdBuffer[16];

int buttonState;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(buzzer, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(coinSlot, INPUT_PULLUP);
  pinMode(coinSlotRGBFrame, OUTPUT);
  pinMode(button, OUTPUT);
  pinMode(pumpMotor, OUTPUT);

  tone(buzzer, 262);
  delay(150);
  tone(buzzer, 294);
  delay(150);
  tone(buzzer, 330);
  delay(150);
  tone(buzzer, 349);
  delay(150);
  tone(buzzer, 392);
  delay(150);
  tone(buzzer, 440);
  delay(150);
  tone(buzzer, 494);
  delay(150);
  tone(buzzer, 563);
  delay(150);
  noTone(buzzer);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!noCoin){
    noCoin = true;
    lcd.setCursor(0, 0);
    lcd.print("   INSERT COINS");
    digitalWrite(coinSlotRGBFrame, HIGH);
  }

  buttonState = digitalRead(button);
  if(buttonState == 1 && pulse > 0 && userBalance){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pumping Liquid");

    for (int i = pulse; i > 0; i--) {
      analogWrite(pumpMotor, 255);
      lcd.setCursor(0, 1);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print(i);
      tone(buzzer, 523);
      delay(500);
      noTone(buzzer);
      delay(500);
    }
    analogWrite(pumpMotor, 0);

    pulse = 0;
    noCoin = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Thank You! Bye!");
    delay(1700);
    tone(buzzer, 3000);
    delay(200);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 3000);
    delay(50);
    noTone(buzzer);
  }  

  coinSlotStatus = digitalRead(coinSlot);
  delay(30);
  if (coinSlotStatus == 0) {
  digitalWrite(coinSlotRGBFrame, LOW);
  tone(buzzer, 2000);
  userBalance = true;
  lcd.setCursor(0, 0);
  lcd.print("Press a Button");
  pulse +=1;
  sprintf(lcdBuffer, "Bal. Php %d.00", pulse);
  lcd.setCursor(0, 0);
  lcd.print(lcdBuffer);
  delay(30);
  }
  noTone(buzzer);
}
