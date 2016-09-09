// -- variables
int led_pin = 11;   // -- pin alimentant la LED
int pause = 500;    // -- pause entre chaque changement d'état
int iterations = 5; // -- nombre d'itérations

// -- exécuté une seule fois
void setup()
{
  Serial.begin(9600);

  // -- init led pin
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  
  while(!Serial);
  Serial.println("Setup complete. Type <n> to make it blink.");
}

// -- boucle
void loop()
{
  while(Serial.available())
  {
    if( Serial.read() == 'n' )
    {
      blinkit();
    }
  }
}

// -- blink it
void blinkit()
{
  for(int i = 0; i < iterations; i++)
  {
    digitalWrite(led_pin, HIGH);
    delay(pause);
    digitalWrite(led_pin, LOW);
    delay(pause);
  }
}

