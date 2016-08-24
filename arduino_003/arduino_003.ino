// -- variable
long last_request_time = 0;

// -- exécuté une seule fois
void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup complete. Type <N> to get the time elapsed since the start of this script.");
}

// -- en boucle
void loop()
{
  // -- si le Serial buffer n'est pas vide
  while(Serial.available())
  {
    char c = Serial.read(); // -- lecture du premier octet disponible
    
    if( c == 'n' || c == 'N' )
    {
      long timestamp = millis();
      Serial.println( "Temps écoulé depuis le début: " + readableTime(timestamp) );

      if( last_request_time != 0 ) Serial.println( "Temps écoulé depuis la dernière requête: " + readableTime(timestamp - last_request_time) );
      last_request_time = timestamp;
    }
  }
}

// -- format de temps lisible
String readableTime(long ms)
{
  int s = ms / 1000;
  ms = ms % 1000;
  int mn = s / 60;
  s = s % 60;

  return String(mn) + ":" + String(s) + ":" + String(ms);
}

