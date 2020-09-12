#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "https://led-control-fcbe9.firebaseio.com/"
#define FIREBASE_AUTH "SKLj9GkxrtMvY8MpnjCms94WMwgq8MCImqERLE6R"
#define WIFI_SSID "NNN"
#define WIFI_PASSWORD "16171819"
void setup() {
Serial.begin(9600);
pinMode(D1, OUTPUT);
// connect to wifi.
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
//Firebase.setInt("LED_STATUS", 0);
// get value
n = Firebase.getInt("LED_STATUS");
Serial.println(n);
// handle error
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
