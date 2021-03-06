
const short switchPin2     = 2;
const short switchPin3     = 3;
const short switchPin4     = 4;
const short switchPin6     = 6;

const short U1Pin     = 1;
const short UgPin     = 2;
//const short xxx = 3;
const short pwmOutPin = 5;
const short UladePin     = 7;

const short outPin8_0    = 8;// Arduino_MOSFET von re
const short outPin9_1    = 9;
const short outPin10_2    = 10;
const short outPin11_3    = 11;
const short outPin12_4    = 12;
const short outPin13_5    = 13;
long Ugi = 0;
long U1i = 0;
float UgMittel = 0;
float U1Mittel = 0;
//int Uin = 0;
int Ug = 0;
int U1 = 0;
int U2 = 0;
int PWM = 0 ;
int i = 0;
short Usoll = 450;
short Umin = 430;

bool debug = 1;

bool ladeState = LOW; 
bool switch2 = LOW;
bool switch3 = LOW;
bool switch4 = LOW;
bool switch6 = LOW;
unsigned long currentMillis = 0;
long previousMillis = 0; 
long interval       = 10000; 
long ladeInterval   = 30000; 


void setup(){
   if( debug ) Serial.begin(9600);
   pinMode( pwmOutPin, OUTPUT );
   pinMode( outPin8_0, OUTPUT );
   pinMode( outPin9_1, OUTPUT );
   pinMode( outPin10_2, OUTPUT );
   pinMode( outPin11_3, OUTPUT );
   pinMode( outPin12_4, OUTPUT );
   pinMode( outPin13_5, OUTPUT );
   pinMode( UladePin, OUTPUT );
   pinMode( switchPin2, INPUT_PULLUP ); 
   pinMode( switchPin3, INPUT_PULLUP );
   pinMode( switchPin4, INPUT_PULLUP );
   pinMode( switchPin6, INPUT_PULLUP );
   digitalWrite( UladePin, LOW );
   //setPwmFrequency(10, 10);
}
void loop() {
  currentMillis = millis();
    

 
 /********************************************************************************** 
 +++ Spannungsstabilisator  
 **********************************************************************************/
  
  Ugi += analogRead( UgPin );
  U1i += analogRead( U1Pin );  
  if( i == 50 ){
    UgMittel = Ugi / i;
    U1Mittel = U1i / i;
    U2 = UgMittel - U1Mittel;
    i = 0;
    if( debug ){
      Serial.print("PWM = " );                       
      Serial.print(PWM);      
      Serial.print("\t UgMittel = ");      
      Serial.print(UgMittel);  
      Serial.print("\t U1Mittel = ");  
      Serial.print(U1Mittel); 
      Serial.print("\t U2 = ");  
      Serial.println( U2 ); 
    }
    Ugi = 0;
    U1i = 0;
    if( U2 <= Usoll && PWM < 255 ) PWM++;
    if( U2 > Usoll && PWM > 0 ) PWM--; //Upwm darf nicht 10 oder kleiner  sein
    analogWrite( pwmOutPin, PWM );
  }
  i++;
  
  /************************************************************************************
  +++ Ladeschalter
  *************************************************************************************/
  if( UgMittel <= Umin ){ 
    digitalWrite( UladePin, HIGH );
    previousMillis = currentMillis;
  }
  if( currentMillis - previousMillis > ladeInterval && UgMittel > Umin){//jetzt messen  
     digitalWrite( UladePin, LOW );
  
    //previousMillis = currentMillis;     
    //if( UgMittel <= Umin ) digitalWrite( UladePin, HIGH );
     //digitalWrite( UladePin, LOW );
    
  } 
 
  /************************************************************************************
  +++ Lichtschalter
  *************************************************************************************/ 
  switch2 = digitalRead( switchPin2);
  switch3 = digitalRead( switchPin3);
  switch4 = digitalRead( switchPin4);
  switch6 = digitalRead( switchPin6);
    
  digitalWrite( outPin8_0,  !switch6 );
  digitalWrite( outPin9_1,  !switch6 );
  digitalWrite( outPin10_2, !switch6 );
  digitalWrite( outPin11_3, !switch4 );
  digitalWrite( outPin12_4, !switch3 );
  digitalWrite( outPin13_5, !switch2 );
  //digitalWrite( outTstPin, 1 );
  
  
}
