// Importamos
// Libreria Básica para conectividad WiFi con chip ESP8266
#include <ESP8266WiFi.h>
// Libreria básica para conexiones con el protocolo HTTP
#include <ESP8266HTTPClient.h>

// Parametros de conexión
const char* ssid = "MOVISTAR_FB28_EXT";
const char* password = "ubypp46915";
const char* host = "192.168.1.36";
const uint16_t port = 3000;
const String path = "/";

void setup() {
    // Inicializamos el puerto serie a 115200 baudios, para informar por medio del monitor serie del IDE.
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Conectando a la red ");
    Serial.println(ssid);

    // Inicialización de Wifi con los parámetros.
    WiFi.begin(ssid,password);

    // Cuando la conexión se establece con éxito, la propiedad status del objeto Wifi pasa a ser WL_CONNECTED
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    // Y la propiedad localIP recoge la dirección IP asignada.
    Serial.println("");
    Serial.println("Conexion realizada con exito");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("");

    delay(500);
}
    // Creamos un objeto de tipo HTTPClient llamado http para las comunicaciones con protocolo http.
    HTTPClient http;

    // Contador para ejemplo
    int dato = 0;
    
void loop() {
    // Configuración de la conexión HTTP con parámetros host, port y url.
    Serial.println("[HTTP] Configurando comunicacion.");
    http.begin(host,port,path);

    // GET
    
    // Iniciamos comunicación enviando cabecera GET y recogiendo el STATUS code enviado por el servidor en la variable httpcode.
    Serial.print("[HTTP] GET ");
    Serial.println(host+path);
    
    int httpcode = http.GET();

    // Si el STATUS recibido es válido, mostrar BODY, sino, el código de error.
    // El body se captura con http.getString();

    if (httpcode){
      // Se ha recibido respuesta del servidor.
      Serial.print("[HTTP] ");
      Serial.println(httpcode);
      // Si la respuesta no es de error 
      if(httpcode == HTTP_CODE_OK) {
          String body = http.getString();
          Serial.println(body);
      } else {
          Serial.print("[HTTP] Error:");
          Serial.println(http.errorToString(httpcode).c_str());
      };
    };

    http.end();
    
    delay(3000);

    // POST

    String datoString = String(dato);
    String bodyString = "Dato numero " + datoString;
    http.addHeader("Content-Type", "text/plain");
    http.POST(bodyString);
    http.end();
    dato +=1;
    delay(3000);
    
    
    };
 
