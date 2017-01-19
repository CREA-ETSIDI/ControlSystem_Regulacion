#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

const float pulso_millis=500;

int t, i=0;
float distancia, duracion, salida, output=0, ancho=1000;

void setup() {
  Serial.begin(9600);
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);
}

void loop() {
  t = millis(); 
  if(i==0)
  {
     output += 5;
  }
  
  if(output>=255)
  {
    output=0;
    i=1;
  }
  
  if(i==1)
  {
    output -= 5;
  }
  
  if (output<=-255)
  {
    output=0;
    i=0;
  }


    Serial.print(output);
    Serial.print("\t");
    Serial.print(distancia);
    Serial.print("\t");
    Serial.println(t);

  
  if(output>0)
  {
    analogWrite(fwdPin,output);
    digitalWrite(bwdPin,LOW);
  }
  else if(output<0)
  {
    salida=abs(output);
    analogWrite(bwdPin,salida);
    digitalWrite(fwdPin,LOW);
  }
  
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;
}
