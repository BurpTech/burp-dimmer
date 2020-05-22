#ifndef JsonHttpApi_hpp
#define JsonHttpApi_hpp

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "../Debug.hpp"

#include "Json.hpp"
#include "Object.hpp"

namespace Json {
  class HttpApi {
    String _prefix;
    const f_withDoc _withDoc;
    const unsigned int _endPointCount;
    Object **_endPoints;
    ESP8266WebServer *_pServer;

    public:
      HttpApi(
        String prefix,
        const f_withDoc withDoc,
        const unsigned int endPointCount,
        Object **endPoints,
        ESP8266WebServer *pServer
      ) :
        _prefix(prefix),
        _withDoc(withDoc),
        _endPointCount(endPointCount),
        _endPoints(endPoints),
        _pServer(pServer) {
      }

      void setup() {
        DEBUG_LIST_START(F("adding endpoints"));
        DEBUG_LIST_VAL(F("endpoint count"), _endPointCount);
        DEBUG_LIST_END;
        for (int i = 0; i < _endPointCount; i++) {
          Object *endPoint = _endPoints[i];
          const char * name = endPoint->name;
          DEBUG_VAL(F("adding endpoints for"), F("name"), name);
          String path = _prefix + String(name);
          DEBUG_VAL(F("adding GET handler"), F("path"), path);
          _pServer->on(
            path,
            HTTP_GET,
            [=]() {
              DEBUG_VAL(F("GET"), F("path"), path);
              _withDoc([=](JsonDocument *pDoc) {
                JsonObject obj = pDoc->to<JsonObject>();
                endPoint->serialize(&obj);
                String json;
                size_t length = serializeJson(*pDoc, json);
                DEBUG_LIST_START(F("sending JSON"));
                DEBUG_LIST_VAL(F("length"), length);
                DEBUG_LIST_VAL(F("json"), json);
                DEBUG_LIST_END;
                _pServer->send(200, "application/json", json);
              });
            }
          );
          DEBUG_VAL(F("adding POST handler"), F("path"), path);
          _pServer->on(
            path,
            HTTP_POST,
            [=]() {
              String json = _pServer->arg("plain");
              DEBUG_LIST_START(F("POST"));
              DEBUG_LIST_VAL(F("path"), path);
              DEBUG_LIST_VAL(F("json"), json);
              DEBUG_LIST_END;
              _withDoc([=](JsonDocument *pDoc) {
                JsonObject obj = pDoc->to<JsonObject>();
                DeserializationError error = deserializeJson(*pDoc, json);
                if (error) {
                  DEBUG_LIST_START(F("Failed to deserialize POST data"));
                  DEBUG_LIST_VAL(F("error"), error.c_str());
                  DEBUG_LIST_VAL(F("json"), json);
                  DEBUG_LIST_END;
                  _pServer->send(400, "text/plain", "400: Invalid Request");
                  return;
                }
                endPoint->deserialize(&obj);
                _pServer->send(200, "text/plain", "200: Success");
              });
            }
          );
        }
      }
  };
};

#endif
