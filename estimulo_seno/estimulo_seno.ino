#define trigPin 2
#define echoPin 6
#define fwdPin 3
#define bwdPin 5

const float m_pi=0.0031416;

int t, i=0;
float distancia, distancia_prev, duracion, output, tension;

void setup() {
  Serial.begin(9600);
  pinMode (trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
  pinMode (fwdPin,OUTPUT);
  pinMode (bwdPin,OUTPUT);
}

bool antirruido(float x, float x_prev)
{
  float x_min = x_prev*0.8;
  float x_max = x_prev*1.3;
  if(x<x_max && x>x_min && i!=1) {
    i=0;
    return 1;
  }
  else {
    i++;
    return 0;
  }
}

void loop() {
  t = millis();
  output = 255*sin(m_pi*t);
  tension = output*5/255;

  if(antirruido(distancia, distancia_prev))
  {
    Serial.print(tension);
    Serial.print(",");
    Serial.println(distancia);
   // Serial.print("\t");
    //Serial.println(t);
  }

  distancia_prev=distancia;
  
  if(output>0)
  {
    analogWrite(fwdPin,output);
    digitalWrite(bwdPin,LOW);
  }
  else if(output<0)
  {
    output=abs(output);
    analogWrite(bwdPin,output);
    digitalWrite(fwdPin,LOW);
  }
  
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (1000);
  digitalWrite (trigPin,LOW);
  duracion = pulseIn(echoPin,HIGH);
  distancia=(duracion/2) / 29.1;
}
