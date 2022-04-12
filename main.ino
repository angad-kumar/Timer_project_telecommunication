#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>

#define relay1 1
#define relay2 2
#define relay3 9

tmElements_t tm;

int count = 0;

void setup() {

  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(8,LOW);

  pinMode(3,INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

void loop() {
if (RTC.read(tm)) {
}
else {
  if (RTC.chipPresent()) {
    digitalWrite(8,HIGH);
    delay(1000);
    digitalWrite(8,LOW);
    delay(1000);
  } else {
    digitalWrite(8,HIGH);
    delay(1000);
    digitalWrite(8,LOW);
    delay(1000);
  }
  delay(9000);
}
delay(1000);


if(digitalRead(3) == LOW)
{
  count += 1;
  if (count >=2)
  {
    count = 0;
    EEPROM.write(0,tm.Minute);
    EEPROM.write(1,tm.Hour);
    digitalWrite(8,HIGH);
    delay(5000);
    digitalWrite(8,LOW);
  }
}

uint16_t set_h = EEPROM.read(1) * 60;
uint16_t set_m = EEPROM.read(0);
uint16_t set_time = set_h + set_m;
uint16_t cur_h = tm.Hour * 60;
uint16_t cur_m = tm.Minute;
uint16_t cur_time = cur_h + cur_m;

if (cur_time >= set_time and cur_time <= set_time + 10)
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
}

else if (cur_time > set_time + 10 and cur_time <= set_time + 310)
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
}

else
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

  delay(200); 
}
