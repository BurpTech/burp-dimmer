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
        DEBUG_PRINT("adding endpoints: endpoint count: [%d]", _endPointCount);
        for (int i = 0; i < _endPointCount; i++) {
          Object *endPoint = _endPoints[i];
          const char * name = endPoint->name;
          DEBUG_PRINT("adding endpoints for: name: [%s]", name);
          String path = _prefix + String(name);
          DEBUG_PRINT("adding GET handler: path: [%s]", path.c_str());
          _pServer->on(
            path,
            HTTP_GET,
            [=]() {
              DEBUG_PRINT("GET: path: [%s]", path.c_str());
              _withDoc([=](JsonDocument *pDoc) {
                JsonObject obj = pDoc->to<JsonObject>();
                endPoint->serialize(&obj);
                String json;
                size_t length = serializeJson(*pDoc, json);
                DEBUG_PRINT("sending JSON: length: [%d]: json: [%s]", length, json.c_str());
                _pServer->send(200, "application/json", json);
              });
            }
          );
          DEBUG_PRINT("adding POST handler: path: [%s]", path.c_str());
          _pServer->on(
            path,
            HTTP_POST,
            [=]() {
              String json = _pServer->arg("plain");
              DEBUG_PRINT("POST: path: [%s]: json: [%s]", path.c_str(), json.c_str());
              _withDoc([=](JsonDocument *pDoc) {
                JsonObject obj = pDoc->to<JsonObject>();
                DeserializationError error = deserializeJson(*pDoc, json);
                if (error) {
                  DEBUG_PRINT("Failed to deserialize POST data: error: [%s]: json: [%s]", error.c_str(), json.c_str());
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
