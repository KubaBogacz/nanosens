/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/

#include <WiFi.h>

#define SSID "JebacPatrykaMarianskiego"
#define PASSWORD "ZmcpgCi36VDYGXPYGQ"
#define ANALOG_IN_PIN A0
#define MAX_ADC 4096
#define SUPPLY 3.3
#define RESISTOR_1 1.0
#define RESISTOR_2 3.23

int sensorValue_adc = 0;  // value read from the pot
float sensorValue_volts = 0.0;
float resistance = 0.0;
float error = 0.0;
char buff[20];

WiFiServer server(8080);

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {
      //Serial.println("Client connected");
      // loop while the client's connected
      if (true) {
        client.write(1);
        client.write(1);
        client.write(1);
        client.write(1);
        client.write("\n");
        client.write("\n");
        // read the analog in value:
        sensorValue_adc = analogRead(ANALOG_IN_PIN);
        sensorValue_volts = sensorValue_adc * SUPPLY / MAX_ADC;

        resistance = RESISTOR_1 * (SUPPLY - sensorValue_volts) / sensorValue_volts;

        error = 100 * (RESISTOR_2 - resistance) / RESISTOR_2;

        // print the results to the Serial Monitor:
        Serial.print("\nsensor = ");
        Serial.print(sensorValue_volts);
        snprintf (buff, sizeof(buff), "sensor = %.2f V", sensorValue_volts);
        client.write(buff);
        client.write("\n");

        Serial.print("\nresistance = ");
        Serial.print(resistance);
        snprintf (buff, sizeof(buff), "resistance = %.2f Ohm", resistance);
        client.write(buff);
        client.write("\n");

        Serial.print("\nerror = ");
        Serial.print(error);
        Serial.print("%");
        snprintf (buff, sizeof(buff), "error = %.2f", error);
        client.write(buff);
        client.write("\n");
        client.write("\n");
        client.write("\n");

        // wait 2 milliseconds before the next loop for the analog-to-digital
        // converter to settle after the last reading:
        delay(500);
      }
    }
  }
}
