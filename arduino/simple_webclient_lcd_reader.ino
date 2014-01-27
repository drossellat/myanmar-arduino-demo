
#include <LiquidCrystal.h>
#include <Console.h>
#include <HttpClient.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//const int ledPin = 13; // the pin that the LED is attached to
//int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  lcd.begin(16, 2);
  lcd.print("you're connected to the console!!");
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  HttpClient client;
  client.get("http://10.1.89.245:3000/messages/latest");
  lcd.clear();
  while (client.available()) {
    char c = client.read();
    lcd.write(c);
    delay(500);   
    }

}






