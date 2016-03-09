
#include <Bridge.h>
#include <AirVantage.h>

#define KEY   "SetGpio"

#define MIN_GPIO 2
#define MAX_GPIO 10

void setup() {
  uint8_t i;
  
  for (i = MIN_GPIO; i < MAX_GPIO; i++) {
    // setup gpio pin
    pinMode(i, OUTPUT);
    
    // turn all relays off
    digitalWrite(i, HIGH);
  }

  // initialize bridge and mailbox
  Bridge.begin(115200);
  AirVantage.begin();

  // Wait until a Serial Monitor is connected.
  while (!Serial);

  AirVantage.startSession("", "", 0, CACHE);

  AirVantage.subscribe(KEY);
}

// execute relay control command
// Since array type are not supported yet, temporary using commas seperated string e.g. 10,0
void parseMessage(String message)
{
  // format for commands is "<pin>,<value>"
  int index = message.indexOf(',');
  String pinStr = message.substring(0, index);
  String valueStr = message.substring(index + 1);
  
  Serial.print("Pin: ");
  Serial.println(pinStr);
  Serial.print("Value: ");
  Serial.println(valueStr);
  
  int pin = pinStr.toInt();
  int value = valueStr.toInt();
  
  if ((pin-MIN_GPIO) >= MAX_GPIO) {
    Serial.println("Invalid pin number");
    return;
  }

  digitalWrite((pin-MIN_GPIO), value);
}

void loop() {
  // wait for gpio data
  String message;

  while (AirVantage.dataAvailable())
  {
    AirVantage.readMessage(message);
    String value = AirVantage.parseString(KEY, message);
    parseMessage(value);
  }
}

