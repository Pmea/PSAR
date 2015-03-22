int photocellPin = 0;     // pin pour connecter la photocell avec resitance (pulldown de 2K) pour les donnees a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect LED to pin 11 
int LEDbrightness;        

int valDelay=10;      // en miliseconde * 10

int valMax;    //pour adapter le systeme a l'environement
int valMin;

void setup(void) {
  Serial.begin(9600);   
  valMax=0;
  valMin= (1 << 15) -1 ; // max int 
  
}
 
void loop(void) {
  Serial.flush();
  if(Serial.available()){
    valDelay= Serial.read();
  }
  
  photocellReading = analogRead(photocellPin);    
  
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
  
  photocellReading= map(photocellReading, valMin, valMax, 0, 100);
  //Serial.print("Analog reading = ");
  //Serial.println(photocellReading);     // the raw analog reading
 
  LEDbrightness = map(photocellReading, 0, 100, 0, 255);
  //Serial.print("\tLed brightness = ");
  //Serial.println(LEDbrightness);     // led data
 

  analogWrite(LEDpin, LEDbrightness);
  Serial.print('l');
  Serial.write(photocellReading);
 
  delay(valDelay*10);
}
