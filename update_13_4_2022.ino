#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>

#define relay1 9
#define relay2 1
#define relay3 2

tmElements_t tm;

int count = 0;
int start_f = 0;
uint16_t start_l_f = 0;
uint16_t start_l_l = 0;



void setup() {

  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  delay(5000);
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

reset();

//210 to 300s
uint16_t cur_ho = tm.Hour;

if ( cur_ho == 0)
{
  int random_h = random(1, 18);
  int random_m = random(1, 59);
  start_f = random(10, 30);
  start_l_f = random(210, 255);
  start_l_l = random(0,45 );

  EEPROM.write(1, random_h);
  EEPROM.write(0, random_m);
  EEPROM.write(2, start_f);
  EEPROM.write(3, start_l_f);
  EEPROM.write(4, start_l_l);

   
}


uint16_t set_h = EEPROM.read(1) * 60;
uint16_t set_m = EEPROM.read(0);
uint16_t set_time = set_h + set_m;
uint16_t cur_h = tm.Hour * 60;
uint16_t cur_m = tm.Minute;
uint16_t cur_time = cur_h + cur_m;

uint16_t first_cycle = EEPROM.read(2);
uint16_t second_cycle = EEPROM.read(3) + EEPROM.read(4);

if (cur_time >= set_time and cur_time <= set_time + first_cycle)
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
}

else if (cur_time > set_time + 10 and cur_time <= set_time + second_cycle)
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



void reset()
{
  if(digitalRead(3) == LOW)
{
  count += 1;
  if (count >=2)
  {
    count = 0;
    EEPROM.write(0,tm.Minute);
    EEPROM.write(1,tm.Hour);
    
    start_f = random(10, 30);
    start_l_f = random(210, 255);
    start_l_l = random(0,45 );
    
    EEPROM.write(2, start_f);
    EEPROM.write(3, start_l_f);
    EEPROM.write(4, start_l_l);
    
    digitalWrite(8,HIGH);
    delay(5000);
    digitalWrite(8,LOW);
  }
}
}
