// -- variables
int outPin = 2;
int inPin = 12;
int state = -1; // -1 for LOW, 1 for HIGH

// -- exécuté une seule fois
void setup()
{
  Serial.begin(9600);

  // -- init des PINs
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);

  // -- état initial
  digitalWrite(outPin, LOW);
  state = 0;
  
  while(!Serial);
  Serial.println("Setup complete");
}

// -- en boucle
void loop()
{
  state = state == -1 ? 1 : -1; // -- inversion de sens à chaque itération de boucle
  Serial.println("--- Nouvelle boucle...");
  Serial.println("state = " + String(state));
  Serial.println("----------------------");
  
  if(state == -1)
  {
    Serial.println( "Setting Pin " + String(outPin) + " to state LOW" );
    digitalWrite(outPin, LOW);
  }
  else
  {
    Serial.println( "Setting Pin " + String(outPin) + " to state HIGH" );
    digitalWrite(outPin, HIGH);
  }
  
  delay(500);

  String inState = digitalRead(inPin) == 1 ? "HIGH" : "LOW";
  Serial.println( "Reading " + String(inPin) + " state: " + inState );

  delay(3000);
}
