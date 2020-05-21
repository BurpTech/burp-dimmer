#ifndef JsonConfigSection_hpp
#define JsonConfigSection_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

#define CONFIG_SECTION_ARRAY_LENGTH(ARRAY) (sizeof ARRAY / sizeof(JsonConfigSection))

class JsonConfigSection {
  using f_callback = std::function<void(JsonObject *pObj)>;

  public:
    const char * name;
    const f_callback serialize;
    const f_callback deserialize;
    JsonConfigSection(
      const char *name,
      const f_callback serialize,
      const f_callback deserialize
    )
    : name(name),
      serialize(serialize),
      deserialize(deserialize)
    {}
};

#endif
