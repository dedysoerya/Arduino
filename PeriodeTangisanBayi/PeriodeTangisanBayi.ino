int led = 13; // bisa diganti d7
int sound_digital = 4; // bisa diganti d2 sesuai kabel ke arah do mic
int sound_analog = A0;
int sound_dig = 500;
int prev_valAnalog = 553;
boolean trigered = 0;
unsigned long time_low = 0;
unsigned long time_high = 0;
unsigned long waktuselisih = 0;

void setup(){
  Serial.begin(9600);
  //pinMode(led, OUTPUT);
  pinMode(sound_digital, INPUT);  
}

void loop(){
  int val_digital = digitalRead(sound_digital);
  int val_analog = analogRead(sound_analog);
  int rangeSensor = val_analog - prev_valAnalog;
  prev_valAnalog = val_analog;

  if (rangeSensor > 10){
      trigered = 1;
      time_high = millis();
      sound_dig = 600;  
     }
  
  if(trigered){
      sound_dig = 600;
      if(val_digital == LOW){
        time_low = millis();
        waktuselisih = time_low - time_high;
        if (waktuselisih > 175){
          sound_dig = 500;
          trigered = 0;
        }
      }
   }
   
  Serial.print(val_analog);
  Serial.print("\t");
  Serial.print(sound_dig);
  Serial.print("\t");
  Serial.println(val_digital);
  delay(10);
 
  
  //Serial.println(switch_time);
}
