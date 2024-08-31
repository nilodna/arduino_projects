boolean estado = false; //Flag para mudar estado da válvula
 
void setup(){
 
  pinMode(10,OUTPUT); //Pino de saída para chavear relé
  pinMode(11,OUTPUT); //Pino de saída para chavear relé
    
}
 
void loop() {
  
   delay(5000);
     
   estado = !estado; //Altera estado anterior da flag 
   digitalWrite(10, estado); //Altera estado do pino

   digitalWrite(11, !estado);
 
}
