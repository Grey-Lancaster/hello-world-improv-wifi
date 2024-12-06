/*
  -------------------------------------------------------------------------
  ESP32 Improv WiFi Basic Web Server
  -------------------------------------------------------------------------
  Developed with contributions from the amazing open-source community.
  Special thanks to:
    - Grey Lancaster, for his collaboration and dedication.
    - The developers of the ImprovWiFi Library:
        https://github.com/jnthas/Improv-WiFi-Library
    - ChatGPT, for providing guidance, code explanations, and optimizations.
    - The developers of the WiFi and Espressif libraries.
    - The open-source community for their continued support and inspiration.

  This program demonstrates the use of the Improv WiFi Library with an ESP32
  to serve a basic webpage. The server displays chip and network information 
  and responds dynamically based on user interaction.

  Created with gratitude for the technology and passion that make projects
  like this possible. Thank you for your contributions and support!

  -------------------------------------------------------------------------
*/


#define LED_BUILTIN 2

#include <WiFi.h>
#include <Esp.h>
#include "ImprovWiFiLibrary.h"

WiFiServer server(80);
ImprovWiFi improvSerial(&Serial);

char linebuf[80];
int charcount = 0;

void blink_led(unsigned long delayMs, int times) {
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayMs);
  }
}

// Forward declaration of handleHttpRequest
void handleHttpRequest();

void onImprovWiFiErrorCb(ImprovTypes::Error err) {
  server.stop();
  blink_led(2000, 3);
}

void onImprovWiFiConnectedCb(const char *ssid, const char *password) {
  server.begin();
  blink_led(100, 3);
}

bool connectWifi(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);

  while (!improvSerial.isConnected()) {
    // blink_led(500, 1);
  }

  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  improvSerial.setDeviceInfo(
    ImprovTypes::ChipFamily::CF_ESP32,
    "ImprovWiFiLib",
    "1.0.0",
    "BasicWebServer",
    "http://{LOCAL_IPV4}?name=Guest"
  );
  
  improvSerial.onImprovError(onImprovWiFiErrorCb);
  improvSerial.onImprovConnected(onImprovWiFiConnectedCb);
  improvSerial.setCustomConnectWiFi(connectWifi);  // Optional

  blink_led(100, 5);
}

void loop() {
  improvSerial.handleSerial();

  if (improvSerial.isConnected()) {
    handleHttpRequest();
  }
}

void handleHttpRequest() {
  WiFiClient client = server.available();
  if (client) {
    blink_led(100, 1);
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1)
          charcount++;

        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println();
          client.println("<!DOCTYPE HTML><html><body>");
          // client.println("<h1 id=\"welcome\">Welcome!</h1>");
          client.println("<h1>Hello Improv WiFi</h1>");
          client.println("<p>This is a simple webpage served by your ESP32</p>");
          client.println("<h3>Chip Info</h3>");
          client.println("<ul><li>Model:");
          client.println(ESP.getChipModel());
          client.println("</li><li>Cores: ");
          client.println(ESP.getChipCores());
          client.println("</li><li>Revision: ");
          client.println(ESP.getChipRevision());
          client.println("</li></ul>");
          client.println("<h3>Network Info</h3>");
          client.println("<ul><li>SSID: ");
          client.println(WiFi.SSID());
          client.println("</li><li>IP Address: ");
          client.println(WiFi.localIP());
          client.println("</li><li>MAC Address: ");
          client.println(WiFi.macAddress());
          client.println("</li></ul>");
          client.println("<script>const params = new URLSearchParams(document.location.search);document.getElementById('welcome').innerHTML = 'Welcome' + (params.get(\"name\") ? ', ' + params.get('name') : '') + '!';</script>");
          client.println("</body></html>");
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}
