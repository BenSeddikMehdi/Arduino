#include <DHT.h> // you should Download the DHT11 library 
// https://github.com/adafruit/DHT-sensor-library
#include <DHT_U.h>
#include<SoftwareSerial.h>
SoftwareSerial gprsSerial(7,8);


DHT dht_11; // create a new struct "dht_11" of type DHT 


int gas_Sensor_PIN = A0; // connected to the output pin  : analogPin 
int flame_Sensor_PIN = A1;// select the input pin for the LDR
int dht_Sensor_PIN = 2;

// stock the data into a variables
int gas_Sensor_Value = 0;
int flame_Sensor_Value = 0;
int dht_Sensor_Value = 0;

void setup(){
  Serial.begin(9600); // open serial at 9600 bps
}

void loop()
{
  // read the data from sensors and assign it to variables
  gas_Sensor_Value = analogRead(gas_Sensor_PIN; 
  flame_Sensor_Value = analogRead(flame_Sensor_PIN);
  dht_Sensor_Value = dht_11.read11(dht_Sensor_PIN);
  // Print the data of sensors on the screen
  Serial.println(gas_Sensor_Value);
  Serial.println(flame_Sensor_Value);
  Serial.println(dht_Sensor_Value);
  // Doing some Test of the input Data
  // you can change threshold
  if (gas_Sensor_Value < 35) 
  {
    sendMessage("Gas Detected");
  }
  if (flame_Sensor_Value < 100)
  {
    sendMessage("Fire Detected");
  }
  if (dht_11.temperature > 35)
  {
    sendMessage("High Temperature Detected");
  }
  delay(100); // Get the data every 100ms.
}
void sendMessage(char message[])
{
    Serial.println("Sending Text...");
    gprsSerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
    delay(100);
    // send sms message, the phone number needs to include the country code e.g. if a U.S. phone number such as +212 then the string must be:
    gprsSerial.println("AT+CMGS = \"+2126XXXXXXXX\"");
    delay(100);
    gprsSerial.println(message); //the content of the message
    delay(100);
    gprsSerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
    delay(100);
    gprsSerial.println();
    Serial.println("Text Sent.");
}
