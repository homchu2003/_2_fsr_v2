
#include <SPI.h>
#include <Wire.h>
#include <Math.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <ArduinoJson.h>

const int nFSRs = 1;
int fsrPin = 0; 
int FSR_SAMPLE[nFSRs]={0};
int i = 0;
char ctrlCMD = 0;

void SCAN_FSRS(){
  for(i=2; i<3; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);

    FSR_SAMPLE[i-2] = analogRead(A0);
    pinMode(i,INPUT);

  }
  
}

void encode_BYTES(int fsr[]) {
 // this function would send the raw bytes of data
 // DO NOTHING 
}
void encode_JONS(int fsr[]) {

  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& fsr_arr = root.createNestedArray("fsr");
  for (unsigned i = 0; i < nFSRs; i++)
  {
   fsr_arr.add(fsr[i]);  // 6 is the number of decimals to print   
  }


  printJSON(root);
}

void printJSON(JsonObject& root)
{
    // The ## are used as marker of the sended string
    Serial.print('#');
    Serial.print('#');
    root.printTo(Serial);
    Serial.print('\n');
}


void serialFlush()
{
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
   // put your main code here, to run repeatedly:
   Serial.flush();
 
   if (Serial.available())  {
       ctrlCMD = Serial.read();
 
       if ((ctrlCMD == 'b'||ctrlCMD == 'd'))    
       {
        Serial.println(ctrlCMD);
        serialFlush();
       }
       switch (ctrlCMD) {
         case 'b':
           SCAN_FSRS(); encode_BYTES(FSR_SAMPLE);
           break;
         case 'd':
            SCAN_FSRS(); encode_JONS(FSR_SAMPLE);
           break;
       }
     
   }
   
}


