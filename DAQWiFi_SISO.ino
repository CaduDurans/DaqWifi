#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Programa do tipo Data Aquisition para placa NodeMCU v3
// Aquisição de dados do tipo MIMO com 2 entradas e 2 saídas

float u1[1]={0};
float y[1]={0};

String u1_value;  
String y1_value;
 
# define DA5 (D5) 

// Nome do roteador WiFi
const char* ssid = "";
// Senha do roteador WiFi
const char* password = "";

ESP8266WebServer server(80); // Configura protocolo TCP através da porta 80

void inputSignal() // Função auxiliar
{
  y[0] = analogRead(A0)*(3.3/1023.0); // Entrada analógica

  String y_value = String (y[0]);
  y_value += (server.method() == HTTP_POST);
  server.send(200, "text/plain", y_value); // envia o valor da entrada em forma de string para o endereço url
}

void outputSignal()
{
  String u1_value = u1_value;
  u1_value += (server.method() == HTTP_GET);
  u1_value += server.arg("u1"); // lê a string que está na url

   u1[0]=u1_value.toFloat(); // converte string para float

    if (u1[0]<0) {u1[0]=0;}
    if (u1[0]>3.3) {u1[0]=3.3;}
    u1[0] = u1[0]*(1023/3.3);
    analogWrite(D5,u1[0]);

    server.send(200, "text/plain", u1_value);
}

// -----------------------------------------------------------------------------------------------

void setup(void) {

  pinMode(DA5,OUTPUT);

  digitalWrite(DA5,LOW);

  Serial.begin(115200);
  Serial.setTimeout(5);
  
  // Configura a comunicação Wifi
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Esperando pela conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Mostra o endereço IP alocado

    if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
    MDNS.addService("http", "tcp", 80);
  }

// Adiciona ao IP dois endereços URL para entrada e saída de dados
  server.on("/input/", inputSignal);
  server.on("/output/", outputSignal);

   // Wait for connection
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) {//wait 10 seconds
    delay(500);
  }

  server.begin(); // Inicia o servidor

}

// -----------------------------------------------------------------------------------------------
void loop(void) 
{  
    server.handleClient(); /* Função necessária para o funcionamento das 
                              usadas neste programa como WebServer*/
}
