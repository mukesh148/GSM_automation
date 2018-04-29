#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define PIN_TX    8    /* rx of Arduino (connect tx of gprs to this pin) */
#define PIN_RX    7   /* tx of Arduino (connect rx of gprs to this pin) */
#define BAUDRATE  9600
#define PHONE_NUMBER "8723019581"
#define MESSAGE_LENGTH 160
#define NUM_SAMPLES 10

char message[MESSAGE_LENGTH]; /* buffer for storing message */
char phone[16];         /* buffer for storing phone number */
char datetime[24];        /* buffer for storing phone number */
int8_t messageIndex = 0;


int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage
float act_voltage=0.0;

/* Create an object named Sim900_test of the class GPRS */
GPRS Sim900_test(PIN_TX,PIN_RX,BAUDRATE); 

//const int8_t lm35_pin = A1;

void setup() {
  Serial.begin(9600);
  while(!Sim900_test.init())  /* Sim card and signal check, also check if module connected */ 
  {
      delay(1000);
      Serial.println("SIM900 initialization error");
  }  
  Serial.println("SIM900 initialization success");
  memset(message, 0, 160);
}

void loop() {
  while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(10);
  }
  voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
  Serial.print(voltage * 11.132);
  Serial.println (" V");
  act_voltage = voltage * 11.132;

  messageIndex = Sim900_test.isSMSunread();
  Serial.println(messageIndex);
  
  if(act_voltage>0.2)
    {
        Serial.println("Need to cool down");
        Serial.println("Calling to inform");
        Sim900_test.callUp(PHONE_NUMBER); /* Call */
        delay(25000);
        Sim900_test.hangup(); /* Hang up the call */
    }
  else
    {
        Serial.println("Everything is fine"); 
    }

  sample_count = 0;
  sum = 0;
  delay(3000);
}

