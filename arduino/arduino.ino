#include <WiFiNINA.h>
#include <SD.h>
#include <SPI.h>

// WiFi credentials
const char* ssid     = "TUO_SSID";
const char* password = "TUA_PASSWORD";

// SD chip select pin per MKR SD Proto Shield
const int SD_CS = 4;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connessione WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Inizializzazione SD
  if (!SD.begin(SD_CS)) {
    Serial.println("SD init failed!");
    while (true);
  }
  Serial.println("SD ready.");

  server.begin();
  Serial.println("Server started.");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = "";
  while (client.connected() && client.available()) {
    char c = client.read();
    request += c;
    if (request.endsWith("\r\n\r\n")) break;
  }

  // Estrai il path dalla request
  String path = "/INDEX.HTM";
  int start = request.indexOf("GET ") + 4;
  int end   = request.indexOf(" HTTP");
  if (start > 3 && end > start) {
    path = request.substring(start, end);
  }
  if (path == "/") path = "/INDEX.HTM";

  // Rimuovi il / iniziale per SD
  String filename = path.substring(1);
  filename.toUpperCase();

  // Determina content-type
  String contentType = "text/plain";
  if (filename.endsWith(".HTM"))  contentType = "text/html";
  if (filename.endsWith(".CSS"))  contentType = "text/css";
  if (filename.endsWith(".JS"))   contentType = "application/javascript";

  // Servi il file
  if (SD.exists(filename.c_str())) {
    File file = SD.open(filename.c_str());
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: " + contentType);
    client.println("Connection: close");
    client.println();
    while (file.available()) {
      client.write(file.read());
    }
    file.close();
  } else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("404 - File not found: " + filename);
  }

  client.stop();
}