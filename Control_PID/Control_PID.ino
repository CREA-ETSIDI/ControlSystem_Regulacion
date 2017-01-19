#include <PID_v1.h>

#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

//const float m_pi=0.0031416;

int output;

double distancia, duracion, tension, v_max=5, v_min=-5;

double ref;

double Kp=0.017051218825377, Kd=0.012205994311692, Ki=7.214988139857667e-04;                //Constantes del PID

PID Control(&distancia, &tension, &ref, Kp, Ki, Kd, DIRECT);

void setup() {
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);

  ref = 20;                             //Distancia de referencia

  Control.SetMode(AUTOMATIC);             //Encendemos el PID
  //Control.SetOutputLimits(v_min, v_max);
}

void loop() {
  
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;

  Control.Compute();

  if (tension < 0)
    {
      digitalWrite(fwdPin,LOW);               // el coche se mueve hacia atras
      output=map(tension,-5,0,255,0);         // se mapea tension para adecuarla al pulso pwm 
      analogWrite(bwdPin,output);
    }
  else if(tension > 0)
    {
      digitalWrite(bwdPin,LOW);               //el coche se mueve hacia delante
      output=map(tension,0,5,0,255);
      analogWrite(fwdPin,output);
    }
  else
    {
      output = 0;
    }
} 
