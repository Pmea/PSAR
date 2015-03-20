
int led = 13;
int mode;  // 0 pour eteins et 1 pour alumer

void setup() {                
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  mode=0;
  //Serial.println("INIT");
}

void loop() {
  //Serial.println("LOOP");
  int val;
  while(Serial.available() > 0){    //attendre une valeur a lire
    val=Serial.read();
    
    int ledVal= map(val, 0, 127, 0, 225);
    Serial.write(ledVal);

    analogWrite(led, ledVal);  
  }
}                   

