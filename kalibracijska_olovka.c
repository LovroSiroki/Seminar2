#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int btn=0;
int i=1;
boolean bp=false;
boolean bnp=false;
void setup() {
  pinMode(5,INPUT);
  pinMode(4, OUTPUT);
  pinMode(32, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("Kalibracijska olovka");
  Serial.println("Uređaj je spreman za korištenje!");
  digitalWrite(32, HIGH);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  if (SerialBT.connected()) {
    if(i<=400){
      if(i<20){
        digitalWrite(32, HIGH);}
      else {
        digitalWrite(32, LOW);}
    }
    i++;
    delay(7);
    if(i==400){
      i=1;}
  }  
  btn = digitalRead(5);
  if (btn==HIGH) {
    bnp=false;
    if (!bp){
      digitalWrite(4, HIGH);
      SerialBT.write('P');
      SerialBT.write('\n');
      Serial.write("button pressed\n");
      delay(10);
      bp=true;}
  }
  if (btn==LOW) {
    bp=false;
    if (!bnp){
      digitalWrite(4, LOW);
      SerialBT.write('N');
      SerialBT.write('\n');
      Serial.write("button released\n");
      delay(10);
      bnp=true;}
  }
  delay(10);
}
