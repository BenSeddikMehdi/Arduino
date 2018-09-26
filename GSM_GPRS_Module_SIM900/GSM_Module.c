#include <SoftwareSerial.h>


SoftwareSerial gprsSerial(7,8);

void setup()
{
    gprsSerial.begin(19200); // GPRS shield baud rate
    Serial.begin(19200);
    delay(500);
}

void loop()
{
    if (Serial.available()) // if there is incoming serial data
        switch(Serial.read()) // read the character
        {
            case 't': // if the character is 't'
                SendTextMessage(); // send the text message
                break;
            case 'd': // if the character is 'd'
                DialVoiceCall(); // dial a number
                break;
        }
    if (gprsSerial.available()){ // if the shield has something to say
        Serial.write(gprsSerial.read()); // display the output of the shield
    }
}

/*
* Name: SendTextMessage
* Description: Send a text message to a number
*/
void SendTextMessage()
{
    Serial.println("Sending Text...");
    gprsSerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
    delay(100);
    // send sms message, the phone number needs to include the country code e.g. if a U.S. phone number such as +212 then the string must be:
    gprsSerial.println("AT+CMGS = \"+2126XXXXXXXX\"");
    delay(100);
    gprsSerial.println("Write your Message here..."); //the content of the message
    delay(100);
    gprsSerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
    delay(100);
    gprsSerial.println();
    Serial.println("Text Sent.");
}

/*
* Name: DialVoiceCall()
* Description: Can call/dial a phone number
*/
void DialVoiceCall()
{
    gprsSerial.println("ATD+2126XXXXXXXX;");//dial the number, must include country code
    delay(100);
    gprsSerial.println();
}
