#ifndef TOOLS_H
#define TOOLS_H
#include <Arduino.h>

#define ligth 23

class LightState;

class LightState {
  private:
  String state = "";
  public:
  LightState(){}

  void setState(String flag) {
    if (flag.endsWith("GET /H?")) {
      Serial.println(flag);
      digitalWrite(ligth, 1); 
      this->state = "Ligado";
    } else if (flag.endsWith("GET /L?")) {
      Serial.println(flag);
      digitalWrite(ligth, 0); 
      this->state = "Desligado";
    }
  }

  String getState() {
    return this->state;
  }
};

int square(int x){
  return (x * x);
}

char *convertInt(int num) {
  char *buffer = (char *) malloc(32 * sizeof(char));
  if (buffer == NULL) {
    return NULL;
  }
  itoa(num, buffer, 10);
  return buffer;
}

String pageHTML(String state) {
  String text = "<!DOCTYPE html>\
<html lang=\"pt-br\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Esp32 Skills</title>\
    <style>\
        body{\
            height: 100vh;\
            display: flex;\
            flex-direction: column;\
            justify-content: center;\
            color: lightgray;\
            background-color: black;\
            margin: 0 auto;\
            padding: 0;\
        }\
        .center {\
            text-align: center;\
        }\
        .btn-liga {\
            color: green;\
        }\
        .btn-desliga {\
            color: red;\
        }\
        .btn-liga a {\
            color: green;\
        }\
        .btn-desliga a {\
            color: red;\
        }\
        .btn {\
            padding: 10px;\
            margin: 10px;\
            width: 25%;\
        }\
        .btn a {\
            font-size: large;\
            text-decoration: none;\
        }\
        .btn-container {\
            display: flex;\
            flex-direction: column;\
        }\
    </style>\
</head>\
<body class=\"center\">\
    <div>\
        <h1>Controle Da Casa</h1>\
        <h3>Luz do Quarto</h3>\
        <h4>" + state + "</h4>\
        <div class=\"btn-container\">\
            <form action=\"/H\" method=\"get\">\
                <button class=\"btn btn-liga\" type=\"submit\">Liga</button>\
            </form>\
            <form action=\"/L\" method=\"get\">\
                <button class=\"btn btn-desliga\" type=\"submit\">Desliga</button>\
            </form>\
        </div>\
    </div>\
</body>\
</html>";
  return text;
}


#endif