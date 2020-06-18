#pragma once

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "../Debug.hpp"

#include "Object.hpp"

namespace BurpDimmer {
  namespace Json {

    class HttpApi {
      public:
        HttpApi(
          String prefix,
          const f_withDoc withDoc,
          Object **endPoints,
          ESP8266WebServer & server
        ) :
          _prefix(prefix),
          _withDoc(withDoc),
          _endPoints(endPoints),
          _server(server) {
        }

        void setup() {
          DEBUG_PRINT("adding endpoints");
          Object ** _currentEndPoint = _endPoints;
          while (*_currentEndPoint) {
            Object *endPoint = (*_currentEndPoint);
            const char * name = endPoint->name;
            DEBUG_PRINT("adding endpoints for: name: [%s]", name);
            String path = _prefix + String(name);
            DEBUG_PRINT("adding GET handler: path: [%s]", path.c_str());
            _server.on(
              path,
              HTTP_GET,
              [=]() {
                DEBUG_PRINT("GET: path: [%s]", path.c_str());
                _withDoc([=](JsonDocument & doc) {
                  JsonObject obj = doc.to<JsonObject>();
                  endPoint->serialize(obj);
                  String json;
                  size_t length = serializeJson(doc, json);
                  DEBUG_PRINT("sending JSON: length: [%d]: json: [%s]", length, json.c_str());
                  _server.send(200, "application/json", json);
                });
              }
            );
            DEBUG_PRINT("adding POST handler: path: [%s]", path.c_str());
            _server.on(
              path,
              HTTP_POST,
              [=]() {
                String json = _server.arg("plain");
                DEBUG_PRINT("POST: path: [%s]: json: [%s]", path.c_str(), json.c_str());
                _withDoc([=](JsonDocument & doc) {
                  JsonObject obj = doc.to<JsonObject>();
                  DeserializationError error = deserializeJson(doc, json);
                  if (error) {
                    DEBUG_PRINT("Failed to deserialize POST data: error: [%s]: json: [%s]", error.c_str(), json.c_str());
                    _server.send(400, "text/plain", "400: Invalid Request");
                    return;
                  }
                  endPoint->deserialize(obj);
                  _server.send(200, "text/plain", "200: Success");
                });
              }
            );
            _currentEndPoint++;
          }
        }

      private:
        String _prefix;
        const f_withDoc _withDoc;
        Object **_endPoints;
        ESP8266WebServer & _server;
    };

  }
}
