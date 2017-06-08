/*
MODO pino1 pino2
morto 0 0
horario 1 0
anthor 0 1
freio 1 1
*/
//diatancia minima parada = 9
//delay para virar 90º = 650

#include <Servo.h>
#define DIR_PIN1 3
#define DIR_PIN2 4
#define DIR_VEL 9
#define ESQ_PIN1 5
#define ESQ_PIN2 6
#define ESQ_VEL 10
#define DIR 15
#define FRE 90
#define ECHO 12
#define TRIG 13
//potência do motor
#define XABLAU 255 

unsigned int d;
int pos=0;
Servo myservo;
int i=0;

void setup() // ta pronto
{
  setupUltrasonic();
  Serial.begin(9600);
  myservo.attach(7);
  myservo.write(90);
  setupMove();
}
void setupMove()
{
pinMode(ESQ_PIN1, OUTPUT);
pinMode(ESQ_PIN2, OUTPUT);
pinMode(ESQ_VEL, OUTPUT);
pinMode(DIR_PIN1, OUTPUT);
pinMode(DIR_PIN2, OUTPUT);
pinMode(DIR_VEL, OUTPUT);
analogWrite(ESQ_VEL, XABLAU);
analogWrite(DIR_VEL,XABLAU);
}
void setupUltrasonic()
{
pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);
}

void moveTras()
{
digitalWrite(DIR_PIN1, LOW);
digitalWrite(DIR_PIN2, HIGH);
digitalWrite(ESQ_PIN1, LOW);
digitalWrite(ESQ_PIN2, HIGH);
}
void moveFrente()
{
digitalWrite(DIR_PIN1, HIGH);
digitalWrite(DIR_PIN2, LOW);
digitalWrite(ESQ_PIN1, HIGH);
digitalWrite(ESQ_PIN2, LOW);
}
void moveDireita()
{
digitalWrite(DIR_PIN1, LOW);
digitalWrite(DIR_PIN2, LOW);
digitalWrite(ESQ_PIN1, HIGH);
digitalWrite(ESQ_PIN2, LOW);
}
void moveEsquerda()
{
digitalWrite(DIR_PIN1, HIGH);
digitalWrite(DIR_PIN2, LOW);
digitalWrite(ESQ_PIN1, LOW);
digitalWrite(ESQ_PIN2, HIGH);
}
void movePara()
{
digitalWrite(DIR_PIN1, LOW);
digitalWrite(DIR_PIN2, LOW);
digitalWrite(ESQ_PIN1, LOW);
digitalWrite(ESQ_PIN2, LOW);
}

unsigned int medeDist() // Implementação da função do sensor SR04. Retorna a distância em cm.
{
  int distancia; 
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW); 
  distancia = pulseIn(ECHO, HIGH); 
  return distancia/58; 
}
void giraCabecote()
{ 
  for(pos = 0; pos <= 180; pos += 1){                                  
    myservo.write(pos);               
    delay(15);} 
  for(pos = 180; pos>=0; pos-=1){                                
    myservo.write(pos);               
    delay(15);} 
}

void curvaDireita()
{
 moveFrente();
 delay(200);
 moveDireita();
 delay(650);
 moveFrente();
 delay(450);
 movePara();
 delay(200);
}

void curvaEsquerda()
{
 unsigned int menor=40;
 moveEsquerda();
 delay(200);
 movePara();
 myservo.write(DIR);
 delay(70);
 d=40;
 do{
   menor=d;
   d = medeDist();
   moveEsquerda();
   delay(50);
   movePara();
   delay(100);
 }while(d<menor);
 movePara();
 delay(200);
 }

void loop()
{
 movePara();
 myservo.write(DIR);
 delay(400);
 d = medeDist();
 if(d>20)
   curvaDireita();
 else{ 
   myservo.write(FRE);
   delay(300);
   d = medeDist();
    if(d<13)
      curvaEsquerda();
     else{
       moveFrente();
       delay(400);
       moveDireita();
       delay(25);
       movePara();
       delay(100);}}
} 
