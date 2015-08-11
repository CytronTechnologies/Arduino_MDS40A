//=========================================================================================
//	Author	      : CYTRON TECHNOLOGIES SDN BHD
//	Tutorial      : Interfacing MDS40A by Arduino-Due with Arduino-LCD Keypad Shield
//	Description   : Using Simplified Serial Mode						
//=========================================================================================

#include <LiquidCrystal.h>

/*
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
*/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Keypad Button Numbering
#define RG   0
#define UP   1
#define DW   2
#define LF   3
#define SEL  4

//constant variable
const int Tx = 1;
const int mtr1_In2 = 2;
const int mtr2_In2 = 12;

int analogPin = A0;
int adc_key_old;
int adc_key_in;
int NUM_KEYS = 5;
int adc_key_val[5] ={30, 150, 360, 535, 760};                           
                    
/*******************************************************************************
* PRIVATE FUNCTION: setup()
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Define of I/O pin as Input or Output 
*
*******************************************************************************/
// The setup() method runs once, when the sketch starts
void setup ()
{
  //Set the mode for each digital pins whether input or output
  pinMode(Tx, OUTPUT);
  pinMode(mtr1_In2, OUTPUT);
  pinMode(mtr2_In2, OUTPUT);
  
  Serial.begin(9600);                  // set serial baud rate as 9600
  Serial.flush();                      // Waits for the transmission of outgoing serial data to complete
  lcd.begin(16, 2);                    // set the lcd dimension
  lcd.clear();                         // LCD screen clear
  lcd.setCursor(0,0);
  lcd.print("MDS40A");                 // display the text
  lcd.setCursor(0,1);
  lcd.print("Serial Mode Demo");
  delay(5000);                          // delay for 5000ms
  adc_key_old = analogRead(analogPin);  // store the unpress key value 
}


/*******************************************************************************
* PRIVATE FUNCTION: loop()
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Non-Stop looping 
*
*******************************************************************************/
void loop()
{
    digitalWrite(mtr1_In2, HIGH);      
    digitalWrite(mtr2_In2, HIGH);         // The Slave Select (IN2) for MDS40A set HIGH 
    adc_key_in = analogRead(analogPin);   // read ADC value
    adc_key_in = get_key(adc_key_in);
    lcd.clear();
    
    if(adc_key_in == UP)                  // Check whether Up button pressed
    {                                     // both motors rotate clockwise (CW)
      Serial.write(220);
      lcd.setCursor(0, 0);
      lcd.print("Both motors");
      lcd.setCursor(0, 1); 
      lcd.print("Clockwise");
      delay(200);
    }
    
    else if(adc_key_in == DW)              // Check whether Down button pressed     
    {                                      // both motors rotate counterclockwise (CCW)
      Serial.write(35);
      lcd.setCursor(0, 0);
      lcd.print("Both motors");
      lcd.setCursor(0, 1); 
      lcd.print("Anticlockwise");
      delay(200);
    }
    
    else
    {                                     // Display button navigation for each movement
      lcd.setCursor(0,0);                      
      lcd.print("CW - Press Up"); 
      lcd.setCursor(0,1);
      lcd.print("CCW - Press Down"); 
      delay(200); 
      Serial.write(127);
    }
}
  

/*******************************************************************************
* PRIVATE FUNCTION: get_key
*
* PARAMETERS:
* ~ integer
*
* RETURN:
* ~ unsigned int input
*
* DESCRIPTIONS:
* convert the ADC value to number between 0 to 4
*
*******************************************************************************/
int get_key(unsigned int input)
{
	int k;
    
	for (k = 0; k < NUM_KEYS; k++)
	{
		if (input < adc_key_val[k])
		{
                return k;
                }
	}
    
    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed
    
    return k;
}


