/*Sound Identifier turunan project dari deteksi tangisan bayi. 
Pada project ini menggunakan board nodemcu dan sensor ky-037
*/

int led = 13; // bisa diganti d7
int sound_digital = 4; // bisa diganti d2 sesuai kabel ke arah do mic
int sound_analog = A0; //output analog sensor suara
int sound_dig = 500; // batas terendah 
boolean playing = 0;
unsigned long timeAnalisis = 0;
unsigned long time_low = 0;
unsigned long time_high = 0;
unsigned long waktuselisih = 0;
unsigned long timeNow = 0;
unsigned long startTime, startLow, rangeLow, startHigh, changeLow;
unsigned long currentTime;
unsigned long playing_time;
unsigned long playingdelay;
unsigned long rangegelombang, rangeHigh;
boolean sinyalLow;
boolean sinyalHigh;
boolean gel=0;
boolean prev_gel=0;
int prev_val = 553;
int range = 0;
int analisis = 0;
int analising = 0;
int hitungGelombang = 0;
int selisihrentang = 0;
unsigned long panjangGelombang = 0;
long g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13,g14,g15,g16,g17,g18,g19,g20;

const long lamaAnalisis = 10000;
const long periodeNormal = 500;

void setup(){
  Serial.begin(9600);
  pinMode(sound_digital, INPUT);
  startTime = millis();  
}

void loop(){
  int val_digital = digitalRead(sound_digital);
  int val_analog = analogRead(sound_analog);
  range = val_analog - prev_val;
  prev_val = val_analog;
  //kirim data suara normal tiap periode waktu tertentu(sesuai nilai periodeNormal)
  currentTime = millis();
  if (currentTime - startTime >= periodeNormal){
    Serial.print(val_analog);
    Serial.print("\t");
    Serial.print(sound_dig);
    Serial.print("\t");
    Serial.println(val_digital);
    startTime = currentTime;
    
  }
 
  //trigering
  if (range > 7){
      time_high = millis();
      playing_time = millis();
      sound_dig = 600;
      playing = 1;
      gel = 1;
      sinyalLow = 0;
      sinyalHigh = 1;
      
      while(playing){
        val_digital = digitalRead(sound_digital);
        val_analog = analogRead(sound_analog);
        range = val_analog - prev_val;
        prev_val = val_analog;
        
        
        if(range>5){
          time_high = millis();
          playing_time = millis();
          sound_dig = 600;
          gel = 1;
          sinyalLow = 0;          
        }


        
        Serial.print(val_analog);
        Serial.print("\t");
        Serial.print(sound_dig);
        Serial.print("\t");
        Serial.println(val_digital);
        delay(10);

        if(val_digital == LOW){
          time_low = millis();
          if (!sinyalLow){
            startLow = millis();
            sinyalLow = 1;
          }
          rangeLow = time_low - startLow;
          waktuselisih = time_low - time_high;
          playingdelay = time_low - playing_time;
          
          if (rangeLow > 100){
            changeLow = millis();
            sound_dig = 500;
            if (gel != prev_gel){
              hitungGelombang +=1;
              //prev_gel = gel;
              Serial.print("Gelombang Ke-");
              Serial.println(hitungGelombang); 
              
              }
            
            gel=0;
            Serial.print("Gelombang Ke-");
            Serial.println(hitungGelombang);            
          }
          if( playingdelay > 3000){
            playing=0;
            Serial.println("Jumlah Gelombang = ");
            Serial.println(hitungGelombang);
            hitungGelombang = 0;
          }
         }     
        }
      }

}
