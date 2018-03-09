#include <Thing.h>
#include <BlinkPattern.h>
#include <Wire.h>

#define BUTTON_PIN 0
#define GREEN_LED_PIN 13
#define RELAY_PIN 12

using namespace g3rb3n;

Thing thing;
BlinkPattern led(GREEN_LED_PIN);

BlinkPattern::Pattern<2> initialize{{1,1},50};
BlinkPattern::Pattern<2> started{{1,1},200};
BlinkPattern::Pattern<2> request{{1,3},100};
BlinkPattern::Pattern<2> done{{1,9},100};

bool state = true;
bool buttonState = false;
bool feedbackState = false;
long nextSwitch = 0;

void setup()
{
    //Serial.begin(230400);
    Serial.begin(115200);
    Serial.println();

    Serial.println("ClientID:" + thing.clientId());

    led.begin();

    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    led.setPattern(initialize);
    thing.onStateChange([](const String& msg){
        Serial.println(msg);
    });

    thing.begin();

    //thing.addSensor(thing.clientId() + "/button/state", 1000, [](Value& value){
    //  value = state;
    //});

    thing.addActuator(thing.clientId() + "/button/feedback", [](Value& value){
        Serial.println("Got " + (String)value);
        feedbackState = (bool)value;
        state = feedbackState;
        led.setPattern(done);
    });

    thing.addActuator(thing.clientId() + "/relay/switch", [](Value& value){
        state = (bool)value;
        digitalWrite(RELAY_PIN, state);
        Serial.println("Got:" + String(state));
        thing.publish(thing.clientId() + "/relay/state", value);
    });
    led.setPattern(started);
}

void loop()
{
    handle();
    led.handle();
    thing.handle();
}

void handle()
{
    bool pushed = !digitalRead(BUTTON_PIN);
    if (pushed && pushed != buttonState && millis() > nextSwitch)
    {
        nextSwitch = millis() + 100;
        state = !state;
        led.setPattern(request);
        Value value = state;
        digitalWrite(RELAY_PIN, state);
        thing.publish(thing.clientId() + "/button/state", value);
    }
    buttonState = pushed;
}
