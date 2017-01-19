#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

const float m_pi=0.0031416;

int maxRange = 200; // maximo rango
int minRange = 0; // Minimo rango
float distancia, duracion, output, drive=0, error, previous_error, integral=0, derivative=0;
int i=0;
float ref=20;
float kp=2, kd=1, ki=-5.5271e-11;

void setup() {
  Serial.begin(9600);
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);
}

void loop() {
  
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;

  if (distancia<=maxRange && distancia>=minRange)
  {
    
    if(drive > -255 && drive < 255)
    {
      error = ref - distancia;
      integral = integral + (error);                          //se calcula el integral
      derivative = (error - previous_error);                  //se calcula el derivativo
      drive = (error*kp) + (integral*ki) + (derivative*kd);   // ecuaciones del pid
      previous_error = error;
    }
    else
    {
      error = ref - distancia;
      drive = (error*kp) + (integral*ki) + (derivative*kd);
      previous_error = error;
    }
    
    if (drive > 255)
    {
      drive  = 255 ;                     // para que drive no se pase de 5 y asi controlar el plso PWM
    }
    else if (drive < -255)
    {
      drive = -255;
    }

    if (drive < 0)
    {
      digitalWrite(fwdPin,LOW);       // el carro se mueve para la izquierda
      //output=map(drive,-5,0,255,0);        // se mapea drive para que el pulso pwm se maneje dentro del rango 
      output = -drive;
      analogWrite(bwdPin,output);
    }
    else
    {
      digitalWrite(bwdPin,LOW);      //el carro se mueve para la derecha
      //output=map(drive,0,5,0,255);
      output = drive;
      analogWrite(fwdPin,output);
    }
  }
  delay(10);
  Serial.println(drive);
}
