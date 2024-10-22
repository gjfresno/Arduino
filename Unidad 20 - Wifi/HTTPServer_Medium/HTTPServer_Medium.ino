#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Fibertel WiFi096 2.4GHz";
const char* password = "00429543203";

WebServer server(80);

const int led = 2;

char  Buffer[1000];
char  Estado_Led = 0;

const char HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html>
<head>
<style>
.button {
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}

.button1 {background-color: #FF0000;} /* RED */
.button2 {background-color: #00FF00;} /* GREEN */
</style>
</head>
<body>

<h1>Pagina Web Test &#128512;</h1>
<p>El estado del led es: %d</p>
<p>La IP del ESP32 es: %s</p>

<button onclick="window.location.href='/ledon'" class="button button2">ENCENDER</button>
<button onclick="window.location.href='/ledoff'" class="button button1">APAGAR</button>

<h2>Text input fields</h2>

<canvas id="myCanvas" width="300" height="150" style="border:1px solid grey"></canvas>

<form>
  <label for="fname">First name:</label><br>
  <input type="text" id="fname" name="fname" value="John"><br>
  <label for="lname">Last name:</label><br>
  <input type="text" id="lname" name="lname" value="Doe">
</form>

</body>
</html>)rawliteral";

void HTML_Send() 
{
  // char buffer[] = "Gustavo";
  // char bufferOut[] = "Gustavo";
  // sprintf(bufferOut, HTML, buffer);

  sprintf(Buffer, HTML, Estado_Led, WiFi.localIP());
  
  server.send(200, "text/html", Buffer);
  
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
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
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

  server.on("/", HTML_Send);

  server.on("/ledon", []() 
  {
      digitalWrite(led, 1);
      Estado_Led = 1;
      HTML_Send();
      //server.send(200, "text/plain", "LED ON");
  });

  server.on("/ledoff", []() 
  {
      digitalWrite(led, 0);
      Estado_Led = 0;
      HTML_Send();
      //server.send(200, "text/plain", "LED OFF");
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
