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

void loop() {
  t = millis();
  output = 255*sin(m_pi*t*1.5);
  tension = output*5/255;

    Serial.print(output);
    Serial.print("\t");
    Serial.println(distancia);
    Serial.print("\t");
    Serial.println(t);

  
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
