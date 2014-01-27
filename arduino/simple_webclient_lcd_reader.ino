
#include <LiquidCrystal.h>
#include <Console.h>
#include <HttpClient.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//const int ledPin = 13; // the pin that the LED is attached to
//int incomingByte;      // a variable to read incoming serial data into
char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

void setup() {
  Bridge.begin();
  Console.begin(); 

  while (!Console){
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");
  // initialize the LED pin as an output:
  lcd.begin(16, 2);
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  while (true) {
    String pageValue = readPage(); //connect to the server and read the output
    lcd.clear();
    lcd.print(pageValue); //print out the findings.
  
    delay(5000); //wait 5 seconds before connecting again
    }
  }


String readPage(){
  //read the page, and capture & return everything between '<' and '>'
  HttpClient client;
  client.get("http://192.168.22.102:3000/messages/latest");
  stringPos = 0;
  memset( &inString, 0, 32 ); //clear inString memory

  while(true){

    if (client.available()) {
      char c = client.read();

      if (c == '<' ) { //'<' is our begining character
        startRead = true; //Ready to start reading the part 
      }else if(startRead){

        if(c != '>'){ //'>' is our ending character
          inString[stringPos] = c;
          stringPos ++;
        }else{
          //got what we need here! We can disconnect now
          startRead = false;
          //client.stop();
          client.flush();
          lcd.print("disconnecting.");
          return inString;

        }

      }
    }

  }

}




