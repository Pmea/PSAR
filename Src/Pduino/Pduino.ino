
int led = 13;
int mode;  // 0 pour eteins et 1 pour alume
byte GetData[] = {0,10};


void setup() {                
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  mode=0;
  
}

// the loop routine runs over and over again forever:
void loop() {
  int val;
  while(Serial.available() > 0){
    val=Serial.read();
    GetData[0]=val;
    Serial.write(val);
    //Serial.write(GetData,sizeof(GetData)); //Send the byte array    
    if(val == 1)
      digitalWrite(led, HIGH);
    if(val == 0)
      digitalWrite(led, LOW);
  
  }
}t                      

