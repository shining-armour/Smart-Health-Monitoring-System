#define USE_ARDUINO_INTERRUPTS true
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.

String APIKEY = "PZSIOY00O197S6XY" ;
String SSID = "XXXXXXXX"  ;   // "SSID-WiFiname"
String PASS =  "XXXXXXXX"; // "Wi-Fi password"
String IP =  "184.106.153.149"    ;  // thingspeak.com IP Address

// Variables
const int PulseWire = A0; 
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;
String BPM;
String temp;             

// Instances
SoftwareSerial esp8266(2,3);      // arduino RX pin=2  arduino TX pin=3   
PulseSensorPlayground pulseSensor;
LiquidCrystal lcd(8,9,10,11,12,13);

byte degree[8] =
{
0b00011,
0b00011,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

//=====================================Sending BPM to ThingSpeak===========================================//
void thingSpeakWrite(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
  cmd += IP;                               // api.thingspeak.com
  cmd += "\",80";
  Serial.println(cmd);
  esp8266.println(cmd); 
  
  if(esp8266.find("Error")){
    Serial.println("AT+CIPSTART error");
    return false;
  }
  
  String getStr = "GET /update?api_key=";   // prepare GET string
  getStr += APIKEY;
  getStr +="&field1=";
  getStr += BPM;
  getStr +="&field2=";
  getStr += temp;
  getStr += "\r\n\r\n";
  
  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  esp8266.println(cmd);
  Serial.println(cmd);
  delay(80);
  
  if(esp8266.find(">")){
    esp8266.print(getStr);
    Serial.print(getStr);
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}


//====================================Doing the Setup=======================================================//

void setup() {                
  Serial.begin(9600); // enable software serial     
  esp8266.begin(115200);                      
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);

  lcd.begin(16,2);
  lcd.createChar(1, degree);
  lcd.setCursor(0,0);
  lcd.print(" Health Monitor");
  lcd.setCursor(0,1);
  lcd.print("    System    ");
  delay(2000);
  
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

//NOTE: For running the code first time uncomment the following lines//

/*esp8266.println("AT+RST");         // Enable this line to reset the module;
  delay(2000);*/


  if(esp8266.available()){
    connectWifi();
  }
  else{
    Serial.println("Wi-Fi Connection Error!");
  }
  
}

//====================================Connecting to Wi-Fi=====================================================//
boolean connectWifi(){
  Serial.println("AT");
  esp8266.println("AT");
  delay(4000);
  
  Serial.println("AT+CWMODE=1");
  esp8266.println("AT+CWMODE=1");   // set esp8266 as client
  delay(2000);
    //showResponse(1000);

  Serial.println("AT+CWJAP=\""+SSID+"\",\""+PASS+"\"");
  esp8266.println("AT+CWJAP=\""+SSID+"\",\""+PASS+"\"");  // set your home router SSID and password
  delay(5000);
    //showResponse(5000);
  if(esp8266.find("OK")){  
    Serial.println("Setup completed");
    return true;
  }
  else{
    return false;
  }
}

//====================================Looping through the readings============================================//
void loop() {
   float reading=analogRead(A1);
   float tempC=reading*(5.0/1023.0)*100;
   float tempF = (tempC * 9.0 / 5.0) + 32.0;
   char buffer1[10];
   char buffer2[10];
    
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int". "myBPM" hold this BPM value now. 
    
   if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   Serial.println("A beat happened");
    }
   delay(20); 
   BPM = dtostrf(myBPM, 4, 1, buffer1);
   temp = dtostrf(tempF, 4, 1, buffer2);// Print the value inside of myBPM. 

    if (isnan(tempF)) {
      Serial.println("Failed to read from Temperature sensor");
      }
    else{
      Serial.println("BPM="+String(BPM)+" BPM");
      Serial.println("Temp="+String(temp)+" *F");
      thingSpeakWrite(); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("BPM :");
      lcd.setCursor(7,0);
      lcd.print(myBPM);
      lcd.setCursor(0,1);
      lcd.print("Temp.:");
      lcd.setCursor(7,1);
      lcd.print(temp);
      lcd.setCursor(13,1);
      lcd.print(" F");
    }
  //thingspeak needs 15 sec delay between updates,     
  delay(15000);  
}
