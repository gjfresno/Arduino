
#include <DHTesp.h>
#include <WiFi.h>
#include <PubSubClient.h>

// SSID/Password Wifi
const char* ssid = "Fibertel WiFi096 2.4GHz";
const char* password = "00429543203";

// La ip donde esta el broker MQTT
const char* mqtt_server = "192.168.0.103";

WiFiClient espClient;
PubSubClient client(espClient);
long value = 0;
const int ledPin = 2;

DHTesp    Dht;
/** Pin number for DHT11 data pin */
const int dhtPin = 5;

void setup() 
{
  // Inicializacion del puerto serial
  Serial.begin(115200);

  // Inicializacion de WiFi
  setup_wifi();

  // Inicializacion del server MQTT
  client.setServer(mqtt_server, 1883);

  // Configuro un SUB
  client.setCallback(callback);

  // Configuro el pin como salida
  pinMode(ledPin, OUTPUT);

  Dht.setup(dhtPin, DHTesp::DHT11);
  Serial.println("DHT initiated");
}

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) 
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "output") // Comparo el tag 
  {
    Serial.print("Changing output to ");
    if(messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      if(messageTemp == "off")
      {
        Serial.println("off");
        digitalWrite(ledPin, LOW);
      }
    }
  }
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) 
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("output");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char Temperatura[20];
char Temperatura2[20];
char Humedad[20];
char Buffer[100];
                                                                                                                  

bool DHT_GetMessure() 
{
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  TempAndHumidity newValues = Dht.getTempAndHumidity();
  // Check if any reads failed and exit early (to try again).
  if (Dht.getStatus() != 0) {
    Serial.println("DHT11 error status: " + String(Dht.getStatusString()));
    return false;
  }

  sprintf(Temperatura, "%d", (int)newValues.temperature);
  sprintf(Temperatura2, "%d", (int)newValues.temperature * 2);
  sprintf(Humedad, "%f", newValues.humidity);
  sprintf(Buffer, "T: %s H: %s", Temperatura, Humedad);

  Serial.println(Buffer);

  // Realizo la publicacion con el TAG Temperatura y el dato Buffer
  client.publish("Temperatura", Temperatura);
  client.publish("Temp", Temperatura2);
  client.publish("Humedad", Humedad);

  return true;
}

void loop() 
{
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    DHT_GetMessure();

    Serial.println("2seg");

    delay(2000);
}
