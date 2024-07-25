int Led_Integrado = 13; 

void setup() 
{ 
  pinMode(Led_Integrado, OUTPUT); 
  delay(1000); 
  digitalWrite(Led_Integrado, LOW); 
} 

void loop() 
{ 
  delay(1000); 
  digitalWrite(Led_Integrado, HIGH); 
  delay(1000); 
  digitalWrite(Led_Integrado, LOW); 
} 
