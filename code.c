int sample[8];
float media;
float temperatura;
int i; 

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);     //Pega a referência de tensão máxima a partir do pino AREF
}
 
void loop() {
  
  media = 0;
  
  for (i = 0; i < 8; i++) {      //Pega 8 samples para deixar um valor mais estabilizado
   sample[i] = analogRead(0);
   media += sample[i];
   delay(10);
  }

  media /= 8;                    //divide pelo número de samples para ter a media
  
  // Converte o valor da tensão em resistência
  media = (3.3 * media) / 1023;
  media = (10000 * media) / (3.3 - media);
  
  //Faz o cálculo pela fórmula do Fator Beta
  temperatura = media / 10000;                  //(R/Ro)
  temperatura = log(temperatura);               //ln(R/Ro)
  temperatura /= 3977;                          //1/B * ln(R/Ro)
  temperatura += 1.0 / (25 + 273.15);           //+ (1/To)
  temperatura = 1.0 / temperatura;              //Inverte o valor
  temperatura -= 273.15;                        //Converte para Celsius
 
  Serial.print("Temperatura no Sensor eh: ");   //printa a temperatura
  Serial.print(temperatura);                    //no monitor serial
  Serial.println(" *C");
 
  delay(1000);                                  //ms entre os  prints
}
