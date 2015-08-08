#include <SoftwareSerial.h>
 
#define DEBUG true
SoftwareSerial esp8266(10,11);
                             

#define TARGET_IP "192.168.1.120" ///         //hosting
#define TARGET_PORT "9094"     


#define ID "Nitro X"  //name of wireless access point to connect to
#define PASS "25364016"  //wifi password

                             
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
   
   

    sendData("AT+RST\r\n",1000,DEBUG); //     
    sendData("AT+CWMODE=1\r\n",1000,DEBUG); // 
     

    
     String cmd="AT+CWJAP=\"";  
     cmd+=ID;
     cmd+="\",\"";
     cmd+=PASS;
     cmd+="\"";      
     sendData( cmd+"\r\n",1000,DEBUG); //     
     sendData("AT+CIPMUX=1\r\n",1000,DEBUG); //      
     sendData("AT+CWMODE=1\r\n",1000,DEBUG); // 
          
         
    
}
 
void loop()
{
    
     sendData("AT+CIPMUX=1\r\n",1000,DEBUG); //      
     sendData("AT+CWMODE=1\r\n",1000,DEBUG); //         
  

    String webpage = "AT+CIPSTART=1,\"TCP\",\""; 
    webpage += TARGET_IP;
    webpage += "\",9094\r\n";   
      
    sendData(webpage,1000,DEBUG);      


    String webpage1 = "<01#WCSY00001**";                       
    String cipsend = "AT+CIPSEND=1,";     
    cipsend+= webpage1.length();
    cipsend+="\r\n";     
      
     sendData(cipsend,1000,DEBUG);
     sendData(webpage1,1000,DEBUG);   
     
     delay(5000);
         
          
     webpage1 = "<01#WCSY00001**";
     cipsend = "AT+CIPSEND=1,";     
     cipsend+= webpage1.length();
     cipsend+="\r\n";     
      
     sendData(cipsend,1000,DEBUG);
     sendData(webpage1,1000,DEBUG);   
     
      delay(5000);  //4min  

}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
