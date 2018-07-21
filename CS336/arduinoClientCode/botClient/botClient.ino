/*
  Bot's Web Client

 This will use the ethernet shield to connect
 to our server, request input from other
 client and use LEDS in relation
 to input (W, A, S, D, Q);

 Circuit:
 * Assuming Ethernet shield attached to pins 10, 11, 12, 13

 created 28 Nov 2015
 by Evan L. Conley
  
*/

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// use the numeric IP for the server:
IPAddress ip(50, 53, 5, 88);

// Initialize the Ethernet client library
EthernetClient client;

//These should refer to whatever pin numbers LED's are connected to
//I placed in random values until we know how to wire them
const int ledWPin =  13;
const int ledAPin =  10;
const int ledSPin =  11;
const int ledDPin =  12;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // If native USB port, wait for connection
  }
  Ethernet.begin(mac, ip);
  delay(1000);
  Serial.println("connecting...");
  
  if (client.connect(ip, 5001))
  {
    Serial.println("connected");
  }
  client.println("Please enter a string of command values:\nW: Forward\nA: left\nS: back\nD: right\nQ: quit");
}

void loop()
{
  if(client.available())
  {
    char c[] = client.read();
    
    //This loop should blink LED's in response to input commands,
    //Quit in response to Q input command
    //And inform of error should they put in an incorrect command 
    for(int letter = c.length()-1, letter > 0, letter--)
    {
         if      (c[letter].equalsIgnoreCase('W'))     {digitalWrite(ledWPin, HIGH);
                                                       digitalWrite(ledWPin, LOW);}
                                                
         else if (c[letter].equalsIgnoreCase('A'))     {digitalWrite(ledAPin, HIGH);
                                                       digitalWrite(ledAPin, LOW);}
                                                
         else if (c[letter].equalsIgnoreCase('S'))     {digitalWrite(ledSPin, HIGH);
                                                       digitalWrite(ledSPin, LOW);}
                                                
         else if (c[letter].equalsIgnoreCase('D'))     {digitalWrite(ledDPin, HIGH);
                                                       digitalWrite(ledDPin, LOW);}
                                                
         else if (c[letter].equalsIgnoreCase('Q'))     {Serial.println();
                                                       Serial.println("disconnecting.");
                                                       client.stop();}
                                                
         else                                          {client.println(c, " is not a valid command value");}
    
    }
  }
    
    if (!client.connected())
    {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    }
    // do nothing forevermore:
    while (true);
}
