int valDelay=100;

void setup(void){
  Serial.begin(9600);
}

void loop(){  
  int b=0;
  if(Serial.available()){ 
    valDelay= Serial.read();
    b=1;
  }
  
  if(b == 1){
    Serial.write(valDelay);
  }
  delay(valDelay * 10);   //en miliseconde*10
}
