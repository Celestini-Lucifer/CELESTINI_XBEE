//this code was written while listening to "Arctic monkeys- Do I wanna know?"
void BroadCast()
{
    TxStatusResponse txStatus = TxStatusResponse();//may not actually need this.
    Tx16Request tx = Tx16Request(0xFFFF, DataOut, sizeof(DataOut)); //format of the frame being broadcasted. destination address,payload,size of payload
    xbee.send(tx);//send out that info brotha. broadcast has no acknowledgement bit so i guess this is pretty much it (fingers crossed).
}

void Read()//function to read stuff
{
    Rx16Response rx16 = Rx16Response(); //objects for doing the response related stuff.
    Rx64Response rx64 = Rx64Response();
    
    xbee.readPacket();//anything available out there?
    if (xbee.getResponse().isAvailable())//WE GOT ONE!! 
    {    
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) //if its using 16 bit addressing. Not sure how this stuff works in broadcast mode. although i guess it still works 
      {
        xbee.getResponse().getRx16Response(rx16);//take the response, dump it in an object by the name of rx16
        option = rx16.getOption();//why do i need this?
        DataIn[0] = rx16.getData(0);//the thing we care 'bout
        DataIn[1] = rx16.getData(1);
      } 
      else if(xbee.getResponse().getApiId() == RX_64_RESPONSE)//don't got no clue why i am doing this
      {
        xbee.getResponse().getRx64Response(rx64);//not commenting this stuff cuz its the same as for 16 bit
        option = rx64.getOption();//why do i need this?
        DataIn[0] = rx64.getData(0);//the thing we care 'bout
        DataIn[1] = rx64.getData(1);        
      } 
      else //(error)
      {

      }
    } 
    else if (xbee.getResponse().isError())
    {

    } 
}

void sendAtCommand(AtCommandRequest request) 
{
  AtCommandResponse response = AtCommandResponse();
  xbee.send(request);
  if (xbee.readPacket(5000)) 
  {
    if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE)
    {
      xbee.getResponse().getAtCommandResponse(response);

      if (response.isOk()) //Are you okay? I isOk.
      {

      } 
      else//command returned some error code for some godforsaken reason.
      {

        
      }
    } 
    else//something went haywire
    {

    }    
  } 
  else if (xbee.getResponse().isError()) //Houston, we have a problem
  {

  }
  else//no response from radio 
  {

  }
}
