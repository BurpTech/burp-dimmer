#ifndef ConfigSection_hpp
#define ConfigSection_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

#define CONFIG_SECTION_ARRAY_LENGTH(ARRAY) (sizeof ARRAY / sizeof(ConfigSection))

class ConfigSection {
  using f_jsonCallback = std::function<void(JsonObject *pObj)>;

  public:
    const char * name;
    const f_jsonCallback serialize;
    const f_jsonCallback deserialize;
    ConfigSection(
      const char *name,
      const f_jsonCallback serialize,
      const f_jsonCallback deserialize
    )
    : name(name),
      serialize(serialize),
      deserialize(deserialize)
    {}
};

#endif
