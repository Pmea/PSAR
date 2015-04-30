// rapport valeur moyenne changement d'idee

#include <SimpleTimer.h>
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
#define VOYANTPIN 13

DHT dht(DHTPIN, DHTTYPE);

int photoCellPin = A7;     // pin pour connecter la photocell avec resitance (pulldown de 2K) pour les donnees a0
int photoCellReading;    
int temperatureCellReading;
int humidityCellReading;


boolean on_off;


int valDelay=500;      // en miliseconde

int lastValPhoto=0;
int lastValTemp=0;
int lastValHumi=0;

SimpleTimer timer;

char buff [64];

void setup(void) {
  pinMode(photoCellPin, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(VOYANTPIN, OUTPUT);
  dht.begin();
  
  Serial.begin(9600);  
  timer.setInterval(1000, periodique);
 
  lastValPhoto=0;
 lastValTemp=0;
 lastValHumi=0;
 
 delay(500);
  photoCellReading= analogRead(photoCellPin);
  temperatureCellReading= dht.readTemperature();
  humidityCellReading= dht.readHumidity();
  
  lastValPhoto= photoCellReading;
  lastValTemp= temperatureCellReading;
  lastValHumi= humidityCellReading;
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
  
  lastValPhoto= photoCellReading;  
  lastValTemp= temperatureCellReading;
  lastValHumi= humidityCellReading;
  
  photoCellReading= analogRead(photoCellPin);
  photoCellReading= map(photoCellReading, 0, 1023, 0, 100);
  temperatureCellReading= dht.readTemperature();
  humidityCellReading= dht.readHumidity();
  
  sprintf(buff, "lgtvl: %d;", photoCellReading);
  Serial.println(buff);
  sprintf(buff, "lgtvr: %d;", photoCellReading -lastValPhoto);
  Serial.println(buff);
 
  sprintf(buff, "tmpvl: %d;", temperatureCellReading);
  Serial.println(buff);
  sprintf(buff, "tmpvr: %d;", temperatureCellReading -lastValTemp);
  Serial.println(buff);
  
  sprintf(buff, "hmdvl: %d;", humidityCellReading);
  Serial.println(buff);
  sprintf(buff, "hmdvr: %d;", humidityCellReading -lastValHumi);
  Serial.println(buff);

  delay(valDelay);
}

void periodique(void){
  if(on_off){
    digitalWrite( VOYANTPIN, HIGH);
    on_off=false;
  }
  else{
    digitalWrite( VOYANTPIN, LOW);
    on_off=true;
  }
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

