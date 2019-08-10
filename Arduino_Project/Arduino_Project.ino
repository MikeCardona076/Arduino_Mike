#include <LiquidCrystal.h>
int RS = 53;
int E = 51;
int D4 = 43;
int D5 = 47;
int D6 = 45;
int D7 = 41;
#define Pecho 6
#define Ptrig 7
#define Micro 8
long duracion, distancia;   
LiquidCrystal lcd (RS, E, D4, D5, D6, D7);

 
void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13, 1);            // Define el pin 13 como salida
  pinMode(8, 1);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("No detected");
  }
  
void loop() {
  
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
  if (distancia >= 40 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    //Serial.println("---");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("No detected");
    lcd.setCursor(0, 1);
    lcd.print("EL MIKE");
   
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13, 0);               // en bajo el pin 13
    digitalWrite(8,0);                 // el pin 8 en bajo
    
  }
  
   if (distancia <= 40){
    digitalWrite(13, 1);     // en alto el pin 13 si la distancia es menor a 10cm
    digitalWrite(8,1);
    Serial.println("Alarma.......");  
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("detected");
    
    
  }
                                  // espera 400ms para que se logre ver la distancia en la consola
  delay(100);
}
