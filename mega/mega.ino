/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/

String buff;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("setting mode");
  
  Serial2.write("AT\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);
  
  Serial2.write("AT+CWMODE_DEF=2\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);

  Serial2.write("AT+CWSAP_DEF=\"ESP8266\",\"1111111111\",5,4\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);

  Serial2.write("AT+CIFSR\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);

  Serial2.write("AT+CIPMUX=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);

  Serial2.write("AT+CIPSERVER=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);

  Serial2.write("AT+CIPDINFO=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(100);
  
  //Serial2.write("AT+CWLAPOPT\r\n");
  //delay(1000);
  //Serial2.write("AT+CIPSTART=\"TCP\",\"192.168.43.204\",2333\r\n");

}

void loop() {

  //Serial2.write("AT+CWLIF\r\n");
  if(Serial2.available()){
    buff = Serial2.readString();
    Serial.println(buff);
    parseRaw(buff);
  };

}

int parseRaw(String s) {
   if(s[0] == '0')  return 0;
   if(s[0] == '+') {
    int i = 0;
    while(s[i] != ':') {
      ++i;
    }
    Serial.println(i);
    s = s.substring(i,s.length());
    Serial.println(s);
   }
}

