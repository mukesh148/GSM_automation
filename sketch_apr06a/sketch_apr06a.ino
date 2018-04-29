#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define PIN_TX    8    /* rx of Arduino (connect tx of gprs to this pin) */
#define PIN_RX    7   /* tx of Arduino (connect rx of gprs to this pin) */
#define BAUDRATE  9600
#define PHONE_NUMBER "8723019581"
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH]; /* buffer for storing message */
char phone[16];         /* buffer for storing phone number */
char datetime[24];        /* buffer for storing phone number */
int8_t messageIndex = 0;

/* Create an object named Sim900_test of the class GPRS */
GPRS Sim900_test(PIN_TX,PIN_RX,BAUDRATE); 

//const int8_t lm35_pin = A1;

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
//  pinMode(4, OUTPUT);     
  while(!Sim900_test.init())  /* Sim card and signal check, also check if module connected */ 
  {
      delay(1000);
      Serial.println("SIM900 initialization error");
  }  
  Serial.println("SIM900 initialization success");
  memset(message, 0, 160);
}

void loop() {
//  int16_t temp_adc_val;
  float temp_val;
//  temp_adc_val = analogRead(lm35_pin);  /* Read temperature from LM35 */
//  temp_val = (temp_adc_val * 4.88);
  temp_val = 40;
//  Serial.print("Temperature = ");
  Serial.print(temp_val);
//  Serial.print(" Degree Celsius\n");
    if(temp_val>30)
    {
        Serial.println("Need to cool down");
        Serial.println("Calling to inform");
        Sim900_test.callUp(PHONE_NUMBER); /* Call */
        delay(25000);
        Sim900_test.hangup(); /* Hang up the call */
        exit(0);
    }
//    for(int i=0; i<4; i++){
//      break;}
}
