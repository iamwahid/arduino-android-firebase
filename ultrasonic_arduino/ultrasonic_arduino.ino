#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "nodemcu-543df.firebaseio.com"
#define FIREBASE_AUTH "jmEzvHFSbfsQg91srEP7Jn34MhK6SdWp9CLxi3bN"
#define WIFI_SSID "mbayar0"
#define WIFI_PASSWORD "12345678"

const int trigPin = 5;
const int echoPin = 4;
const int r1 = 11;
const int r2 = 12;

//unsigned long time;

char* statuso = "mati";
char* statusi = "mati";

int vstart = 0;
int count = 0;

// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//pinMode(r1, INPUT_PULLUP); // Sets the trigPin as an Output
//pinMode(r2, INPUT_PULLUP); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

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
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

//if (digitalRead(r2) == LOW) {
//  if (statuso == "mati") {
//    statuso = "nyala";  
//    delay(500);
//  } else if (statuso == "nyala") {
//    statuso = "mati";
//    delay(500);  
//  }
//}
//
//if (digitalRead(r1) == LOW) {
//  if (statusi == "mati") {
//    statusi = "nyala";  
////    delay(500);
//  } else if (statusi == "nyala") {
//    statusi = "mati";
////    delay(500);  
//  }
//}

//if (distance > 10 && distance < 30) {
//  digitalWrite(r1, HIGH);
//  digitalWrite(r2, LOW);
//  vstart = 1;
//} else if (distance >= 30) {
//  digitalWrite(r1, LOW);
//  digitalWrite(r2, HIGH);
//  if (vstart == 1) {
//    count++;
//    vstart = 0;  
//  }
//}
//Serial.print("Status 1: ");
//Serial.println(statuso);
//Serial.print("Status 2: ");
//Serial.println(statusi);

//time = millis();
//int minute = (time / 1000) / 60;
if (Firebase.failed()) {
Serial.print("setting /number failed:");
Serial.println(Firebase.error());
return;
} else {
  Firebase.setString("Distance", String(distance));
}
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
//Serial.print("Count: ");
//Serial.println(count);
delay(1000);
}
