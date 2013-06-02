

int serialRxState = IDLE;
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() 
{
  char temp;
  while (Serial.available() && (dataReady == false)) 
  {
    temp = (char)Serial.read();
    switch(serialRxState)
    {
      case IDLE: // Idle state
      {
        if(temp == start_c)
        {
          serialRxState = RX;
        }
      }
      break;
      
      case RX:
      {
        if(temp == esc_c)
        {
          //detected an escape
          serialRxState = ESCAPE;
        }
        else if ( temp  == end_c)
        {
          // found the end
          dataReady = true;
          serialRxState = IDLE;
        }
        else
        {
          dataPacket += temp;
        }
      }
      break;
      
      case ESCAPE:
      {
        serialRxState = RX;
        dataPacket += temp;
      }
      break;      
      
      default:
      serialRxState = IDLE;
      break;
    }
  
  }
}


int addChar(String * buffer, char c)
{
  // add a char to the data buffer
  // if it gets too full, then returns -1
  if((*buffer).length() >= maxDataPacketSize)
  {
    return -1;
  }
  buffer += c;
  return 0;
}

boolean hhNet_check_address(String * buffer, int address)
{
  int temp = 0;
  temp = (*buffer)[0] << 8;
  temp |= (*buffer)[1];
  if(temp == address)
  {
    return true;
  }
  return false;
}

//void hhNet_send_nack(hhNetReturnCode_t ret)
void hhNet_send_nack(int returncode)
{
  // send a no acknolwege to the hhnet controller
  // also sends why the command wasnt interpreted

}

int hhNet_send_ack()
{
  // send an ack to indicate that the command was rxed
  // successfully
  return 0;
}

void hhNet_send_response( uint8_t * buffer, int len)
{
  int i;
  // send the buffer back to the host
  for(i = 0; i < len; ++i)
  {
    

}
