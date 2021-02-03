int relayON = LOW;
int relayOFF = HIGH;
const int relay1Pin = 12;
const int relay2Pin = 14;
int motorDirection = 0; //1=CCW 0=CW
int motorState = 0;     //initial motor state 0=off, 1=on

String buttonTitle1[] = {"CCW", "CW", "Motor ON"};
String buttonTitle2[] = {"CCW", "CW", "Motor OFF"};
String argId[] = {"ccw", "cw", "do"};

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WebServer.h>
// #include <ESPmDNS.h>

const char *ssid = "Your WiFi SSID";
const char *password = "Your WiFi password";

WebServer server(80);

void handleRoot()
{
    //Robojax.com ESP32 Relay Motor Control
    String HTML = "<!DOCTYPE html>\
  <html>\
  <head>\
  	
                  < title > Robojax ESP32 Relay Motor Control</ title>

                  <meta name =\"viewport\" content=\"width=device-width, initial-scale=1\">\
  
                              < style>

                      html,
           body
    {
    width:
        100 %\;
    height:
        100 %\;
    margin:
        0
    }
    *{box - sizing : border - box}
         .colorAll{
             background - color : #90ee90
         }
         .colorBtn{
             background - color : #add8e6
         }
         .angleButtdon,
        a
    {
        font - size : 30px\;
    border:
        1px solid #ccc\;
    display:
        table - caption\;
    padding:
        7px 10px\;
        text - decoration : none\;
    cursor:
        pointer\;
    padding:
        5px 6px 7px 10px
    }
    a{
        display : block
    }
        .btn
    {
    margin:
        5px\;
    border:
        none\;
    display:
        inline - block\;
        vertical - align : middle\;
        text - align : center\;
        white - space : nowrap
    }
    ";

        HTML += "</style>

                < / head >

                <body>
                <h1> Robojax ESP32 Relay Motor Control</ h1> ";

                if (motorDirection == 0 && motorState)
    {
        HTML += "
                < h2 > < span style =\"background-color: #FFFF00\">Motor Running in CCW</span></h2>
                                      ";    
    }
    else if (motorDirection == 1 && motorState)
    {
        HTML += "
                < h2 > < span style =\"background-color: #FFFF00\">Motor Running in CW</span></h2>
                                      ";      
    }
    else
    {
        HTML += "
                < h2 > < span style =\"background-color: #FFFF00\">Motor OFF</span></h2>
                                      ";    
    }
    if (motorDirection == 0)
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton\" style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[0];
        HTML += "=off\">";
        HTML += buttonTitle1[0]; //relay ON title
    }
    else
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton \" style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += argId[0];
        HTML += "=on\">";
        HTML += buttonTitle2[0]; //relay OFF title
    }
    HTML += "</a>	
            < / div >

            ";     

            if (motorDirection == 1)
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton\" style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[1];
        HTML += "=off\">";
        HTML += buttonTitle1[1]; //relay ON title
    }
    else
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton \" style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += argId[1];
        HTML += "=on\">";
        HTML += buttonTitle2[1]; //relay OFF title
    }
    HTML += "</a>	
            < / div >

            ";     

            if (motorState == 0)
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += argId[2];
        HTML += "=on\">";
        HTML += buttonTitle1[2]; //relay ON title
    }
    else
    {
        HTML += "	<div class=\"btn\">
                < a class
            =\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[2];
        HTML += "=off\">";
        HTML += buttonTitle2[2]; //relay OFF title
    }
    HTML += "</a>	
            < / div >

            ";     

            HTML += "	
                    < / body >
                    </ html> ";
                    server.send(200, "text/html", HTML);
} //handleRoot()

void handleNotFound()
{
    //Robojax.com ESP32 Relay Motor Control
    String message = "File Not Found

                     ";
        message += "URI: ";
    message += server.uri();
    message += "
        Method : ";
                 message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "
        Arguments : ";
                    message += server.args();
    message += "
               ";

               for (uint8_t i = 0; i < server.args(); i++){
                   message += " " + server.argName(i) + ": " + server.arg(i) + "
                                                                               ";
               }

               server.send(404, "text/plain", message);
    //Robojax.com ESP32 Relay Control
} //end of handleNotFound()

void setup(void)
{
    //Robojax.com ESP32 Relay Motor Control

    pinMode(relay1Pin, OUTPUT);        // define a pin as output for relay
    digitalWrite(relay1Pin, relayOFF); //initial state either ON or OFF

    pinMode(relay2Pin, OUTPUT);        // define a pin as output for relay
    digitalWrite(relay2Pin, relayOFF); //initial state either ON or OFF

    Serial.begin(115200); //initialize the serial monitor
    Serial.println("Robojax ESP32 Relay Motor Control");

    //Relay control ON OFF by Robojax.com

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: http://");
    Serial.println(WiFi.localIP());

    //multicast DNS //Robojax.com ESP32 Relay Control
    if (MDNS.begin("robojaxESP32"))
    {
        Serial.println("MDNS responder started");
        Serial.println("access via http://robojaxESP32");
    }

    server.on("/", handleRoot);
    server.on("/motor", HTTP_GET, relayControl);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");

} //end of setup

void loop(void)
{
    //Robojax ESP32 Relay Motor Control
    server.handleClient();

    if (motorState == 1)
    {
        controlMotor();
    }
    else
    {
        motorStop();
    }

    delay(100);
    //Robojax ESP32 Relay Motor Control
} //end of loop

/*
 * relayControl()
 * updates the value of "relayState" varible to 1 or zero 
 * returns nothing
 * written by Ahmad Shamshiri
 * on Wednesday Feb 22, 2020 at 16:20 in Ajax, Ontario, Canada
 * www.robojax.com
 */
void relayControl()
{

    if (server.arg(argId[0]) == "on")
    {
        motorDirection = 0; // CCW
    }
    else if (server.arg(argId[1]) == "on")
    {
        motorDirection = 1; // CW
    }
    else if (server.arg(argId[2]) == "on")
    {
        motorState = 1;
        ; // turn the motor ON
    }
    else if (server.arg(argId[2]) == "off")
    {
        motorState = 0;
        ; // turn the motor OFF
    }

    handleRoot();
} //relayControl() end

/*
 * controlMotor()
 * controls the relay so the motor rotates in CCW/CW
 */
void controlMotor()
{
    if (motorDirection == 1)
    {
        digitalWrite(relay1Pin, LOW);  // turn relay 1 ON
        digitalWrite(relay2Pin, HIGH); // turn relay 2 OFF
                                       //Serial.println("Rotating in CCW");
    }
    else
    {
        digitalWrite(relay1Pin, HIGH); // turn relay 1 OFF
        digitalWrite(relay2Pin, LOW);  // turn relay 2 ON
                                       //Serial.println("Rotating in CW");
    }

} // controlMotor()

/*
 * motorStop()
 * controls the relay so the motor is stopped
 */
void motorStop()
{
    digitalWrite(relay1Pin, relayOFF); // turn relay 1 OFF
    digitalWrite(relay2Pin, relayOFF); // turn relay 2 OFf
                                       //Serial.println("Stopped");
}
