#include <SimpleTimer.h>

int photocellPin = 0;     // pin pour connecter la photocell avec resitance (pulldown de 2K) pour les donnees a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect LED to pin 11 
int LEDbrightness;        

int valDelay=100;      // en miliseconde

int valMax;    //pour adapter le systeme a l'environement
int valMin;

int moy;
int lastVal;
long nbEchant=1;

SimpleTimer timer;

void setup(void) {
  Serial.begin(9600);  
  timer.setInterval(1000 * 6 /* * 60*/, periodique);
  
  moy= analogRead(photocellPin);
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
  lastVal= moy;
}
 
void loop(void) {
  timer.run();

  Serial.flush();
  
  if(Serial.available()){
   char cmd[5+1];   // +1 pour '\0'
   int tmp= recv_cmd(5, cmd);
   
   if( strcmp(cmd, "delay") == 0){
     valDelay= tmp;
      
      char buff[64];
      sprintf(buff,"%s: %d;", cmd, valDelay);
      Serial.println(buff);
    }
  }
  
  lastVal= photocellReading;
  photocellReading = analogRead(photocellPin);
  
  moy= moy +  ((float)photocellReading /(float)nbEchant);
  nbEchant++;  

  if(valMin > photocellReading){
    valMin= photocellReading;
  }
  
  if(valMax < photocellReading){
    valMax= photocellReading;
  }
  
  LEDbrightness= map(photocellReading, valMin, valMax, 0, 255);


  //analogWrite(LEDpin, LEDbrightness);
  
  char buff [64]="";
  sprintf(buff, "cellval: %d;", photocellReading);
  Serial.println(buff);
  sprintf(buff, "cellvar: %d;", photocellReading -lastVal);
  Serial.println(buff);
 
  delay(valDelay);
}

void periodique(void){
 // Serial.println("TIMER;");
  nbEchant=1;
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
}

int recv_cmd(int len_cmd, char* cmd){
  int val;
  
  int i=0;
  char tmp;
  
    while(i < len_cmd+1){
      if(Serial.available()){
        tmp=Serial.read();
        if(tmp == ':')
          break;
        if(tmp >'0' && tmp< 'z'){    // 0-9, A-Z et a-z
          cmd[i]= tmp;
          i++;
        }
      }
    }
    
     if(tmp == ':'){
        cmd[i]='\0';
        val= Serial.parseInt();
        Serial.read(); //pour supprimer le ;
        return val;
     }
     Serial.println("Error");
     return -1;
   }

