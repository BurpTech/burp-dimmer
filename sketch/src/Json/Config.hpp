#ifndef JsonConfig_hpp
#define JsonConfig_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"
#include "Object.hpp"
#include "Document.hpp"

namespace Json {
  class Config {
    const f_withDoc _withDoc;
    const unsigned int _sectionCount;
    Object **_sections;
    Document *_pDocument;

    public:
      Config(
        const f_withDoc withDoc,
        const unsigned int sectionCount,
        Object **sections,
        Document *pDocument
      ) :
         _withDoc(withDoc),
        _sectionCount(sectionCount),
        _sections(sections),
        _pDocument(pDocument) {
      }

      void serialize() {
        DEBUG_LIST_START(F("creating JsonDocument"));
        DEBUG_LIST_VAL(F("section count"), _sectionCount);
        DEBUG_LIST_END;
        _withDoc([=](JsonDocument *pDoc) {
          for (int i = 0; i < _sectionCount; i++) {
            DEBUG_VAL(F("serializing section"), F("name"), _sections[i]->name);
            JsonObject section = pDoc->createNestedObject(_sections[i]->name);
            _sections[i]->serialize(&section);
          }
          _pDocument->serialize(pDoc);
        });
      }

      void deserialize() {
        DEBUG_LIST_START(F("creating JsonDocument"));
        DEBUG_LIST_VAL(F("section count"), _sectionCount);
        DEBUG_LIST_END;
        _withDoc([=](JsonDocument *pDoc) {
          _pDocument->deserialize(pDoc);
          for (int i = 0; i < _sectionCount; i++) {
            DEBUG_VAL(F("deserializing section"), F("name"), _sections[i]->name);
            JsonObject section = (*pDoc)[_sections[i]->name];
            _sections[i]->deserialize(&section);
          }
        });
      }
  };
};

#endif
