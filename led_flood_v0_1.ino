// include the library code:
#include <LiquidCrystal.h>
#include "hhnet_routines.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P2_4, P2_5, P2_0, P2_1, P1_4, P1_5);

String dataPacket = ""; // string to hold incoming data
boolean dataReady = false; // flag to say when we are ready
const int PWM_PIN = P2_2;
const int maxDataPacketSize = 20;
const int hhNetAddress = 1;

// function prototypes
//void hhNet_send_ack(void);
//void hhNet_send_nack(hhNetReturnCode_t ret);

unsigned char strobeOnTime = 40;
unsigned char strobeOffTime = 100;
char mode = 'f';
int state = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("LED flood v0.1");
  lcd.setCursor(0, 1);
  lcd.print("Got: ");
  lcd.setCursor(5, 1);
  
  dataPacket.reserve(maxDataPacketSize); // allocate space for the data
  
  // serial setup
  Serial.begin(9600);

  
  // pwm setup
  analogFrequency(500);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() 
{
 
  if(dataReady)
  {
    // check the address
    if(hhNet_check_address(&dataPacket, hhNetAddress))
    {
      // do stuff
      switch(dataPacket[3])
      {
        case CMD_HHNET_VERSION:
        {
          //code to return a version code
          hhNet_send_response("0.1");
        }
        break;
        
        case CMD_HHNET_WRITE_REGISTER:
        {
          // code to write to an internal register
          if(dataPacket[4] == 'f')
          {
            // set the fader mode
            mode = 'f';
            // set the intensity
            analogWrite(PWM_PIN, (int)dataPacket[5]);
            hhNet_send_ack();
          }
          else if(dataPacket[4] == 's')
          {
            // set strobe mode
            mode = 's';
            // set the strobe parameters
            strobeOnTime = dataPacket[5];
            strobeOffTime = dataPacket[6];
            hhNet_send_ack();
          }
          else
          {
            hhNet_send_nack(RC_HHNET_BAD_PARAMETERS);
            break;
          }
          
        }
        break;
        
        case CMD_HHNET_RESET:
        {
           // Code to reset internal regs
           mode = 'f'
           analogWrite(PWM_PIN, 255);
           strobeOnTime = 40;
           strobeOffTime = 100;
           hhNet_send_ack();
        }
        break;       
        
        
        default:
        {
          // not an implemented command
          hhNet_send_nack(RC_HHNET_NOT_IMPLEMENTED);
        }
        break;
      }     
      dataPacket = "";
      dataReady = false; 
    }
    else
    {
      //packet isnt for us.
      dataPacket = "";
      dataReady = false;
    }    
    lcd.print("               ");
    lcd.setCursor(5,1);
  }

  
  switch(mode)
  {

    case 's':
    // Strobe light!
    digitalWrite(PWM_PIN, HIGH);
    delay(40);
    digitalWrite(PWM_PIN, LOW);
    delay(95);
    break;
    
    default:
      // its all good
    break;
  }
  
}

