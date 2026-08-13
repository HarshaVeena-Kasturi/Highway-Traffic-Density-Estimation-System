#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define TRIG1 5
#define ECHO1 18

#define TRIG2 17
#define ECHO2 16

#define TRIG3 4
#define ECHO3 2

#define GREEN 25
#define YELLOW 26
#define RED 27
#define BUZZER 14

float getDistance(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo,HIGH);
  return duration * 0.034 / 2;
}

void setup()
{
  pinMode(TRIG1,OUTPUT);
  pinMode(ECHO1,INPUT);

  pinMode(TRIG2,OUTPUT);
  pinMode(ECHO2,INPUT);

  pinMode(TRIG3,OUTPUT);
  pinMode(ECHO3,INPUT);

  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);

  pinMode(BUZZER,OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  float d1 = getDistance(TRIG1,ECHO1);
  float d2 = getDistance(TRIG2,ECHO2);
  float d3 = getDistance(TRIG3,ECHO3);

  int count = 0;

  if(d1 < 30) count++;
  if(d2 < 30) count++;
  if(d3 < 30) count++;

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Vehicles:");
  lcd.print(count);

  lcd.setCursor(0,1);

  if(count == 0)
  {
    lcd.print("No Traffic");
    digitalWrite(GREEN,HIGH);
    digitalWrite(YELLOW,LOW);
    digitalWrite(RED,LOW);
    digitalWrite(BUZZER,LOW);
  }

  else if(count == 1)
  {
    lcd.print("Low Traffic");
    digitalWrite(GREEN,HIGH);
    digitalWrite(YELLOW,LOW);
    digitalWrite(RED,LOW);
    digitalWrite(BUZZER,LOW);
  }

  else if(count == 2)
  {
    lcd.print("Medium");
    digitalWrite(GREEN,LOW);
    digitalWrite(YELLOW,HIGH);
    digitalWrite(RED,LOW);
    digitalWrite(BUZZER,LOW);
  }

  else
  {
    lcd.print("HIGH TRAFFIC");
    digitalWrite(GREEN,LOW);
    digitalWrite(YELLOW,LOW);
    digitalWrite(RED,HIGH);
    digitalWrite(BUZZER,HIGH);
  }

  delay(1000);
}
