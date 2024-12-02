#include <LiquidCrystal.h>
char ble; //to read bluetooth
int bsl =A3 ; //bike start led

int trigPin = 8;
int echoPin = 9;
long duration;
int d;
int nm = 10; //find exact distance with angle
int buzz = A0;

int s1 = 13;
int s2 = 7;
int y;
int z;
//led just to chk switches
int l1 = A1;
int l2 = A2;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int r1, r2;
int rx1 = 6;
int rx2 = 10;
void start();
int key=0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
 
  pinMode(s1, INPUT);
  digitalWrite(s1, HIGH);
  pinMode(s2, INPUT);
  digitalWrite(s2, HIGH);
  pinMode(l1, OUTPUT);
  digitalWrite(l1, LOW);
  pinMode(l2, OUTPUT);
  digitalWrite(l2, LOW);
  pinMode(bsl, OUTPUT);
  digitalWrite(bsl, LOW);

  pinMode(rx1, INPUT);
  digitalWrite(rx1, HIGH);
  pinMode(rx2, INPUT);
  digitalWrite(rx2, HIGH);

  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  //chk for helmet. if true=start bike & run below processes
  //if false= do not start bike
  //if bluetooth signal sent=0(true)-start bike
  //if bluetooth signal sent=1(false)-dont start bike
  //bluetooth read=ble
  while(key==0)
  {
  start();
  }
  while (1)
 {
  Serial.println("started");
    //ALCHOL
    r1 = digitalRead(rx1);
    r2 = digitalRead(rx2);
    if (r1 == 0 && r2 == 1) //minor
    {
      //message family
      Serial.println("msg family");
    }
    else if (r1 == 1 && r2 == 0) //major
    {
      //message police and family
      Serial.println("msg police & family");
    }
    else if (r1 == 0 && r2 == 0)
    {
      //do nothing.
      Serial.println("do nothing");
    }

    //ULTRASONIC DISTANCE SENSOR
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    d = duration * 0.034 / 2;
    lcd.setCursor(0, 1);
    lcd.print("d= ");
    lcd.print(d);

    lcd.setCursor(5, 0);
    if (d > nm) //pothole
    {
      digitalWrite(buzz, HIGH);
      delay(100);
      digitalWrite(buzz, LOW);
      delay(100);
      lcd.print("pothole");
      delay(500);
    }
    else if (d < nm) //hump
    {
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
      lcd.print("hump");
      delay(500);
    }
    else if (d == nm)
    {
      digitalWrite(buzz, LOW);
    }

    //SWITCHES - accident
    y = digitalRead(s1);
    z = digitalRead(s2);

    if (y == 0) //minor
    {
      //just to chk-led
      digitalWrite(l1, HIGH);
      delay(500);
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      Serial.println("major accident");
      //msg family with location
    }
    else if (z == 0) //major
    {
      //just to chk-led
      digitalWrite(l2, HIGH);
      delay(500);
      digitalWrite(l2, LOW);
      digitalWrite(l1, LOW);
      Serial.println("minor accident");
      //msg family police & ambulance with location
    }
    else
    {
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
    }
  }}//close func

  void start()
  {
    if (Serial.available())
    {
      ble = Serial.read();
      Serial.println(ble);

      if (ble == 's')
      {
        //Serial.print("started the bike");
        key=1;
        digitalWrite(bsl, HIGH);
        delay(500);
       

        //chk for helmet. if true=start bike & run below processes
        //if false= do not start bike
        lcd.setCursor(0, 0);
        lcd.clear();
      }
      else if (ble == 1)
      {
        key=1;
        lcd.print("wear your helmet");
      }
    }
  }
