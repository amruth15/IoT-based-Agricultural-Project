#include <FirebaseArduino.h>
#include <Firebase.h>
#include <ESP8266WiFi.h>    //esp8266 library
#include <DHT.h>         // dht11 temperature and humidity sensor library
#define FIREBASE_HOST "temphumid-bd7f8.firebaseio.com/"
#define FIREBASE_AUTH "DF9VdtfpVKgd906sOc5xUbNpJYklqyH5eawD5g3S"
#define WIFI_SSID "Redmi"                  // wifi name 
#define WIFI_PASSWORD "11223344"                 //password of wifi
#define DHTPIN D4                // what digital pin we're connected to
#define DHTTYPE DHT11              // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                  //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     // connect to firebase
  dht.begin();                            //Start reading dht sensor
  // Firebase.setString("Humidity","0");
  // Firebase.setString("Temperature","0");
}

void loop() {
  float h = dht.readHumidity();       // Reading temperature or humidity
  float t = dht.readTemperature();   // Read temperature as Celsius (the default)
  delay(20000);
  if (isnan(h) || isnan(t)) {  // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");    //convert integer humidity to string humidity
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t) + String("Â°C"); //convert integer temperature to string temperature
 
 //  Firebase.setString("Msg","Hello");
  Firebase.pushString("Humidity", fireHumid);         //setup path and send readings
  Firebase.pushString("Temperature", fireTemp);        //setup path and send readings
   

  Firebase.setFloat("Humidity",h);
  Firebase.setFloat("Temperature",t);
  delay(4000);
}
