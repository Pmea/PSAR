int photocellPin = 0;     // pin pour connecter la photocell avec resitance (pulldown de 2K) pour les donnees a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect LED to pin 11 
int LEDbrightness;        

int valDelay=100;      // en miliseconde

int valMax;    //pour adapter le systeme a l'environement
int valMin;

int moy;
int lastVal;
long nbEchant=0;

void setup(void) {
  Serial.begin(9600);   
  
  moy= analogRead(photocellPin);
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
  lastVal= moy;
}
 
void loop(void) {
  Serial.flush();
  if(Serial.available()){
    valDelay= Serial.parseInt();  // ou sinon avec OSC a voir 
  }
  
  
  lastVal= photocellReading;
  photocellReading = analogRead(photocellPin);    
  nbEchant++;  
  moy= moy +  ((float)photocellReading /(float)nbEchant);
  
  if(valMin > photocellReading){
    //Serial.print("New Min = ");
    //Serial.println(photocellReading);
    valMin= photocellReading;
  }
  
  if(valMax < photocellReading){
    //Serial.print("New Max = ");
    //Serial.println(photocellReading);
    valMax= photocellReading;
  }
  
  LEDbrightness= map(photocellReading, valMin, valMax, 0, 255);
  //Serial.print("Analog reading = ");
  //Serial.println(photocellReading);     // the raw analog reading
 
  //Serial.print("\tLed brightness = ");
  //Serial.println(LEDbrightness);     // led data
 

  analogWrite(LEDpin, LEDbrightness);
  
  Serial.print('valphotocell: ');
  Serial.println(photocellReading);
  
  Serial.print('lastphotocell:');
  Serial.println(lastVal);
 
  delay(valDelay);
}

void periodique(int lastVal, int lastMoy){
  
  nbEchant=0;
  lastVal= lastVal;   // en theorie inutile
  moy= lastMoy;      // en theorie inutile
  valMax= moy + moy * ( 20 / 100 );
  valMin= moy - moy * ( 20 / 100 );
}
