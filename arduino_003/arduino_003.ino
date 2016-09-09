// -- variable
String myBuffer = "";

// -- exécuté une seule fois
void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup complete. Type your String, then click SEND.");
}

// -- en boucle
void loop()
{
  // -- RAZ à chaque boucle loop
  myBuffer = "";
  
  // -- si le Serial buffer n'est pas vide
  // -- lire son contenu lettre à lettre (while)
  while(Serial.available())
  {
    char c = Serial.read(); // -- lecture du premier octet disponible
    myBuffer = myBuffer + String(c); // -- concaténation dans le buffer
  }

  // -- s'il n'est pas vide, le renvoyer après modification
  if(myBuffer != "")
  {
    myBuffer.toUpperCase();
    Serial.println("myBuffer: " + myBuffer + ".");
  }

  delay(500); // -- petit délais
}

