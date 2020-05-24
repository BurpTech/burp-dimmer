#ifndef HttpServer_hpp
#define HttpServer_hpp

#include "Debug.hpp"

#include <ESP8266WebServer.h>

#define _HTTP_SERVER_PORT 80

class HttpServer {
  using f_onSettings = std::function<void(const char *ssid, const char *password)>;

  static f_onSettings _onSettings;
  static File _uploadFile;

  public:
    static ESP8266WebServer server;

    static void setup(f_onSettings onSettings) {
      _onSettings = onSettings;

      server.on(
          "/settings",
          HTTP_GET,
          [=](){ _handleFileRead("/settings.html"); });

      server.on(
          "/settings",
          HTTP_POST,
          _handleSettings);

      server.on(
          "/upload",
          HTTP_GET,
          [](){ _handleFileRead("/upload.html"); });

      server.on(
          "/upload",
          HTTP_POST,
          [](){ server.send(200); },
          _handleFileUpload);

      server.onNotFound([=](){ _handleFileRead(server.uri()); });

      server.begin();

      DEBUG_PRINT("HTTP Server started: port: [%d]", _HTTP_SERVER_PORT);
    }

    static void loop() {
      server.handleClient();
    }

  private:
    static String _getContentType(String path) {
      String pathLower = path;
      pathLower.toLowerCase();
      if (pathLower.endsWith(".html")) return "text/html";
      if (pathLower.endsWith(".css")) return "text/css";
      if (pathLower.endsWith(".js")) return "application/javascript";
      if (pathLower.endsWith(".json")) return "application/json";
      if (pathLower.endsWith(".png")) return "image/png";
      if (pathLower.endsWith(".gif")) return "image/gif";
      if (pathLower.endsWith(".jpg")) return "image/jpeg";
      if (pathLower.endsWith(".jpeg")) return "image/jpeg";
      if (pathLower.endsWith(".ico")) return "image/x-icon";
      return "text/plain";
    }

    static void _handleFileRead(String path) {
      DEBUG_PRINT("start: path: [%s]", path.c_str());
      if (path.endsWith("/")) {
        path += "index.html";
      }
      DEBUG_PRINT("adjusted: path: [%s]", path.c_str());
      String contentType = _getContentType(path);
      DEBUG_PRINT("checked content type: contentType: [%s]", contentType.c_str());
      if (Storage::exists(path)) {
        File file = Storage::open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        DEBUG_PRINT("file streamed: sent bytes: [%d]", sent);
        file.close();
        return;
      }
      DEBUG_PRINT("file not found");
      server.send(404, "text/plain", "404: Not Found");
    }

    static void _handleFileUpload() {
      char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE] = "";
      char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE] = "";
      DEBUG_PRINT("POST data received: raw: %[s]", server.arg("plain").c_str()); 
      if (!server.hasArg("ssid") ||
          !server.hasArg("password") ||
          server.arg("ssid") == NULL ||
          server.arg("password") == NULL) {
          server.send(400, "text/plain", "400: Invalid Request");
          return;
      }
      server.sendHeader("Location", "/success.html");
      server.send(303);
      server.arg("ssid").toCharArray(ssid, WIFI_CONFIG_SSID_BUFFER_SIZE);
      server.arg("password").toCharArray(password, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
      _onSettings(ssid, password);
    }

    static void _handleSettings() {
      HTTPUpload &upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        String filename = upload.filename;
        DEBUG_PRINT("started upload: filename: [%s]", filename.c_str());
        if (!filename.startsWith("/")) filename = "/" + filename;
        DEBUG_PRINT("adjusted filename: [%s]", filename.c_str());
        _uploadFile = Storage::open(filename, "w");
        DEBUG_PRINT("opened file: filename: [%s]", filename.c_str());
        filename = String();
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        DEBUG_PRINT("received chunk: bytes: [%d]", upload.currentSize);
        if (_uploadFile) {
          size_t bytesWritten = _uploadFile.write(upload.buf, upload.currentSize);
          DEBUG_PRINT("bytes written: [%d]", bytesWritten);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (_uploadFile) {
          DEBUG_PRINT("upload complete: total size: [%d]", upload.totalSize);
          _uploadFile.close();
          server.sendHeader("Location", "/success.html");
          server.send(303);
        } else {
          server.send(500, "text/plain", "500: couldn't create file");
        }
      }
    }
};

HttpServer::f_onSettings HttpServer::_onSettings;
File HttpServer::_uploadFile;
ESP8266WebServer HttpServer::server(_HTTP_SERVER_PORT);

#endif
