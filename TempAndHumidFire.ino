#include <FirebaseArduino.h>
#include <Firebase.h>
#include <ESP8266WiFi.h>    
#include <DHT.h>         
#define FIREBASE_HOST "temphumid-bd7f8.firebaseio.com/"
#define FIREBASE_AUTH "DF9VdtfpVKgd906sOc5xUbNpJYklqyH5eawD5g3S"
#define WIFI_SSID "Redmi"                
#define WIFI_PASSWORD "11223344"             
#define DHTPIN D4              
#define DHTTYPE DHT11            
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
  Serial.println(WiFi.localIP());                
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   
  dht.begin();                     
}

void loop() {
  float h = dht.readHumidity();       
  float t = dht.readTemperature();   
  delay(20000);
  if (isnan(h) || isnan(t)) {  
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");  
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t) + String("Â°C"); 
 
 //  Firebase.setString("Msg","Hello");
  Firebase.pushString("Humidity", fireHumid);        
  Firebase.pushString("Temperature", fireTemp);   
   

  Firebase.setFloat("Humidity",h);
  Firebase.setFloat("Temperature",t);
  delay(4000);
}
