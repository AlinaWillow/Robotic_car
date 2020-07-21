#include "IRremote.h"

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
int pv, v;

//Infrared sensor
const int pingPin = 13; // Trig
int inPin = 12; //Echo

void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT); //left
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); //right
  pinMode(7, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  

  
}

void loop() {
  readremote();
  infra();
}

void m(int a, int b) {

  if (a == 1 && b == 1) {
    digitalWrite(4, 1);
    digitalWrite(5, 0);

    digitalWrite(6, 1);
    digitalWrite(7, 0);
  }

  if (a == 2 && b == 2) { //ถอยหลัง
    digitalWrite(4, 0);
    digitalWrite(5, 1);

    digitalWrite(6, 0);
    digitalWrite(7, 1);
  }

  if (a == 1 && b == 0) {
    digitalWrite(4, 1);
    digitalWrite(5, 0);

    digitalWrite(6, 0);
    digitalWrite(7, 0);
  }

  if (a == 0 && b == 1) {
    digitalWrite(4, 0);
    digitalWrite(5, 0);

    digitalWrite(6, 1);
    digitalWrite(7, 0);
  }

  if (a == 1 && b == 2) {
    digitalWrite(4, 1);
    digitalWrite(5, 0);


    digitalWrite(6, 0);
    digitalWrite(7, 1);
  }

  if (a == 2 && b == 1) {
    digitalWrite(4, 0);
    digitalWrite(5, 1);

    digitalWrite(6, 1);
    digitalWrite(7, 0);
  }
  if (a == 0 && b == 0) {
    digitalWrite(4, 0);
    digitalWrite(5, 0);


    digitalWrite(6, 0);
    digitalWrite(7, 0);
  }
}
void readremote() {
  if (irrecv.decode(&results)) {
    int v = results.value;
    if (v == -1) {
      v = pv;
    }

    Serial.println(v);
    if (v == 25245 || v == 7611) { //ปุ่มบน
      m(1, 1);
    }
    if (v == 8925 || v == -11233) { //ปุ่มซ้าย
      m(1, 2);
    }
    if (v == 19899 || v == -15811) { //ปุ่มขวา
      m(2, 1);
    }
    if (v == -22441 || v == -4645) { //ปุ่มล่าง
      m(2, 2);
    }
    if (v == 765 || v == 19227) { //ปุ่ม OK
      m(0, 0);
    }    
    pv = v;
    irrecv.resume(); // Receive the next value
  }
}

void infra(){
  
  long duration, cm;

pinMode(pingPin, OUTPUT);


digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(5);
digitalWrite(pingPin, LOW);
pinMode(inPin, INPUT);
duration = pulseIn(inPin, HIGH);

cm = microsecondsToCentimeters(duration);

int x;

if (cm <= 10){
  
    m(2, 2);
    delay(500);
    m(0,0);
}
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
