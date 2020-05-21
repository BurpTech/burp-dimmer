#ifndef HttpServer_hpp
#define HttpServer_hpp

#include "Debug.hpp"

#include <ESP8266WebServer.h>

#define _HTTP_SERVER_PORT 80

class HttpServer {
  using f_onSettings = std::function<void(const char *ssid, const char *password)>;

  static ESP8266WebServer _server;
  static f_onSettings _onSettings;
  static File _uploadFile;
  static String _getContentType(String path);
  static void _handleFileRead(String path);
  static void _handleFileUpload();
  static void _handleSettings();

  public:
    static void setup(f_onSettings onSettings);
    static void loop();
};

HttpServer::f_onSettings HttpServer::_onSettings;
File HttpServer::_uploadFile;
ESP8266WebServer HttpServer::_server(_HTTP_SERVER_PORT);

void HttpServer::setup(f_onSettings onSettings) {
  _onSettings = onSettings;

  _server.on(
      "/settings",
      HTTP_GET,
      [=](){ _handleFileRead("/settings.html"); });

  _server.on(
      "/settings",
      HTTP_POST,
      _handleSettings);

  _server.on(
      "/upload",
      HTTP_GET,
      [](){ _handleFileRead("/upload.html"); });

  _server.on(
      "/upload",
      HTTP_POST,
      [](){ _server.send(200); },
      _handleFileUpload);

  _server.onNotFound([=](){ _handleFileRead(_server.uri()); });

  _server.begin();

  DEBUG_VAL(F("HTTP Server started"), F("port"), _HTTP_SERVER_PORT);
}

void HttpServer::loop() {
  _server.handleClient();
}

String HttpServer::_getContentType(String path) {
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

void HttpServer::_handleFileRead(String path) {
  DEBUG_VAL(F("start"), F("path"), path);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  DEBUG_VAL(F("adjusted"), F("path"), path);
  String contentType = _getContentType(path);
  DEBUG_VAL(F("checked content type"), F("contentType"), contentType);
  if (Storage::exists(path)) {
    File file = Storage::open(path, "r");
    size_t sent = _server.streamFile(file, contentType);
    DEBUG_VAL(F("file streamed"), F("sent bytes"), sent);
    file.close();
    return;
  }
  DEBUG_MSG(F("file not found"));
  _server.send(404, "text/plain", "404: Not Found");
}

void HttpServer::_handleSettings() {
  char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE] = "";
  char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE] = "";
  DEBUG_VAL(F("POST data received"), F("raw"), _server.arg("plain")); 
  if (!_server.hasArg("ssid") ||
      !_server.hasArg("password") ||
      _server.arg("ssid") == NULL ||
      _server.arg("password") == NULL) {
      _server.send(400, "text/plain", "400: Invalid Request");
      return;
  }
  _server.sendHeader("Location", "/success.html");
  _server.send(303);
  _server.arg("ssid").toCharArray(ssid, WIFI_CONFIG_SSID_BUFFER_SIZE);
  _server.arg("password").toCharArray(password, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
  _onSettings(ssid, password);
}

void HttpServer::_handleFileUpload() {
  HTTPUpload &upload = _server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    DEBUG_VAL(F("started upload"), F("filename"), filename);
    if (!filename.startsWith("/")) filename = "/" + filename;
    DEBUG_VAL(F("adjusted filename"), F("filename"), filename);
    _uploadFile = Storage::open(filename, "w");
    DEBUG_VAL(F("opened file"), F("handle"), _uploadFile);
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    DEBUG_LIST_START(F("received chunk"));
    DEBUG_LIST_VAL(F("bytes"), upload.currentSize);
    DEBUG_LIST_VAL(F("file handle"), _uploadFile);
    DEBUG_LIST_END;
    if (_uploadFile) {
      size_t bytesWritten = _uploadFile.write(upload.buf, upload.currentSize);
      DEBUG_VAL(F("bytes written"), F("bytesWritten"), bytesWritten);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (_uploadFile) {
      DEBUG_VAL(F("upload complete"), F("total size"), upload.totalSize);
      _uploadFile.close();
      _server.sendHeader("Location", "/success.html");
      _server.send(303);
    } else {
      _server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}

#endif
