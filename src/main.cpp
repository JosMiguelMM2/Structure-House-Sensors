#include <Arduino.h>
#include <WiFi.h>

// Configuración de la red Wi-Fi
const char *ssid = "Galaxy Note10+";
const char *password = "ectWy729nc.042swVGT";


void setup() {
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

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hola mundo");
}
