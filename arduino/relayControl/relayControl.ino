
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

  AirVantage.startSession("", "", 0, CACHE);

  AirVantage.subscribe(KEY);
}

// Pin is 1-indexed so offset by 1
// then map to the MIN_GPIO - MAX_GPIO range
int pinToGpio(int pin) {
  return (pin-1+MIN_GPIO);
}

// execute relay control command
// Since array type are not supported yet, temporary using commas seperated string e.g. 10,0
void parseMessage(String message)
{
  // format for commands is "<pin>,<value>"
  int index = message.indexOf(',');
  String pinStr = message.substring(0, index);
  String valueStr = message.substring(index + 1);

  if(Serial) {
    Serial.print("Pin(");
    Serial.print(pinStr);
    Serial.print(") Value(");
    Serial.print(valueStr);
    Serial.println(")");
  }

  int pin = pinStr.toInt();
  int value = valueStr.toInt();

  if (pinToGpio(pin) >= MAX_GPIO) {
    Serial.println("Invalid pin number");
    return;
  }

  digitalWrite(pinToGpio(pin), value);
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

