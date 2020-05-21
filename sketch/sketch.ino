#include <Arduino.h>
#include <functional>

#include "src/Debug.hpp"

#include "src/Button.hpp"
#include "src/RotaryEncoder.hpp"
#include "src/Light.hpp"
#include "src/Storage.hpp"
#include "src/Network.hpp"
#include "src/HttpServer.hpp"

#include "src/ConfigFile.hpp"
#include "src/Config.hpp"

#define RESET_DELAY 1000

void lightOnUpdate(bool on, int brightness);
Light light(D1, lightOnUpdate);

void buttonOnRelease();
Button button(D7, buttonOnRelease);

void resetButtonOnRelease();
Button resetButton(D2, resetButtonOnRelease);

ICACHE_RAM_ATTR void knobInterruptDispatch();
void knobOnChange(int direction);
RotaryEncoder knob(D5, D6, knobInterruptDispatch, knobOnChange);

void networkOnStateChange(Network::State state);
void httpServerOnSettings(const char *ssid, const char *password);

void appleSerialize(JsonObject *pObj) {
  (*pObj)["color"] = "red";
}

void appleDeserialize(JsonObject *pObj) {
  const char *color = (*pObj)["color"];
  DEBUG_VAL(F("apple"), F("color"), color);
}

void bananaSerialize(JsonObject *pObj) {
  (*pObj)["color"] = "yellow";
}

void bananaDeserialize(JsonObject *pObj) {
  const char *color = (*pObj)["color"];
  DEBUG_VAL(F("banana"), F("color"), color);
}

using namespace std::placeholders; // for _1, _2
ConfigFile _configFile("/config.json");
ConfigSection _configSections[] = {
  ConfigSection(
    "apple",
    appleSerialize,
    appleDeserialize
  ),
  ConfigSection(
    "banana",
    bananaSerialize,
    bananaDeserialize
  )
};
Config<256> _config(
  CONFIG_SECTION_ARRAY_LENGTH(_configSections),
  _configSections,
  std::bind(&ConfigFile::write, _configFile, _1),
  std::bind(&ConfigFile::read, _configFile, _1)
);

void setup() {
  Serial.begin(115200);
  Storage::begin();
  resetButton.setup();
  light.setup();
  button.setup();
  knob.setup();
  Network::setup(networkOnStateChange);
  HttpServer::setup(httpServerOnSettings);

  // Testing new config
  _config.serialize();
  _config.deserialize();
}

void loop() {
  resetButton.loop();
  button.loop();
  knob.loop();
  Network::loop();
  HttpServer::loop();
}

void resetButtonOnRelease() {
  DEBUG_VAL(F("Resetting"), F("delay (ms)"), RESET_DELAY);
  delay(RESET_DELAY);
  ESP.reset();
}

void lightOnUpdate(bool on, int brightness) {
  DEBUG_LIST_START(F("new value"));
  DEBUG_LIST_VAL(F("on"), on);
  DEBUG_LIST_VAL(F("brightness"), brightness);
  DEBUG_LIST_END;
}

void buttonOnRelease() {
  DEBUG_MSG(F("toggle the light"));
  light.toggle();
}

void knobInterruptDispatch() {
  knob.interrupt();
}

void knobOnChange(int direction) {
  DEBUG_VAL(F("change the light brightness"), F("change"), direction);
  light.changeBrightness(direction);
}

void networkOnStateChange(Network::State state) {
  DEBUG_VAL(F("new state"), F("state"), static_cast<int>(state));
}

void httpServerOnSettings(const char *ssid, const char *password) {
  DEBUG_LIST_START(F("new settings"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  Network::setStationConfig(ssid, password);
}
