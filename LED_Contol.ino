#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "https:
#define FIREBASE_AUTH "SKLj9GkxrtMvY8MpnjCms94WMwgq8MCImqERLE6R"
#define WIFI_SSID "Redmi Y2"
#define WIFI_PASSWORD "55555555"
void setup() {
Serial.begin(9600);
pinMode(D1, OUTPUT);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
int n = 0;
void loop() {

n = Firebase.getInt("LED_STATUS");
Serial.println(n);

if(n==1) {
Serial.println("LED ON");
digitalWrite(D1,HIGH);  
return;
delay(10);
}
else {
Serial.println("LED OFF");
digitalWrite(D1,LOW);  
return;
}
}
