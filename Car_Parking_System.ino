
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //Change the HEX address
#include <Servo.h>

Servo myservo1;

int Green_led = 5;
int Red_led = 6;

int IR1 = 2;
int IR2 = 4;

int Slot = 4;           //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  pinMode(Green_led, OUTPUT);
  pinMode(Red_led, OUTPUT);


  myservo1.attach(3);
  myservo1.write(90);

  lcd.setCursor (0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor (0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay (2000);
  lcd.clear();
}

void loop() {

  if (digitalRead (IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      digitalWrite(Red_led, LOW);
      digitalWrite(Green_led, HIGH);
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);
        Slot = Slot - 1;
        
      }
    }

    else {
      digitalWrite(Red_led, HIGH);
      digitalWrite(Green_led, LOW);
      lcd.setCursor (0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor (0, 1);
      lcd.print("  Parking Full  ");
      lcd.clear();
    }
  }

  if (digitalRead (IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0);
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay (1000);
    myservo1.write(90);
    flag1 = 0, flag2 = 0;
  }

  lcd.setCursor (0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor (0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);

    }
