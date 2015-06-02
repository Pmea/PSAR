//TODO
// Il serait interessant d'ajouter un Watchdog pour redemarer la partie arduino
// si il y a un bug quelque part
// pour cela il existe de nombreuse bibliotheque (les liens sont disponible sur le site officiel arduino) 

#include <SimpleTimer.h>
#include "DHT.h"

#define DHTPIN 2        // le pin ou est connecter le module DHT11
#define DHTTYPE DHT11   // DHT 11, le type de module pour la temperature et l'humidité
#define VOYANTPIN 13    // le pin pour le led clignotante, montrant le bon fonctionnement de la partie arduino


DHT dht(DHTPIN, DHTTYPE);

int photoCellPin = A7;     // pin pour connecter la photocell avec resitance (pulldown de 2K) pour les donnees a7
int photoCellReading;    
int temperatureCellReading;
int humidityCellReading;


boolean on_off;


int valDelay=500;      // en miliseconde

int lastValPhoto=0;
int lastValTemp=0;
int lastValHumi=0;

// timer qui va commender l'allumage periodique de la voyant de fonctionnement
SimpleTimer timer;

char buff [64];

void setup(void) {
  pinMode(photoCellPin, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(VOYANTPIN, OUTPUT);
  dht.begin();
  
  Serial.begin(9600);  
  timer.setInterval(1000, periodique);    // preparation du timer
 
  lastValPhoto=0;
  lastValTemp=0;
  lastValHumi=0;
 
  delay(250);      // delai de sureté pour laisser le temps au capteur DHT de d'initialiser (sinon risque de fausse valeur) 
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
  
  if(Serial.available()){            // si il y a quelquess choses a lire, sur le canal d'entrée
   char cmd[5+1];   // +1 pour '\0'
   int tmp= recv_cmd(5, cmd);
   if( strcmp(cmd, "delay") == 0){      // on verifi que cela correspond bien a la commande changement de delay
     valDelay= tmp;
     
      char buff[64];
      sprintf(buff,"%s: %d;", cmd, valDelay);
      Serial.println(buff);
    }
  }
  
  // sauvegarde des dernieres valeurs
  lastValPhoto= photoCellReading;  
  lastValTemp= temperatureCellReading;
  lastValHumi= humidityCellReading;
  
  // lecture des nouvelles valeurs
  photoCellReading= analogRead(photoCellPin);
  photoCellReading= map(photoCellReading, 0, 1023, 0, 100);
  temperatureCellReading= dht.readTemperature();
  humidityCellReading= dht.readHumidity();
  
  
  //TODO pour eviter les erreurs de capteur, il faudrait revifier que la difference entre 
  // la valeurs sauvegardé et la nouvelle valeur n'est pas plus a plus de 30% de l'ancienne.
  // de simple if, else a faire
 
  // creation de la commande conforme au protocole et
  // envoi de la valeur sur le canal de communication
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


// allumage du voyant pour informer l'etat de fonctionnement du dispositif
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



// traiter la commande recu
// verification du format et extraction de la valeur
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

