#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP8266-AP";
const char *password = "123456789";
ESP8266WebServer server(80);
String homePage = "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <link rel=\"stylesheet\" href=\"styles.css\">\
    <title>Navbar Example</title>\
    <style>\
        body {\
            margin: 0;\
            font-family: Arial, sans-serif;\
        }\
        .navbar {\
            background-color: #333;\
            overflow: hidden;\
        }\
        .navbar ul {\
            list-style-type: none;\
            margin: 0;\
            padding: 0;\
            overflow: hidden;\
        }\
        .navbar li {\
            float: left;\
        }\
        .navbar a {\
            display: block;\
            color: white;\
            text-align: center;\
            padding: 14px 16px;\
            text-decoration: none;\
        }\
        .navbar a:hover {\
            background-color: #ddd;\
            color: black;\
        }\
    </style>\
</head>\
<body>\
    <nav class=\"navbar\">\
        <ul>\
            <li><a href=\"/\">Acasă</a></li>\
            <li><a href=\"/aboutUs\">Contact</a></li>\
            <li><a href=\"/clients\">Client</a></li>\
        </ul>\
    </nav>\
    <p> Senzorul nostru oferă o soluție non-invazivă, eliminând necesitatea verificărilor manuale și deschizând calea către o gestionare mai simplă a consumului de energie. În același timp, interface-ul intuitiv și accesibil al platformei noastre online vine în ajutorul persoanelor cu dizabilități, facilitându-le accesul la informațiile esențiale despre consum.</p>\
    <p>Pentru persoanele în vârstă sau cu dizabilități, \"SmartMeter\" nu este doar o inovație tehnologică, ci și o soluție care le oferă independență în monitorizarea și controlul consumului de energie. Aceasta este o treaptă importantă spre crearea unei societăți mai incluzive.<\p>\
    <p>Vă invităm să vă alăturați inițiativei noastre de a face tehnologia utilă pentru toți și să contribuim împreună la crearea unui mediu în care fiecare individ poate beneficia de avantajele unei gestionări inteligente a consumului de energie.<\p>\
</body>\
</html>";

String aboutUsPage = "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <link rel=\"stylesheet\" href=\"styles.css\">\
    <title>Navbar Example</title>\
    <style>\
        body {\
            margin: 0;\
            font-family: Arial, sans-serif;\
        }\
        .navbar {\
            background-color: #333;\
            overflow: hidden;\
        }\
        .navbar ul {\
            list-style-type: none;\
            margin: 0;\
            padding: 0;\
            overflow: hidden;\
        }\
        .navbar li {\
            float: left;\
        }\
        .navbar a {\
            display: block;\
            color: white;\
            text-align: center;\
            padding: 14px 16px;\
            text-decoration: none;\
        }\
        .navbar a:hover {\
            background-color: #ddd;\
            color: black;\
        }\
    </style>\
</head>\
<body>\
    <nav class=\"navbar\">\
        <ul>\
            <li><a href=\"/\">Acasă</a></li>\
            <li><a href=\"/aboutUs\">Contact</a></li>\
            <li><a href=\"/clients\">Client</a></li>\
        </ul>\
    </nav>\
    <p> Senzorul nostru oferă o soluție non-invazivă, eliminând necesitatea verificărilor manuale și deschizând calea către o gestionare mai simplă a consumului de energie. În același timp, interface-ul intuitiv și accesibil al platformei noastre online vine în ajutorul persoanelor cu dizabilități, facilitându-le accesul la informațiile esențiale despre consum.</p>\
    <p>Pentru persoanele în vârstă sau cu dizabilități, \"SmartMeter\" nu este doar o inovație tehnologică, ci și o soluție care le oferă independență în monitorizarea și controlul consumului de energie. Aceasta este o treaptă importantă spre crearea unei societăți mai incluzive.<\p>\
    <p>Vă invităm să vă alăturați inițiativei noastre de a face tehnologia utilă pentru toți și să contribuim împreună la crearea unui mediu în care fiecare individ poate beneficia de avantajele unei gestionări inteligente a consumului de energie.<\p>\
</body>\
</html>";

String clientsPage = "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <link rel=\"stylesheet\" href=\"styles.css\">\
    <title>Navbar Example</title>\
    <style>\
        body {\
            margin: 0;\
            font-family: Arial, sans-serif;\
        }\
        .navbar {\
            background-color: #333;\
            overflow: hidden;\
        }\
        .navbar ul {\
            list-style-type: none;\
            margin: 0;\
            padding: 0;\
            overflow: hidden;\
        }\
        .navbar li {\
            float: left;\
        }\
        .navbar a {\
            display: block;\
            color: white;\
            text-align: center;\
            padding: 14px 16px;\
            text-decoration: none;\
        }\
        .navbar a:hover {\
            background-color: #ddd;\
            color: black;\
        }\
    </style>\
</head>\
<body>\
    <nav class=\"navbar\">\
        <ul>\
            <li><a href=\"/\">Acasă</a></li>\
            <li><a href=\"/aboutUs\">About Us</a></li>\
            <li><a href=\"/clients\">Client</a></li>\
        </ul>\
    </nav>\
  ";

String clientResponse = "";
String *clientResponsePointer = &clientResponse;

int count = 0;

void displayWebsite() {
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Adresa IP a AP-ului: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", homePage);
  });

  server.on("/aboutUs", HTTP_GET, []() {
    server.send(200, "text/html", aboutUsPage);
  });

  server.on("/clients", HTTP_GET, []() {
    server.send(200, "text/html", clientsPage);
  });

  server.on("/clients", HTTP_POST, []() {
    String data = server.arg("data");
    Serial.print("Date primite: ");
    Serial.println(data);

    String htmlResponse = "<div class=\"card\"><div class=\"card-body\">id cliend : 5647204132 ->   " + data;
    htmlResponse += "</div></div>";
    *clientResponsePointer = htmlResponse;

    clientsPage += *clientResponsePointer;
  });

  
}

void setup() {
  Serial.begin(115200);
  displayWebsite();
  server.begin();
}

void loop() {
  server.handleClient();
}