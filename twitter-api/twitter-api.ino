#include <Bridge.h>
#include <HttpClient.h>

// -- Resource URLs
// -- Returns nb of retweets of the last tweet of user name <id>
//String URL = "http://www.jumahe.com/api/twitter/usr-rt/?id=";
// -- Returns nb of retweets from tweet <id>
//String URL = "http://www.jumahe.com/api/twitter/retweets/?id=";
// -- Returns the last tweet id that matches the query <q>
String URL = "http://www.jumahe.com/api/twitter/query/?q=";
// -- QUERY: #hashtag OR @handlename OR string
String QUERY = "%23judemo";

// -- The LED Pin
int ledZepPin = 13;

// -- Buffer
String dataBuffer = "";

// -- Last data
String last = "";

// -- HTTP Client
HttpClient client;

// -----------------------------------------------------------
// -- SETUP
// -----------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  // -- Debug/Wait
  while(!Serial);
  Bridge.begin();
  
  // -- init LED Pin
  pinMode(ledZepPin, OUTPUT);
  digitalWrite(ledZepPin, LOW);

  // -- init Bridge
  Bridge.begin();
  
  Serial.println("Setup complete.");
}

// -----------------------------------------------------------
// -- LOOP
// -----------------------------------------------------------
void loop()
{
  Serial.println("NEW REQUEST...");
  
  dataBuffer = "";
  
  client.get(URL + QUERY);
  
  while ( client.available() )
  {
    char c = client.read();
    dataBuffer += c;
  }

  Serial.println("--> " + dataBuffer);

  if(last == "" || last != dataBuffer)
  {
    last = dataBuffer;
    
    // -- notify the user
    digitalWrite(ledZepPin, HIGH);
    delay(500);
    digitalWrite(ledZepPin, LOW);
    delay(500);
    digitalWrite(ledZepPin, HIGH);
    delay(500);
    digitalWrite(ledZepPin, LOW);
    delay(500);
    digitalWrite(ledZepPin, HIGH);
    delay(2000);
    digitalWrite(ledZepPin, LOW);
  }
  
  delay(15000);
}
