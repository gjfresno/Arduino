#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Fibertel WiFi096 2.4GHz";
const char* password = "00429543203";

WebServer server(80);

const int led = 2;

const char HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html>
<head>
<title>Page Title</title>
</head>
<body>

<h1>Hola desde esp32!</h1>
<p> Hola mundo </p>

</body>
</html>
)rawliteral";

void handleRoot() 
{
  digitalWrite(led, 1);

  server.send(200, "text/plain", HTML);
}


void handleNotFound() 
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) 
    {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setup(void) 
{
  // Configuramos el led como salida
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  // Configuramos el puerto serial
  Serial.begin(115200);

  // Configuramos el wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Escribimos en pantalla ""
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) 
  {
      Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/ledon", []() 
  {
      digitalWrite(led, 1);
      server.send(200, "text/plain", "LED ON");
  });

  server.on("/ledoff", []() 
  {
      digitalWrite(led, 0);
      server.send(200, "text/plain", "LED OFF");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
