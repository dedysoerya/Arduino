/*Pembacaan Tag UHF dengan Redaer UHF Midle Range dan Arduino UNO
 * 
 * Wiring
 * UNO to Max3232 to pinDB9 to 
 * UNO  <-----> Max2323  DB9 <----> DB9
 * 5v   <-------->VCC 
 * GND  <-------->GND   5(GND)
 * 2(rx)<-------->RXD   2(rx)
 * 3(tx)<-------->TXD
 * 
 */

#include <SoftwareSerial.h>

const byte rxp=2;
const byte txp=3;

byte password[12] = {0x11,0x11,0x22,0x22,0x33,0x33,0x44,0x44,0x55,0x55,0x66,0x66};

byte panjang, alamat, stat, cmd, Lcrc, Mcrc, pos;
uint16_t crcData,pc;

SoftwareSerial mySerial(rxp,txp);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  mySerial.begin(57600);
  Serial.println("Config finsished");

}

void loop() {
  // put your main code here, to run repeatedly:
  while(mySerial.available()){
    delay(15);
    panjang = mySerial.read();
    Serial.print(panjang,HEX);
    Serial.print(" | ");
    alamat = mySerial.read();
    Serial.print(alamat,HEX);
    Serial.print(" | ");
    cmd = mySerial.read();
    Serial.print(cmd,HEX);
    Serial.print(" | ");
    stat = mySerial.read();
    Serial.print(stat,HEX);
    Serial.print(" | ");
    crcData = mySerial.read() << 8;
    crcData += mySerial.read();
    Serial.print(crcData,HEX);
    Serial.print(" | ");
    pc = mySerial.read()<<8;
    pc += mySerial.read();
    Serial.print(pc,HEX);
    Serial.println(" | ");

    byte data[(panjang-9)];
    for (int i = 0; i<panjang-9; i++){
      data[i] = mySerial.read();
      Serial.print(data[i],HEX);
      Serial.print(" | ");
    }

    prosesData(data, (panjang-9));
    Lcrc = mySerial.read();
    Mcrc = mySerial.read();
  }

}

void prosesData(byte data[],byte panjangData){
  bool pass = compareArray(data,password,panjangData);
  //bool pass= 1;
  if(pass){
    Serial.println("Tag sudah terdaftar");
  }
  else{
    Serial.println("Tag belum terdaftar"); 
  }
}

bool compareArray(byte array1[],byte array2[],byte panjangData){
  bool pass = true;
  for(int i = 0; i < panjangData; i++){
    if (array1[i] != array2[i]){
      pass = false;
      break;
    }
  }
  return pass;
}
