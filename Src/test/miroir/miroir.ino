
void setup(void){
  Serial.begin(9600);
  Serial.flush();
}

void loop(void){
  char buffer[256]="";
  
  char cmd[16];
  int compt=0;
  
  while(Serial.available()< 6){}
  while( compt < 6){
    cmd[compt]= Serial.read();
    compt++;
    Serial.println(compt);
  }
  if(compt != 0){
    cmd[compt]='\0';
    sprintf(buffer, "%s: %d", cmd, compt);
    Serial.println(buffer);
  }
  Serial.flush();
}
