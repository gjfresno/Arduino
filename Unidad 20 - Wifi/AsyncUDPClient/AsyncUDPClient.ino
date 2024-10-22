#include "WiFi.h"
#include "AsyncUDP.h"

const char* ssid = "Fibertel WiFi096 2.4GHz";
const char* password = "00429543203";

AsyncUDP udp;

void setup()
{
    // Inicializacion del puerto serial
    Serial.begin(115200);

    // Inicializacion del modulo wifi en station (cliente wifi)
    WiFi.mode(WIFI_STA);

    // Configura ssid y password del wifi
    WiFi.begin(ssid, password);

    // Espera hasta poder conectarse
    if (WiFi.waitForConnectResult() != WL_CONNECTED) 
    {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }

    Serial.println("WiFi Conectado");
    
    // Abre una conexion de escucha para la recepcion de datos
    if(udp.connect(IPAddress(192,168,0,103), 4000)) {
        Serial.println("UDP connected");
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
        //Send unicast
        udp.print("Hello Server!");
    }
}

// LOOP 
void loop()
{
    delay(1000);
    
    //Envia broadcast sobre le puerto 4000
    udp.broadcastTo("Hola, hay alguien escuchando?", 4000);
}
