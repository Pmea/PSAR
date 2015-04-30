
void setup(void){
  Serial.begin(9600);
  Serial.flush();
}


void loop(void){
  
    char cmd[16];
    int val;
    
    int i=0;
    char tmp;
    
    while(i < 5){
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
        val= Serial.parseInt();

        cmd[i]='\0';
        char buff[64];
        sprintf(buff,"%s: %d", cmd, val);
        Serial.println(buff);

     }
     else{
       Serial.println("Error");
       Serial.flush(); // vider la liste
       while(Serial.available()){
         Serial.read();
       }
     }
    
}
