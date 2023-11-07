#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Configuración de la red Wi-Fi
//const char *ssid = "Galaxy Note10+";
//const char *password = "ectWy729nc.042swVGT";
// const char *ssid = "U-SIGLOXXI";
// const char *password = "UdeCsigloXXI";
//  const char *ssid = "ERIKA MENDEZ";
//  const char *password = "Or7oIOZ*1G98OiRL";
const char *ssid = "FAMILIA SB";
const char *password = "88180137";
const char *host = "192.168.20.95"; //"192.168.126.75";//
const int port = 3000;

/*pines leds*/
byte led1 = 32;
byte led2 = 33;
byte led3 = 25;
byte led4 = 26;
byte led5 = 27;

void encenderLeds(int led)
{
  digitalWrite(led, HIGH);
  delay(10);
}

void apagarLeds(int led)
{
  digitalWrite(led, LOW);
  delay(10);
}

// metodo GET
String GET(String hostS)
{
  String response;
  HTTPClient http;
  // URL de la página web a la que deseas acceder
  http.begin(hostS);
  int httpResponseCode = http.GET(); // Realiza una solicitud GET
  if (httpResponseCode > 0)
  {
    response = http.getString(); // Obtiene la respuesta del servidor
    http.end();                  // Cierra la conexión HTTP
  }
  return response;
}

void controlaR(String jsonData)
{
  // Tamaño máximo del JSON que esperas
  const size_t capacity = JSON_ARRAY_SIZE(5) + 5 * JSON_OBJECT_SIZE(3) + 256;

  // Parsea el JSON
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, jsonData);

  // Accede a los datos y controla los LEDs
  for (size_t i = 0; i < doc.size(); i++)
  {
    const String nombre = doc[i]["nombre"];
    const String statusLed = doc[i]["statusLed"];
    Serial.println(nombre);
    Serial.println(statusLed);
    delay(600);
    // Aquí puedes realizar el control de los LEDs según los datos obtenidos
    if (statusLed == "HIGH")
    {
      if (nombre == "Led1")
      {
        encenderLeds(led1);
      }
      if (nombre == "Led2")
      {
        encenderLeds(led2);
      }
      if (nombre == "Led3")
      {
        encenderLeds(led3);
      }
      if (nombre == "Led4")
      {
        encenderLeds(led4);
      }
      if (nombre == "Led5")
      {
        encenderLeds(led5);
      }
    }
    if (statusLed == "LOW")
    {
      if (nombre == "Led1")
      {
        apagarLeds(led1);
      }
      if (nombre == "Led2")
      {
        apagarLeds(led2);
      }
      if (nombre == "Led3")
      {
        apagarLeds(led3);
      }
      if (nombre == "Led4")
      {
        apagarLeds(led4);
      }
      if (nombre == "Led5")
      {
        apagarLeds(led5);
      }
    }
  }
}

void POST(String path, int dato, String name)
{
  HTTPClient http;

  http.begin(host, port, path);

  http.addHeader("Content-Type", "application/json");

  String json = "{\"name\":\"" + name + "\", \"temperature\":" + String(dato) + "}";
  Serial.println(json);
  int httpCode = http.POST(json);

  if (httpCode > 0)
  {
    Serial.println("HTTP code: " + String(httpCode));

    if (httpCode == 200)
    {
      Serial.println("Post created successfully");
    }
    else
    {
      Serial.println("Post creation failed");
    }
  }
  else
  {
    Serial.println("Error connecting to server");
  }

  http.end();

  delay(500);
}
void setup()
{
  Serial.begin(9600);
  // Conéctate a la red Wi-Fi
  WiFi.begin(ssid, password);
  delay(200);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }

  Serial.println("Conexión exitosa a la red Wi-Fi");
  Serial.print("Dirección IP asignada por el router: ");
  Serial.println(WiFi.localIP());

  /*Establecer los pines de los leds*/
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop()
{
  String hostS = "http://" + String(host) + ":" + String(port) + "/Stado";
  Serial.println(hostS);
  String respuesta = GET(hostS);
  Serial.println(respuesta);
  controlaR(respuesta);
  delay(10);
  String host2 = "http://" + String(host) + ":" + String(port) + "/Newta";
  Serial.println(host2);
  // POST(host2, 2, "Desde Esp32");
}
