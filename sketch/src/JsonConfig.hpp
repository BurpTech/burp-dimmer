#ifndef JsonConfig_hpp
#define JsonConfig_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

#include "JsonConfigSection.hpp"

template <int capacity>
class JsonConfig {
  using f_callback = std::function<void(JsonDocument *pDoc)>;

  const unsigned int _sectionCount;
  const JsonConfigSection *_sections;
  const f_callback _onSerialize;
  const f_callback _onDeserialize;

  public:
    JsonConfig(
      const unsigned int sectionCount,
      const JsonConfigSection *sections,
      const f_callback onSerialize,
      const f_callback onDeserialize
    )
    : _sectionCount(sectionCount),
      _sections(sections),
      _onSerialize(onSerialize),
      _onDeserialize(onDeserialize)
    {}
    void serialize();
    void deserialize();
};

template <int capacity>
void JsonConfig<capacity>::serialize() {
  DEBUG_LIST_START(F("creating StaticJsonDocument"));
  DEBUG_LIST_VAL(F("capacity"), capacity);
  DEBUG_LIST_VAL(F("section count"), _sectionCount);
  DEBUG_LIST_END;
  StaticJsonDocument<capacity> doc;
  for (int i = 0; i < _sectionCount; i++) {
    DEBUG_VAL(F("serializing section"), F("name"), _sections[i].name);
    JsonObject section = doc.createNestedObject(_sections[i].name);
    _sections[i].serialize(&section);
  }
  _onSerialize(&doc);
}

template <int capacity>
void JsonConfig<capacity>::deserialize() {
  DEBUG_LIST_START(F("creating StaticJsonDocument"));
  DEBUG_LIST_VAL(F("capacity"), capacity);
  DEBUG_LIST_VAL(F("section count"), _sectionCount);
  DEBUG_LIST_END;
  StaticJsonDocument<capacity> doc;
  _onDeserialize(&doc);
  for (int i = 0; i < _sectionCount; i++) {
    DEBUG_VAL(F("deserializing section"), F("name"), _sections[i].name);
    JsonObject section = doc[_sections[i].name];
    _sections[i].deserialize(&section);
  }
}

#endif
