// I'm using the WiFiNINA library to connect to a WiFi network,
// the BH1750 library to read the light level from a BH1750 light sensor,
// and the Wire library to communicate with the I2C bus.

#include <WiFiNINA.h>
#include <BH1750.h>
#include <Wire.h>

// These are my WiFi credentials.
char ssid[] = "Tryit";
char pass[] = "asmi1234";

// I'm creating a WiFi client object and a BH1750 light sensor object.
WiFiClient client;
BH1750 lightMeter;

// These are the hostname and path of the IFTTT Maker channel.
char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "frt-m3Wab4WD_H348gZx7PkMcP6K3AH_1xaHSiVsHdS";
String queryString = "?value1=57&value2=25";

// This function initializes the WiFi connection.
void setup() {
  // I'm initializing the WiFi connection.
  WiFi.begin(ssid, pass);

  // I'm starting serial communication.
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open

  // I'm connecting to the web server on port 80.
  if (client.connect(HOST_NAME, 80)) {
    // If connected:
    Serial.println("Connected to server");
    
    // I'm initializing the I2C bus.
    Wire.begin();

    // I'm initializing the BH1750 light sensor.
    lightMeter.begin();

    Serial.println(F("BH1750 Test begin"));
  }
  else {
    // If not connected:
    Serial.println("Connection failed");
  }
}

// This function is called repeatedly in an infinite loop.
void loop() {
  // If the user presses the 's' key, I send an HTTP GET request to IFTTT.
  if (Serial.read() == 's') {
    // I'm sending an HTTP GET request to IFTTT
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // End HTTP header

    // I'm reading and printing the response from IFTTT until the connection closes.
    while (client.connected()) {
      if (client.available()) {
        // I'm reading and printing the response from IFTTT
        char c = client.read();
        Serial.print(c);
      }
    }

    // I'm closing the client connection.
    client.stop();
    Serial.println();
    Serial.println("Disconnected");          
    delay(1000);                                                                 
  }
}
