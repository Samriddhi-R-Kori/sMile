int alc = A1;
int led = A4;
int led1 = A5;
int x;
int tx1 = 6;
int tx2 = 10;


void setup() {
  // put your setup code here, to run once:

  pinMode(alc, INPUT);
  digitalWrite(alc, HIGH);
  pinMode(led, OUTPUT);
  analogWrite(led, 0);
  pinMode(led1, OUTPUT);
  analogWrite(led1, 0);
  Serial.begin(9600);
}

void loop()
{
  x = analogRead(alc);
  Serial.println(x);

  if (x > 200 && x < 2000) //low
  {
    digitalWrite(tx1, LOW);//0
    digitalWrite(tx2, HIGH);//1

    analogWrite(led, 0);
    analogWrite(led1, 250);
    delay(500);
    //msg family
  }

   else if (x > 2000) //high
  {
    digitalWrite(tx1, HIGH);//1
    digitalWrite(tx2, LOW);//0
    analogWrite(led1, 0);
    analogWrite(led, 250);
    delay(500);
    //msg family & police with location
  }

  else if (x > 400)
  {

    digitalWrite(tx1, LOW);//0
    digitalWrite(tx2, LOW);//0
    analogWrite(led, 0);
    delay(500);
    analogWrite(led1, 0);
    delay(500);
  }


}
