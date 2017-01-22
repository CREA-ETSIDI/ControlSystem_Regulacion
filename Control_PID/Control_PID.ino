#include <PID_v1.h>

#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

int output;

char cadena[4];       //Creamos un array que almacenará los caracteres que escribiremos en la consola del PC
byte posicion=0;      //Variable para cambiar la posición de los caracteres del array

double distancia, duracion, tension;    //Variables para el sensor de US y el controlador

double ref=30;                          //Distancia de referencia inicial

double Kp=27.65280482674217, Kd=4.887091689039301, Ki=39.11721241597037;    //Constantes del PID 

PID Control(&distancia, &tension, &ref, Kp, Ki, Kd,REVERSE);                //Declaramos el PID llamado Control

void setup() {
  Serial.begin(9600);                     //Comunicacion serial para enviar y recibir datos a traves del PC
  
  pinMode (trigPin,OUTPUT);               //Configuración de los pines
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);                            

  Control.SetMode(AUTOMATIC);             //Encendemos el PID
  Control.SetOutputLimits(-255, 255);     //Limitamos los valores de salida del PID conforme a los limites del PWM
}

void loop() {

  if(Serial.available())                //Si hay datos dentro del buffer
  {
    memset(cadena, 0,sizeof(cadena));   //memset borra el contenido de "cadena" desde la posición 0 hasta el final
 
    while(Serial.available()>0)         //Mientras haya datos en el buffer
    {
      delay(5);                         //Delay para mejorar la recepción de datos
      cadena[posicion]=Serial.read();   //Lee los caracteres de "cadena" posicion a posicion
      posicion++;
    }
 
    ref=atoi(cadena);                   //Convertimos la cadena de caracteres en enteros y se lo asignamos a la referencia
    posicion=0;                         //Ponemos la posicion a 0
  }
  
  digitalWrite (trigPin,HIGH);          //Actualizacion de la distancia
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;

  Control.Compute();                    //Actualizacion de la salida del PID

  Serial.print(tension);                //Impresion serial de la referencia, la tension y la distancia
  Serial.print("\t");
  Serial.print(ref);
  Serial.print("\t");
  Serial.println(distancia);
                                          //SALIDAS
  
 if (tension < 0)                             //Si tension es negativa
    {
      digitalWrite(fwdPin,LOW);               //El coche se mueve hacia atras
      output=abs(tension);                    //Se adecua tension al valor PWM
      analogWrite(bwdPin,output);             //Se escribe el valor analogico
    }
  else if(tension > 0)                        //Si tension es positiva
    {
      digitalWrite(bwdPin,LOW);               //El coche se mueve hacia delante;
      analogWrite(fwdPin,tension);            //Se escribe el valor analogico
    }
  else                                        //Si tension es cero
    {
      digitalWrite(fwdPin,LOW);               //El coche no se mueve
      digitalWrite(bwdPin,LOW); 
    }
} 
