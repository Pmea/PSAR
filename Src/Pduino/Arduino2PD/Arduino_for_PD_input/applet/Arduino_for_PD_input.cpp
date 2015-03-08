#include "WProgram.h"
#include "SimpleMessageSystem.h"
/* Analog/Digital inputs to PD trigger
 * ------------
 * send serial values to PD to trigger something
 */

char firstChar; 
char secondChar;

void setup()
{
  Serial.begin(115200);
}


void loop()
{ 
  
  
   if (messageBuild()) { // Checks to see if the message is complete 
      firstChar = messageGetChar(); { // Gets the first word as a character 

     if (firstChar = 'r') { // Checking for the character 'r' 
          secondChar = messageGetChar(); // Gets the next word as a character 
          if (firstChar = 'd') // The next character has to be 'd' to continue 
               messageSendChar('d');  // Echo what is being read 

       for (int i=0;i<=5;i++) { 
       messageSendInt(analogRead(i)); // Read analog pins 0 to 5
          }

       for (int m=2;m<=12;m++) { 
       messageSendInt(digitalRead(m)); // Read digital pins 2 to 12, 13 is onboard LED on Arduino NG
          }
            
       messageEnd(); // Terminate the message being sent 
       
          
                    } 
      }
   }
}
  

  
  
