#include <PID_v1.h>

#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

//const float m_pi=0.0031416;

int output;

char cadena[30]; //Creamos un array que almacenará los caracteres que escribiremos en la consola del PC. Le asignamos  un tope de caracteres, en este caso 30
byte posicion=0;  //Variable para cambiar la posición de los caracteres del array

double distancia, duracion, tension, v_max=255, v_min=-255;

double ref=30;           //Distancia de referencia

double Kp=9.124631746167328, Kd=1.446652977112854, Ki=14.388195686937985;                //Constantes del PID

PID Control(&distancia, &tension, &ref, Kp, Ki, Kd,REVERSE);

void setup() {
  Serial.begin(9600);
  
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);                            

  Control.SetMode(AUTOMATIC);             //Encendemos el PID
  Control.SetOutputLimits(v_min, v_max);
}

void loop() {

  if(Serial.available()) //Nos dice si hay datos dentro del buffer
  {
    memset(cadena, 0,sizeof(cadena));//memset borra el contenido del array  "cadena" desde la posición 0 hasta el final sizeof
 
    while(Serial.available()>0) //Mientras haya datos en el buffer ejecuta la función
    {
      delay(5); //Poner un pequeño delay para mejorar la recepción de datos
      cadena[posicion]=Serial.read();//Lee un carácter del string "cadena" de la "posicion", luego lee el siguiente carácter con "posicion++"
      posicion++;
    }
 
    ref=atoi(cadena);//Convertimos la cadena de caracteres en enteros
    posicion=0;//Ponemos la posicion a 0
  }
  
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;

  Control.Compute();

  Serial.print(tension);
  Serial.print("\t");
  Serial.print(ref);
  Serial.print("\t");
  Serial.println(distancia);

  
 if (tension < 0)
    {
      digitalWrite(fwdPin,LOW);               // el coche se mueve hacia atras
      //output=map(tension,-5,0,255,0);         // se mapea tension para adecuarla al pulso pwm 
      output=abs(tension);
      analogWrite(bwdPin,output);
    }
  else if(tension > 0)
    {
      digitalWrite(bwdPin,LOW);               //el coche se mueve hacia delante
      //output=map(tension,0,5,0,255);
      output=tension;
      analogWrite(fwdPin,output);
    }
  else
    {
      output = 0;
    }
} 
