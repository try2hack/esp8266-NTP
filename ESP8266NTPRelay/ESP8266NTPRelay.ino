#include <ESP8266WiFi.h>
#include <time.h>
#include <TridentTD_LineNotify.h>

#define D0 16
#define LED D0

const char* ssid = "testbug"; //ใส่ชื่อ SSID Wifi
const char* password = ""; //ใส่รหัสผ่าน
const char* LINE_TOKEN = "lArNLNaLtifPccIUU1kTjNMv5mQ3VbFnOScqBLpF6GG";

int timezone = 7 * 3600; 
int dst = 0; //กำหนดค่า Date Swing Time

void setup()
{
Serial.begin(115200);
pinMode(LED,OUTPUT); // setup output
Serial.println(LINE.getVersion());
LINE.setToken(LINE_TOKEN);
WiFi.mode(WIFI_STA); //เชื่อมต่อ Wifi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("*");
delay(1000);
}
configTime(timezone, dst, "pool.ntp.org", "time.nist.gov"); //ดึงเวลาจาก Server
Serial.println("\nLoading time");
while (!time(nullptr)) {
Serial.print("*");
delay(1000);
}
Serial.println("");
}

void loop()
{
//configTime(timezone, dst, "pool.ntp.org", "time.nist.gov"); //แสดงเวลาปัจจุบัน
time_t now = time(nullptr);
struct tm* p_tm = localtime(&now);

Serial.print(p_tm->tm_hour);
Serial.print(":");
Serial.print(p_tm->tm_min);
Serial.print(":");
Serial.print(p_tm->tm_sec);
if((p_tm->tm_min%2) == 0 && (p_tm->tm_sec)== 0)
  {  
  digitalWrite(LED,LOW); // Pin D0 is HIGH
  Serial.println(" on");
  LINE.notify("เปิด");
  delay(30000);
  
  digitalWrite(LED,HIGH); // Pin D0 is LOW
  Serial.println(" off");
  LINE.notify("ปิด");
  delay(1000);                        
  }
  
Serial.println("");
delay(1000);

}
