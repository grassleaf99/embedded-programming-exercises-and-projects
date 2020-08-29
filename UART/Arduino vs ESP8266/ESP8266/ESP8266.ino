// Load Wi-Fi library 
#include <ESP8266WiFi.h> 
#include <SoftwareSerial.h>

// Replace with your network credentials 
const char* ssid = "your wifi name"; 
const char* password = "your password"; 

// Set web server port number to 80 
WiFiServer server(80); 

// Variable to store the HTTP request 
String header; 

// Auxiliary variables to store the current output state 
volatile int16_t brightness = 125;

//The circuit:
// * RX is digital pin D2 
// * TX is digital pin D3
SoftwareSerial ntUART(D2, D3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  // Connect to Wi-Fi network with SSID and password 
  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    Serial.print("."); 
  } 
  // Print local IP address of ESP8266 and start web server 
  Serial.println(""); 
  Serial.println("WiFi connected."); 
  Serial.print("ESP8266 IP address: "); 
  Serial.println(WiFi.localIP()); 
  server.begin();
  ntUART.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available(); // Listen for incoming clients 
  if (client) // If a new client connects,
  { 
    Serial.println("New Client."); // print a message out in the serial port 
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) // loop while the client's connected
    {
      if (client.available())       // if there's bytes to read from the client,
      { 
         char c = client.read();    // read a byte, then
         Serial.write(c);           // print it out the serial monitor 
         header += c; 
         if (c == '\n') // if the byte is a newline character
         {
            // if the current line is blank, you got two newline characters in a row. 
            // that's the end of the client HTTP request, so send a response: 
            if (currentLine.length() == 0) 
            {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) 
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK"); 
              client.println("Content-type:text/html"); 
              client.println("Connection: close"); 
              client.println(); 
              
              if (header.indexOf("GET /tang50") >= 0) // nếu header có đoạn "GET /tang50"
              { 
                brightness += 50;
                if(brightness > 255)
                brightness = 255;
                ntUART.write(brightness);  // gửi dữ liệu về độ sáng đèn LED cho Arduino
              } 
              else if (header.indexOf("GET /giam50") >= 0) // nếu header có đoạn "GET /giam50"
              { 
                brightness -= 50;
                if(brightness < 0)
                brightness = 0;
                ntUART.write(brightness);  // gửi dữ liệu về độ sáng đèn LED cho Arduino
              }
              
              // Display the HTML web page 
              client.println("<!DOCTYPE html><html>"); 
              client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"); 
              client.println("<link rel=\"icon\" href=\"data:,\">");
              // CSS to style the on/off buttons 
              // Feel free to change the background-color and 
              // font-size attributes to fit your preferences
              client.println("<title>UART Arduino vs ESP8266</title>");
              client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto;}"); 
              client.println("</style></head>"); 

              // Web Page Heading 
              client.println("<body><h1>ESP8266 Web Server</h1>"); 

              client.println("<p style=\"text-align:center; border:2px dotted black; font-size:large;\">Brightness of LED " + String(brightness) + "</p>");   
              client.println("<a href=\"/giam50\">");
              client.println("<button style=\"position:absolute; left:100px; top:400px; background-color: #FF0000; color: #0000FF; border: 1px solid black; padding: 16px 40px; font-size: 30px; margin: 2px;\">-50</button>");
              client.println("</a>");            
              client.println("<a href=\"/tang50\">");
              client.println("<button style=\"position:absolute; left:250px; top:400px; background-color: #00FF00; color: #FFFF00; border: 1px solid black; padding: 16px 40px; font-size: 30px; margin: 2px;\">+50</button>");
              client.println("</a>");
              client.println("</body></html>"); 
              
              // The HTTP response ends with another blank line 
              client.println(); 
              // Break out of the while loop 
              break; 
            }
            else    // if you got a newline, then clear currentLine 
              currentLine = "";
         }
         else if(c != '\r')   //if you got anything else but a carriage return character, add it to the end of the currentLine
            currentLine += c;
      }
    }
    // Clear the header variable 
    header = ""; 
    // Close the connection 
    client.stop(); 
    Serial.println("Client disconnected."); 
    Serial.println("");
  }
}
