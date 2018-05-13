#include <XBee.h>
#include<SoftwareSerial.h>

#define nssRX 2
#define nssTX 3

SoftwareSerial nss(nssRX,nssTX);

XBee xbee = XBee();//constructor?
XBeeResponse response = XBeeResponse();//also constructor?

// create reusable response objects for responses we expect to handle 
uint8_t option = 0;
uint8_t DataOut[2];//data that we will receive,for now, its like just 2 bytes for testing purposes.
uint8_t DataIn[2];//data received. 


uint8_t idCmd[] = {'I','D'};
//uint8_t idValue[] = {0x01, 0x10}; // some made up value for testing purposes
uint8_t idCmd2[] = {'W','R'}; // write to EEPROM command.

void setup() 
{
  // start serial
  nss.begin(9600);
  xbee.setSerial(nss);
  Serial.begin(38400);
  delay(15000);//xbee's are cray cray. they need some time to start.
}

// continuously reads packets, looking for RX16 or RX64
void loop()
{   
    Read(); //read the environment.
    DataOut[1] = 255;
    DataOut[0] = 128;//just some random shit
    BroadCast();//broadcast   
}

void reset_ID(uint8_t ID)
{
    uint8_t *idValue = &ID;
    
    AtCommandRequest request = AtCommandRequest(idCmd, idValue, sizeof(idValue));
    
    sendAtCommand(request);
    request.clearCommandValue();
    request.setCommand(idCmd2);
    sendAtCommand(request);
    request.clearCommandValue();
}


