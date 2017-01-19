#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

const float pulso_m=100;
const float zero_m=1000;

int t, i=0;
float distancia, duracion, salida, output;
double reg;

void setup() {
  Serial.begin(9600);
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);
}

void loop() {
  t = millis(); 
  if(i==0 || i==2)
  {
    if(output!=0)
    {
      reg=t;
    }
     output = 0;
     if((reg+zero_m)<t)
     {
      i+=1;
     }
  }
  if(i==1)
  {
    if(output!=255)
    {
      reg=t;
    }
     output = 255;
     if((reg+pulso_m)<t)
     {
      i=2;
     }
  }
  if(i==3)
  {
    if(output!=-255)
    {
      reg=t;
    }
     output = -255;
     if((reg+pulso_m)<t)
     {
      i=0;
     }
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
