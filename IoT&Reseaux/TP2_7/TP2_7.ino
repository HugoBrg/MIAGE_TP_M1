/*
 * Auteur : G.Menez
 */
#include <WiFi.h>
#include <HTTPClient.h>
#include "net_misc.h"

#include "OneWire.h"
#include "DallasTemperature.h"

/* ---- CONST---- */
const int lumiPIN = 13;
const int tempPIN = 23;
const int redPIN = 19;
const int greenPIN = 21;

/* ---- LED ---- */
// Ces variables permettent d'avoir une représentation
// interne au programme du statut "electrique" de l'objet.
// Car on ne peut pas interroge une GPIO pour lui demander !
String redState = "Eteinte";
String greenState = "Eteinte";
String redCouleur = "red";
String greenCouleur = "red";

/* ---- TEMP ---- */
OneWire oneWire(tempPIN); // Pour utiliser une entite oneWire sur le port 23
DallasTemperature tempSensor(&oneWire) ; // Cette entite est utilisee par le capteur de temperature

/* ---- WEB ---- */
// Set web server port number to 80
WiFiServer server(80);

/*--------------------------------*/
float getTemperature() {
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
  return t;
}

/*--------------------------------*/
int getLuminosite(){
  int luminosite = analogRead(lumiPIN);
  Serial.print("Luminosite | getLuminosite() : "); // for debug
  Serial.print(luminosite);
  Serial.print(" Lux\n");
  return luminosite;
}

/*--------------------------------*/
void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for a serial connection. Needed for native USB port only

  int luminosite1 = analogRead(lumiPIN);  
  Serial.print("Luminosite | setup1() : "); // for debug
  Serial.print(luminosite1);
  Serial.print(" Lux\n");
  
  // Initialize the output variables as outputs
  pinMode(redPIN, OUTPUT);
  // Set outputs to LOW
  digitalWrite(redPIN, LOW);

  // Initialize the output variables as outputs
  pinMode(greenPIN, OUTPUT);
  // Set outputs to LOW
  digitalWrite(greenPIN, LOW);
  
  // Init temperature sensor 
  tempSensor.begin();
 
  connect_wifi(); // Connexion Wifi  
 
  server.begin(); // Lancement du serveur



  int luminosite2 = analogRead(lumiPIN);  
  Serial.print("Luminosite | setup2() : "); // for debug
  Serial.print(luminosite2);
  Serial.print(" Lux\n");
}

/*--------------------------------*/
void make_html_response_page(WiFiClient client, String mac, String temperature, String luminosite, String chauffage){
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
    String background="white";
    Serial.print("chauffage : "+chauffage+"++++++");
    if(chauffage=="jour"){
      background="yellow";
    }
    else if(chauffage=="nuit"){
      background="black";
    }
    client.println("<head><style>body{font-family: Helvetica; margin: 0px auto; text-align: center; background-color:"+background+";}");
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
    client.println("<p>Luminosite : "+ luminosite +" Lux</p>");
            
    // Display current state, and ON/OFF buttons for LED
    client.println("<p>Statut de la LED rouge : <font color=" + redCouleur +">" + redState + "</font></p>");
    client.println("<p>Statut de la LED verte : <font color=" + greenCouleur +">" + greenState + "</font></p>");
    
    
    // Ctrl buttons
    client.println("<div><a href=\"/redLedOn\"><button class=\"buttong\">Chauffage ON</button></a></div>");
    client.println("<div><a href=\"/redLedOff\"><button class=\"buttong buttonr\">Chauffage OFF</button></a></div>");
    
    client.println("<div><a href=\"/greenLedOn\"><button class=\"buttong\">Clim ON</button></a></div>");
    client.println("<div><a href=\"/greenLedOff\"><button class=\"buttong buttonr\">Clim OFF</button></a></div>");
    
    client.println("</body></html>");
            
    // The HTTP response ends with another blank line
    client.println();
}

/*--------------------------------*/
void post_test(){
    HTTPClient http;
     
    http.begin("192.168.43.141"); //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain"); //Specify content-type header
    int httpResponseCode = http.POST("POSTING from ESP32"); //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request

    Serial.println("Success on sending POST : ");
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
}

/*--------------------------------*/
String chauffage(float temperature, int luminosite){
    
    //float temp = temperature.toFloat();
    //int lumi = luminosite.toInt();
    
    if(temperature < 25 && luminosite < 1800){
      //NUIT
      Serial.print("NUIT");
      Serial.print("\n");
      digitalWrite(greenPIN, HIGH);
      digitalWrite(redPIN, LOW);
      return "nuit";
  }
  else if (temperature > 25 && luminosite > 1800){
      //JOUR
      Serial.print("JOUR");
      Serial.print("\n");
      digitalWrite(redPIN, LOW);
      digitalWrite(greenPIN, HIGH);
      return "jour";
  }
}

/*--------------------------------*/
void request_analysis(String header){
  /*
   * Analyse de la requete du client
   */
    if (header.indexOf("GET /redLedOn") >= 0) { // turns the GPIOs on
        Serial.println("GET request to push red LED on");
        redState = "Allumee";
        redCouleur = "green";   
        digitalWrite(redPIN, HIGH);
    } 
    else if (header.indexOf("GET /redLedOff") >= 0) {// turns the GPIOs off
        Serial.println("GET request to push red LED off");
        redState = "Eteinte";
        redCouleur = "red";          
        digitalWrite(redPIN, LOW);
    }
    else if (header.indexOf("GET /greenLedOn") >= 0) {// turns the GPIOs on
        Serial.println("GET request to push green LED on");
        greenState = "Allumee";
        greenCouleur = "green";             
        digitalWrite(greenPIN, HIGH);
    }
    else if (header.indexOf("GET /greenLedOff") >= 0) {// turns the GPIOs off
        Serial.println("GET request to push green LED off");
        greenState = "Eteinte";
        greenCouleur = "red";           
        digitalWrite(greenPIN, LOW);
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
            float temperatureF = getTemperature();
            int luminositeI = getLuminosite();
            String temperatureS = String(temperatureF);
            String luminositeS = String(luminositeI);
  
            //String chauffage = chauffage(temperatureF, luminositeI);
            //String chauffage = chauffage(temperatureS, luminositeS);  
          
            make_html_response_page(client, WiFi.macAddress(),temperatureS, luminositeS, chauffage(temperatureF, luminositeI));
          
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
    //post_test();
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  //else
  //   Serial.println("Waiting for client ..."); 
}
