void setup()
{
  pinMode( 1, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(digitalRead(1));
  Serial.println();
}


