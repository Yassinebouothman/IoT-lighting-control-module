#include <WiFi.h>                                                // esp32 library
//#include <WiFiManager.h> 
#include <IOXhop_FirebaseESP32.h>    


//Provide the RTDB payload printing info and other helper functions.





#define FIREBASE_HOST ""                         // the project name address from firebase id

#define FIREBASE_AUTH ""                    // the secret key generated from firebase

#define WIFI_SSID ""                                          // input your home or public wifi name

#define WIFI_PASSWORD ""                                    //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase

int led = 2;                                                               

void setup() {


// in setup()
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);

  delay(1000);

  pinMode(led, OUTPUT);    

  
//  WiFiManager wifiManager;
//  wifiManager.resetSettings();
//  wifiManager.autoConnect("CIRCUIT DIGEST WiFi Manager");                   // to use ESP32 as a wifi manager you can uncomment this 
//  Serial.println("connected :)");            

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

//  Serial.println();
//
//  Serial.print("Connected to ");
//
//  Serial.println(WIFI_SSID);
//
//  Serial.print("IP Address is : ");
//
//  Serial.println(WiFi.localIP());                                                      //print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    // connect to firebase

  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status

}

void loop() {
  
  fireStatus = Firebase.getString("LED_STATUS");                     // get led status input from firebase

  if (fireStatus == "ON") {                         // compare the input of led status received from firebase

    Serial.println("Led Turned ON");                 

    digitalWrite(led, HIGH);                                                         // make output led ON

  }

  else if (fireStatus == "OFF") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");

    digitalWrite(led, LOW);                                                         // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}
