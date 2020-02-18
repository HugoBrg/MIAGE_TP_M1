/*
 * Auteur : G.Menez
 */
#include <WiFi.h>
#include "net_misc.h"

#include "OneWire.h"
#include "DallasTemperature.h"

/* ---- LED ---- */
// LED will use GPIO pin 19
const int LEDpin = 19;
// Ces variables permettent d'avoir une représentation
// interne au programme du statut "electrique" de l'objet.
// Car on ne peut pas interroge une GPIO pour lui demander !
String LEDState = "off";
String couleur = "";

/* ---- TEMP ---- */
OneWire oneWire(23); // Pour utiliser une entite oneWire sur le port 23
DallasTemperature tempSensor(&oneWire) ; // Cette entite est utilisee par le capteur de temperature

/* ---- LUMI ---- */
int lumiPin = 13;

/* ---- WEB ---- */
// Set web server port number to 80
WiFiServer server(80);

/*--------------------------------*/
String getTemperature() {
  /* Renvoie la String la valeur de temperature
   * Attention !!
   *    J'ai enleve le delay mais convertir prend du temps ! 
   *    moins que les requetes Http.
   */
  float t;
  tempSensor.requestTemperaturesByIndex(0);
  t = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature : "); // for debug
  Serial.print(t);
  Serial.print(" C\n");
  return String(t);
}

/*--------------------------------*/
String getLuminosite(){
  int luminosite = analogRead(lumiPin);  
  Serial.print("Luminosite : "); // for debug
  Serial.print(luminosite);
  Serial.print(" C\n");
  return String(luminosite);
}

/*--------------------------------*/
void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for a serial connection. Needed for native USB port only
  
  // Initialize the output variables as outputs
  pinMode(LEDpin, OUTPUT);
  // Set outputs to LOW
  digitalWrite(LEDpin, LOW);
  
  // Init temperature sensor 
  tempSensor.begin();
 
  connect_wifi(); // Connexion Wifi  
 
  server.begin(); // Lancement du serveur
}

/*--------------------------------*/
void make_html_response_page(WiFiClient client, String mac, String temperature, String luminosite){
    /*
     * Cette fonction transmet au client la page Web qui forme la reponse 
     * à sa requete.
     */
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
                     
    // Web Page heading
    client.println("<!DOCTYPE html><html>");
    //client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    //client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS
    client.println("<head><style>body{font-family: Helvetica; margin: 0px auto; text-align: center; background-color:lightGrey;}");
    client.println("div{display: inline-block;}");
    client.println(".buttong{padding: 16px 40px; font-size: 30px; color:green;}");
    client.println(".buttonr{color: red;}");
    client.println("p{text-align: left; font-size: 20px;font-weight : bold;}");
    client.println("h1, h2{color: #00008b;}</style></head>");

    // Web Page Body
    client.println("<body><h1>ESP32 Web Server</h1>");
    client.println("<h2>Controler la LED, le photoresistor et la temperature via le web.</h2>");
    client.println("<p>Objet Ref : " + mac + "</p>");
    client.println("<p>Temperature : "+ temperature +" C</p>");
    client.println("<p>Luminosite : "+ luminosite +" soleil</p>");
            
    // Display current state, and ON/OFF buttons for LED
    client.println("<p>Statut de la LED : <font color=" + couleur +">" + LEDState + "</font></p>");
    
    // Ctrl buttons
    client.println("<div><a href=\"/ledOn\"><button class=\"buttong\">Push for LED ON</button></a></div>");
    client.println("<div><a href=\"/ledOff\"><button class=\"buttong buttonr\">Push for LED OFF</button></a></div>");
    client.println("</body></html>");
            
    // The HTTP response ends with another blank line
    client.println();
}

/*--------------------------------*/
void request_analysis(String header){
  /*
   * Analyse de la requete du client
   */
    if (header.indexOf("GET /ledOn") >= 0) { // turns the GPIOs on
        Serial.println("GET request to push LED on");
        LEDState = "Allumee";
        couleur = "green";
        
        digitalWrite(LEDpin, HIGH);
    } 
    else if (header.indexOf("GET /ledOff") >= 0) {// turns the GPIOs off
              Serial.println("GET request to push LED off");
              LEDState = "Eteinte";
              couleur = "red";
              
              digitalWrite(LEDpin, LOW);
         }
}

/*--------------------------------*/
void loop(){
  
  String header; // Entete de l'HTTP request
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // Nouvelle connexion,
    Serial.println("New Client.");          // Afficher qu'il y a un nouveau client
    String currentLine = "";                // créer une variable pour stocker les données à venir
                                            // fin de requete quand on a une ligne vide juste le \n ou \r\n !
    while (client.connected()) {            // Boucler jusqu'à avoir un client connecté
      if (client.available()) {             // S'il y un client 
        char c = client.read();             // et qu'il y a un byte à lire,
        Serial.write(c);                    // l'afficher sur le port série .. juste pour le debug
        header += c;                        // et le placer dans le buffer "header"  
        
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            // if the current line is blank, you got two newline characters in a row.
            // that's THE END OF the client HTTP request, so :

            // a) Analyse de la requete : cela peut avoir un impact sur l'état de l'objet !
            request_analysis(header);
            
            // b) Envoi de le reponse au client
            String temperature = getTemperature();
            String luminosite2 = getLuminosite();
            make_html_response_page(client, WiFi.macAddress(),temperature, luminosite2);

          
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      } 
    }
    // Clear the header variable
    header = "";

    // give the web browser time to receive the data
    delay(100); // millis
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  //else
  //   Serial.println("Waiting for client ..."); 
}
