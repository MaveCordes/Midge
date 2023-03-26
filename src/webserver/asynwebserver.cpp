#include <header.h>
#include <fridge.h>

void notFound(AsyncWebServerRequest *request)
{
  if (!dis_sd)
  {
    data_file_main = SD.open(request->url().c_str());

    if (request->url().endsWith(F(".txt")) || (request->url().endsWith(F(".csv"))) || (request->url().endsWith(F(".TXT"))) || (request->url().endsWith(F(".CSV"))))
    {
      request->send(SD, request->url(), String(), true);
    }
    else if (data_file_main.isDirectory())
    {
      sd_directory_bool = true;
      sd_directory = request->url().c_str();
      request->send_P(200, "text/html", sdcard_html, processor);
      sd_directory_bool = false;
    }
  }
  else
  {
    // request->redirect("/");
    request->send_P(404, PSTR("text/plain"), PSTR("Not found"));
  }
}

void async_server_on()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request)
            { if(!request->authenticate(http_username.c_str(), http_password.c_str()))
              return request->requestAuthentication();
              request->send_P(200, "text/html", settings_html, processor); });
  server.on("/sdcard", HTTP_GET, [](AsyncWebServerRequest *request)
            { if(!request->authenticate(http_username.c_str(), http_password.c_str()))
              return request->requestAuthentication();
              request->send_P(200, "text/html", sdcard_html, processor); });
  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request)
            { if(!request->authenticate(http_username.c_str(), http_password.c_str()))
              return request->requestAuthentication();
              request->send_P(200, "text/html", about_html, processor); });
  server.on("/cam", HTTP_GET, [](AsyncWebServerRequest *request)
            { if(!request->authenticate(http_username.c_str(), http_password.c_str()))
              return request->requestAuthentication();
              request->send_P(200, "text/html", cam_html, processor); });
  server.on("/iSerial", HTTP_GET, [](AsyncWebServerRequest *request)
            { if(!request->authenticate(http_username.c_str(), http_password.c_str()))
              return request->requestAuthentication();
              request->send_P(200, "text/html", iSerial_html, processor); });
  server.onNotFound(notFound);
  // Alternative for .onNotFound
  // server.serveStatic("/", SD, "");
}

void store_value(const char *store_temp, uint8_t store_int)
{
  preferences.begin("stored_values", false);
  preferences.putUChar(store_temp, store_int);
  preferences.end();
}

void store_toggle(const char *store_temp, bool store_bool)
{
  preferences.begin("stored_values", false);
  preferences.putBool(store_temp, store_bool);
  preferences.end();
}

void initWebSocket()
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

String printDirectory(File dir)
{
  dir.rewindDirectory();
  while (true)
  {
    File entry = dir.openNextFile();
    String file_name = entry.name();
    if (!entry)
    {
      break;
    }
    if (file_name.startsWith("/.") || (file_name.indexOf("_") > 0) || (file_name.startsWith("/System")))
    {
    }
    else if (entry.isDirectory())
    {
      file_name.remove(0, 1);
      response += String("<a href='") + String(entry.name()) + String("'>") + String(file_name) + String("</a>") + String("</br>");
    }
    else
    {
      file_name.remove(0, 1);
      response += String("<a href='") + String(entry.name()) + String("'>") + String(file_name) + String("</a>") + String("</br>");
    }
    entry.close();
  }
  return response;
}