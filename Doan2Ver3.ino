
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <DHT.h>

#include <DFRobotDFPlayerMini.h>
#include "SoftwareSerial.h"

SoftwareSerial mySoftwareSerial(3, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

LiquidCrystal_I2C lcd(0x27, 20, 4);
#define BLYNK_PRINT Serial   // Comment this out to disable prints and save space 

#define in 12 //Chân 12 là chân người vào
#define out 13 //Chân 13 là chân người ra
#define relay 5 //Chân còi báo

//thingspeak
      
const char* ssidd = "Wifi Free DUT";           // Give your wifi network name
const char* passwordd = "muoiso10";   // Give your wifi network password


WiFiClient client;
//ThingSpeakSetting
const int channelID    = 1257322;// Enter Channel ID;
String writeAPIKey    = "YMB1SNCG6XJ86ET7";
const char* server    = "api.thingspeak.com";

void    wifiSetup();
void    thingConnect();
void    readSensor(void);
//float   getMoist();
void    printData(void);

#define DHTTYPE DHT11
#define DHTPIN 4 //Chân 4 là DHT
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float humi; 
float temp;
int c;

char auth[] = "58KE-oK65ay5v27Ntx6cDC9XuXt3MD0E";
char ssid[] = "Wifi Free DUT";
char pass[] = "muoiso10";


int count = 0; //biến đếm người

void thingConnect() {
  if (client.connect(server, 80)) {
    String body = "field1=" + String(temp, 1) + "&field2=" + String(humi, 1) + "&field3=" + String(count);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");
  }
}
void wifiSetup() {
  Serial.print("Connecting");
  WiFi.begin(ssidd, passwordd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("\r\nWiFi connected");
//  logoConsole();
}

void printData(void) {
  Serial.printf("Temp: %s°C - Hum: %s% - Moist: %s%\r\n", String(temp, 1).c_str(), String(humi, 1).c_str(), String(count, 1).c_str());
}

void readSensor(void) {
  temp  = dht.readTemperature();
  humi  = dht.readHumidity();
  //int c = count;
  
//---------------------------------------------------------------------------------//  \n");
}
void IN()
{
    count++;
    lcd.setCursor(0,1);
    lcd.print("So nguoi: ");
    lcd.print(count);
    lcd.setCursor(10,1);
    Serial.print("So nguoi: ");
    Serial.println(count); 
    delay(500);
}
void OUT()
{
    if (count == 0)
    {
      count == 0;
      lcd.setCursor(0,1);
      lcd.print("So nguoi: ");
      lcd.print(count);
      lcd.setCursor(10,1);
      Serial.println("Khong co nguoi: ");
      delay(500);
    }
    else 
    {  
    count--;
    lcd.setCursor(0,1);
    lcd.print("So nguoi: ");
    lcd.print(count);
    lcd.setCursor(10,1);
    Serial.print("So nguoi: ");
    Serial.println(count);
    delay(500);
    } 
}

void Demsonguoi()
{
  
  int readVao = digitalRead(in); // CẢM BIẾN vào
  int readRa  = digitalRead(out); // CẢM BIẾN ra

   //Dem nguoi
  if(readVao == LOW)
  IN();
  if(readRa == LOW)
  OUT();
  if (count == 0)
  Serial.println("Khong co nguoi");
  if (count >=10) 
  quasonguoi();
  
  Blynk.virtualWrite(V0, count);
}

void quasonguoi()
{
    Serial.println("Qua so nguoi ");
    Blynk.notify("Quá số người quy định!");
       
    myDFPlayer.play(1);
    delay(3000);
 
    lcd.setCursor(0,1);
    lcd.print("WARNING!!");
    lcd.print(count);
    lcd.print("    ");
    
}

void Nhietdo()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
    lcd.setCursor(0,2);
    lcd.print("Nhiet do: ");
    lcd.print(t);
    lcd.print((char)0xDF);
    lcd.print("C");
    lcd.setCursor(0,3);
    lcd.print("Do am   : ");
    lcd.print(h);
    lcd.print(" %");
      
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t); 
}
   
void setup()
{
  Serial.begin(9600);
  Serial.println("Dang chay vong SETUP");
  

  //Bắt đầu 2 chân SDA và SCK của I2C và khởi tạo LCD
  Wire.begin(2, 0); // SDA SCL
  lcd.init();                 
  lcd.backlight();  
  lcd.home();
  lcd.setCursor(0,0);//Đưa con trỏ về vị trí 0,0
  lcd.print("MAX     : 50 nguoi");
 
  //Bat dau DHT
  dht.begin();
  wifiSetup();
  
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(relay, OUTPUT);
  
  //Bat dau Blynk
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(500L,Nhietdo);
  timer.setInterval(500L,Demsonguoi);

  //Bat dau mp3
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {  while(true){delay(0); }   }
  myDFPlayer.volume(20); 
  
}

void loop()
{
  Serial.println("Dang trong vong LOOP");
  Blynk.run();
  timer.run();
  
  thingConnect();
  readSensor();
  printData();
  
  Demsonguoi();
  Nhietdo();
}
