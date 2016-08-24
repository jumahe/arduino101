// -- exécuté une seule fois
void setup()
{
  Serial.begin(9600);
  while(!Serial); // -- préférable, pour être sûr :)
  Serial.println("Hello World!");
}

// -- pas besoin pour l'instant
void loop(){}
