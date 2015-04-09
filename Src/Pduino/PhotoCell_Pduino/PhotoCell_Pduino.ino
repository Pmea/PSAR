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

void setup(void) {
  Serial.begin(9600);  
  //SimpleTimer timer;
  //int timerId= timer.setInterval(1000/**3600*/, periodique);
  //timer.enable(timerId);
  
  moy= analogRead(photocellPin);
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
  lastVal= moy;
}
 
void loop(void) {
  Serial.flush();
  
  if(Serial.available()){
          valDelay= Serial.parseInt();
    /*char* cmd;
    cmd= recv_cmd(5);
    if( strcmp(cmd, "delay")){
      valDelay= Serial.parseInt();
      //Serial.println(valDelay);
    }*/
    delay(1000);
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
  sprintf(buff, "cellval: %d", photocellReading);
  Serial.println(buff);
  sprintf(buff, "cellvar: %d", photocellReading -lastVal);
  Serial.println(buff);
 
  delay(valDelay);
}

void periodique(void){
  Serial.println("PERIODIQUE");
  nbEchant=1;
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
}



char* recv_cmd(int len_cmd){
  char cmd[len_cmd];
  int val;
  
  int i=0;
  char tmp;
  
   while(i < len_cmd+1){        // +1 pour les ':'
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
     }
     else{
       Serial.println("Error");
       Serial.flush(); // vider la liste
       while(Serial.available()){
         Serial.read();
       }
       
       return "";
     }
     return cmd;

}

