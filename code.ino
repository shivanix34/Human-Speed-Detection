#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int sensorA = 3;
int sensorB = 2;
unsigned long t1 = 0;
unsigned long t2 = 0;
float speed;
const unsigned long interval = 500;
unsigned long previousMillis = 0;
bool motionDetected = false;

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print(" DNP project");
  delay(3000);
  lcd.clear();
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Human Speed");
  lcd.setCursor(0, 1);
  lcd.print("Measurement");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // Forward direction measurement
    if (!motionDetected) {
      while (digitalRead(sensorA));
      while (digitalRead(sensorA) == 0);
      t1 = millis();
      while (digitalRead(sensorB));
      t2 = millis();
      motionDetected = true;

      calculateSpeed(t1, t2);
      displaySpeed(speed, "F");
    }
    else {
      motionDetected = false;

      // Opposite direction measurement
      while (digitalRead(sensorB));
      while (digitalRead(sensorB) == 0);
      t1 = millis();
      while (digitalRead(sensorA));
      t2 = millis();

      calculateSpeed(t1, t2);
      displaySpeed(speed, "R");
    }
  }
}

void calculateSpeed(unsigned long t1, unsigned long t2) {
  speed = t2 - t1;
  speed = speed / 1000;
  speed = (0.15 / speed);
  speed = speed * 3600;
  speed = speed / 1000;
}

void displaySpeed(float speed, String direction)
{
  for (int i = 5; i > 0; i--)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Human speed (");
    lcd.print(direction);
    lcd.print(") = ");
    lcd.setCursor(3, 1);
    lcd.print(speed);
    lcd.print(" km/hr   ");
    delay(500);
    lcd.setCursor(3, 1);
  }
}