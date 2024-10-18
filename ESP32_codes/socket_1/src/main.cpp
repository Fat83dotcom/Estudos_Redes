#include "tools.h"
#include "connect_tool.h"

#define led_1 2

LightState *st = new LightState();

void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(ligth, OUTPUT);
  Serial.begin(9600);
  WifiManager();
  espServer.begin();
}

void socketServer() {
  espClient = espServer.accept();           // aguarda por conexões de clientes

  if (espClient) {                          // se um cliente conectar
    Serial.println("Novo cliente.");        // imprime uma mensagem na porta serial
    String currentLine = "";                // cria uma string para armazenar dados recebidos do cliente
    digitalWrite(led_1, 1);
    while (espClient.connected()) {         // enquanto o cliente estiver conectado
      if (espClient.available()) {          // se há bytes para serem lidos do cliente
        char c = espClient.read();          // lê um byte, então
        Serial.write(c);                    // imprime na porta serial
        if (c == '\n') {                    // se o byte é um caractere de nova linha
          // se a linha atual está vazia, significa que há dois caracteres de nova linha em sequência.
          // esse é o fim do pedido HTTP do cliente, então envia uma resposta:
          if (currentLine.length() == 0) {
            // Cabeçalhos HTTP sempre começam com um código de resposta (ex. HTTP/1.1 200 OK)
            // e um content-type para que o cliente saiba o que está vindo, seguido por uma linha em branco:
            espClient.println("HTTP/1.1 200 OK");
            espClient.println("Content-type:text/html");
            espClient.println();
            // o conteúdo da resposta HTTP segue o cabeçalho:
            espClient.print(pageHTML(st->getState()));
            // A resposta HTTP termina com outra linha em branco:
            espClient.println();
            // interrompe o loop while:
            break;
          } else {    // se receber uma nova linha, limpa currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // se receber algo diferente de um retorno de carro
          currentLine += c;      // adiciona ao final de currentLine
        }
        // Verifica se a requisição do cliente foi "GET /H" ou "GET /L":
        st->setState(currentLine);
      }
    }
    // Serial.println(currentLine);
    // encerra a conexão:
    espClient.stop();
    Serial.println("Cliente Desconectado.");
  }
}

void blink() {
  static unsigned long current = millis();
  if ((millis() - current) < 250) {
    digitalWrite(led_1, 1);
  } else {
    digitalWrite(led_1, 0);
  }
  if ((millis() - current) >= 500) {
    current = millis();
  }
}

void loop() {
  blink();
  socketServer();
}
