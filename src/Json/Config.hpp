#ifndef JsonConfig_hpp
#define JsonConfig_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"
#include "Object.hpp"
#include "Document.hpp"

namespace Json {
  class Config {
    public:
      Config(
        const f_withDoc withDoc,
        Object **sections,
        Document *pDocument
      ) :
         _withDoc(withDoc),
        _sections(sections),
        _pDocument(pDocument) {
      }

      void serialize() {
        DEBUG_PRINT("creating JsonDocument");
        _withDoc([=](JsonDocument *pDoc) {
          Object ** _currentSection = _sections;
          while (*_currentSection) {
            DEBUG_PRINT("serializing section: name: [%s]", (*_currentSection)->name);
            JsonObject section = pDoc->createNestedObject((*_currentSection)->name);
            (*_currentSection)->serialize(&section);
            _currentSection++;
          }
          _pDocument->serialize(pDoc);
        });
      }

      void deserialize() {
        DEBUG_PRINT("creating JsonDocument");
        _withDoc([=](JsonDocument *pDoc) {
          _pDocument->deserialize(pDoc);
          Object ** _currentSection = _sections;
          while (*_currentSection) {
            DEBUG_PRINT("deserializing section: name: [%s]", (*_currentSection)->name);
            JsonObject section = (*pDoc)[(*_currentSection)->name];
            (*_currentSection)->deserialize(&section);
            _currentSection++;
          }
        });
      }

    private:
      const f_withDoc _withDoc;
      Object **_sections;
      Document *_pDocument;
  };
};

#endif
