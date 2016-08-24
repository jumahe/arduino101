#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h"

// -- Limitation
int maxCalls = 10;
// -- Requests calls counter
int calls = 0;
// -- The LED Pin
int ledZepPin = 13;
// -- Last Tweet ID
String lastID = "";

// -----------------------------------------------------------
// -- SETUP
// -----------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  // -- Debug/Wait
  delay(4000);
  while(!Serial);
  Bridge.begin();
  
  // -- init LED Pin
  pinMode(ledZepPin, OUTPUT);
  digitalWrite(ledZepPin, LOW);
  
  Serial.println("Setup complete.");
}

// -----------------------------------------------------------
// -- LOOP
// -----------------------------------------------------------
void loop()
{
  if (calls < maxCalls)
  {
    Serial.println("Calling LatestTweet Choreo... " + (calls+1) + "/" + maxCalls);
    runLatestTweet();
    calls++;
  }
  else
  {
    Serial.println("Skipping to save Temboo calls. Adjust maxCalls or restart.");
  }

  // -- Wait 30 secs before the next call
  delay(30000);
}

// -----------------------------------------------------------
// -- Call function
// -----------------------------------------------------------
void runLatestTweet()
{
  TembooChoreo LatestTweetChoreo;

  // -- Invoke the Temboo client
  LatestTweetChoreo.begin();

  // -- Set Temboo account credentials
  LatestTweetChoreo.setAccountName(TEMBOO_ACCOUNT);
  LatestTweetChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  LatestTweetChoreo.setAppKey(TEMBOO_APP_KEY);

  // -- Set profile to use for execution
  LatestTweetChoreo.setProfile("judemo");
  // -- Identify the Choreo to run
  LatestTweetChoreo.setChoreo("/Library/Twitter/Search/LatestTweet");

  // -- Run the Choreo
  unsigned int returnCode = LatestTweetChoreo.run();

  // -- 0 == OK
  if (returnCode == 0) 
  {
    while (LatestTweetChoreo.available()) 
    {
      // -- read the first line
      String name = LatestTweetChoreo.readStringUntil('\x1F');
      name.trim();

      // -- read the second line
      String data = LatestTweetChoreo.readStringUntil('\x1E');
      data.trim();
      
      // -- if the first line is "ID", then read the value on the second line
      if (name == "ID")
      {
        if ( data != lastID )
        {
          // -- set the last data ID
          lastID = data;

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
      }
    }
  }
  
  // -- close the Temboo Client
  LatestTweetChoreo.close();
}
