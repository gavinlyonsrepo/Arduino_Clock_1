#include <LCD5110_Graph.h> //5110 Nokia
#include <Keypad.h> //keypad
#include <SFE_BMP180.h> //pressure
#include <dht.h> //DHT11
#include <DS1307RTC.h>
#include <Sleep_n0m1.h> //https://github.com/n0m1/Sleep_n0m1

//clock
char settime[12];

//lm35
#define tempPin A1

//dht
#define dht_dpin A0 //no ; here. Set equal to channel sensor is on

//keypad
const byte numRows = 4; //number of rows on the keypad
const byte numCols = 3; //number of columns on the keypad
char keymap[numRows][numCols] =
{
  {'1', '2', '3', },
  {'4', '5', '6', },
  {'7', '8', '9', },
  {'*', '0', '#', }
};
//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {13, 12, 11, 10}; //Rows 0 to 3
byte colPins[numCols] = {9, 8, 7}; //Columns 0 to 3
//initializes an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

//alarm
char alarm[4];    //alarm
#define buzzer A3 // buzzer
boolean alarmOn = false;

//LCD Nokia 5110
// (SCK/CLK, MOSI/DIN, DC, RST, CS/CE)
LCD5110 lcd(2, 3, 4, 6, 5);
extern unsigned char SmallFont[];
extern unsigned char BigNumbers[];
boolean sleepset = false; //sleep
  
void setup() {
  // put your setup code here, to run once:  
   
   //buzzer
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  
  //init LCD
  lcd.InitLCD();
  lcd.setContrast(62);
  lcd.setFont(SmallFont);
  lcd.print("Alarm Clock", LEFT, 5);
  lcd.print("Gavin Lyons", LEFT, 15);
  lcd.print("Press Seven", LEFT, 25);
  lcd.print("for help.", LEFT, 35);
  lcd.update();
  delay(3500);
  lcd.clrScr();
  delay(50);
}

void loop() {
 char timebuf[5];  // Time
char datebuf[7];  // Date
 lcd.clrScr();
  delay(5);
 //scan the keypad
  char key = keypad.getKey();
  if (key) // Check for a valid key.
  {
    switch (key)
    {            
      case '1':
        // temperature
        DisplayLM();
        break;
      case '2':
        //humdity
       DisplayDHT();
        break;  
       case '3': //check pressure
        DisplayPressure();
        break;
      case '4':
        //Serial.println(key);
       DisplayAlarm();
        break;
      case '5':
        //Serial.println(key);
       SetAlarm();
        DisplayAlarm();
        alarmOn = true;
        break;
     case '6': //check buzzer
        //Serial.println(key);
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);        
         break;
     
     case '7': 
     //keypad help
      keypadhelp();
        break;
      
      case '8': //sleep mode
        SleepSet();
        break;
     case '9': //set time
        setmytime();
        break;
     case '0': 
            //sleepmode for six hours
            sleepmode();
      break;
     case '*':  
       //stop alarm 
       StopAlarm();
        alarmOn = false;
        break;
      case '#': 
      //lcd reset
      lcd.InitLCD();
      lcd.setContrast(62);
      lcd.setFont(SmallFont);
      lcd.print("LCD reset", CENTER, 20);
      lcd.update();
      delay(1000);
      lcd.clrScr();
      delay(50);
      break;
      }
  }

  //time date RTC
  tmElements_t tm;
  if (RTC.read(tm)) {
    int year2digit=0;  // 2 digit year
    year2digit = tm.Year - 30;  // 2 digit year variable
    //year4digit = tm.Year + 1970;  // 4 digit year variable
        sprintf(timebuf, "%02d%02d", tm.Hour, tm.Minute); // format time
        sprintf(datebuf, "%02d%02d%02d", tm.Day, tm.Month, year2digit); // format date
        delay(1);
   //check alarm
   if ((timebuf[0] == alarm[0]) and (timebuf[1] == alarm[1]) and (timebuf[2] == alarm[2]) and  (timebuf[3] == alarm[3]))
        {
          //turn on  alarm
          digitalWrite(buzzer,HIGH);
          
        } 
   //GUI time
   lcd.setFont(BigNumbers);
   lcd.print(timebuf,LEFT+15,1);     
   lcd.setFont(BigNumbers);
   lcd.print(datebuf, LEFT, 25);
     //gui alarm symbol
        lcd.setFont(SmallFont);
        if (alarmOn == true)
        {
          lcd.print("A", LEFT+5, 5);
        }else
        {
          lcd.print(" ", LEFT+5, 5);
        }
   lcd.update();
   delay(200); /// stop flicker
  }else
  {//clock running error messages 
   if (RTC.chipPresent()) {
      lcd.setFont(SmallFont);
      lcd.print(" DS1307 RTC", LEFT, 0);
      lcd.print("is stopped.", LEFT, 10);
      lcd.print("Please run ", LEFT, 20);
      lcd.print("SetTime", LEFT, 30);
      lcd.print("key 9", LEFT, 40);
      lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);     
    } else {
      lcd.setFont(SmallFont);
      lcd.print(" DS1307 RTC", LEFT, 0);
      lcd.print("read error!", LEFT, 10);
      lcd.print("Please check", LEFT, 20);
      lcd.print("circuitry", LEFT, 30);
      lcd.print("& battery", LEFT, 40);
      lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);  
    }

    }
}//end of main

//Function to display keypad help
void keypadhelp()
{
      lcd.setFont(SmallFont);
      lcd.print("0:Sleep 6hr", LEFT, 10);
      lcd.print("1:Temperture", LEFT, 20);
      lcd.print("2:Humdity", LEFT, 30);
      lcd.print("3:Pressure", LEFT, 40);
      lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);
      
      lcd.print("4:Alarm Show", LEFT, 10);
      lcd.print("5:Alarm Set", LEFT, 20);     
      lcd.print("6:Alarm Test", LEFT, 30);
       lcd.print("*:Alarm Stop", LEFT, 40);
       lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);
      
      lcd.print("7:Keypad help", LEFT, 10);
      lcd.print("8:LCD on/off", LEFT, 20);
      lcd.print("9:Set timedate", LEFT, 30);
      lcd.print("#:Screen reset", LEFT, 40);
      lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);
      
}

void SleepSet()
{
sleepset = !sleepset;
if (sleepset == true)
  {
    lcd.setFont(SmallFont);
    lcd.print("LCD Sleep", LEFT, 15);
    lcd.print("Mode ON", LEFT, 25);
    lcd.update();
    delay(1000);
    lcd.clrScr();
    delay(10);  
    lcd.enableSleep();
   }else {
     
     lcd.disableSleep();
     delay(50);
     lcd.setFont(SmallFont);
     lcd.print("LCD Sleep", LEFT, 15);
    lcd.print("Mode OFF", LEFT, 25);
     lcd.update();
     delay(1000);
      lcd.clrScr();
      delay(10);  
      }
}

//function display pressure
void DisplayPressure()
{
    //pressure
   SFE_BMP180 pressure;
   if (pressure.begin()) {
     lcd.setFont(SmallFont);
     lcd.print("BMP180 ", CENTER, 10);
     lcd.print("Pressure", CENTER, 20);
     lcd.print("sensor", CENTER, 30);
     lcd.print("init success", CENTER, 40);
     lcd.update();
     delay(1000);
      lcd.clrScr();
       delay(50); 
  }else{
      lcd.setFont(SmallFont);
      lcd.print("BMP180 ", CENTER, 10);
      lcd.print("Pressure", CENTER, 20);
      lcd.print("init fail", CENTER, 30);
      lcd.update();
      delay(3000);
      lcd.clrScr();
      delay(50);  
  }
  char status;
  double T, P;
  status = pressure.startTemperature();
  if (status != 0)
  {

    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      
      lcd.clrScr();
      delay(1);
      lcd.setFont(SmallFont);
      lcd.print("Temperature:", CENTER, 5);
      lcd.setFont(BigNumbers);
      lcd.printNumF(T, 0, LEFT + 10, 20);
      lcd.setFont(SmallFont);
      lcd.print("~C", LEFT + 40, 35);
      lcd.update();
      delay(2000);
      lcd.clrScr();
      delay(10);
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);


        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          
          // Print out the measurement:
          lcd.setFont(SmallFont);
          lcd.print("Pressure:", CENTER, 5);
          lcd.setFont(BigNumbers);
          lcd.printNumF(P, 0, LEFT + 10, 15);
          lcd.setFont(SmallFont);
          lcd.print("mb", LEFT + 67, 30);

              if (P <= 983) {
                  lcd.print("STORMY", LEFT + 20, 40);
                }
                else if (P >983 && P <998){
                  lcd.print("RAINY", LEFT + 20, 40);;
                }
                 else if (P >=998 && P <1012){
                  lcd.print("CHANGE", LEFT + 20, 40);
                }
                 else if (P >=1012 && P <1025){
                  lcd.print("FAIR", LEFT + 20, 40);
                }
                 else if (P >=1025){
                  lcd.print("DRY", LEFT + 20, 40);
                }
  
          lcd.update();
          delay(2000);  // Pause for 2 seconds.
          lcd.clrScr();
          delay(10);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  
}

void DisplayAlarm()
{
  //alarm

  lcd.clrScr();
  delay(10);
  lcd.setFont(SmallFont);
  lcd.print("Alarm Time:", CENTER, 10);
  lcd.setFont(BigNumbers);
  lcd.print(alarm, CENTER, 25);
  lcd.update();
  delay(2000);
  lcd.clrScr();
  delay(1);
}
void DisplayLM() 
{
  //lm35
  float temp;
  lcd.clrScr();
  delay(1);
  temp = analogRead(tempPin);
  temp = temp * .48828125;
  
  //Printing GUI
  lcd.setFont(SmallFont);
  lcd.print("LM35 Sensor", CENTER, 0);
  lcd.print("Temperature:", CENTER, 10);
  lcd.setFont(BigNumbers);
  lcd.printNumF(temp, 1, LEFT +10, 22);
  lcd.setFont(SmallFont);
  lcd.print("~C", LEFT + 67, 37);
  lcd.update();
  delay(3000);
  lcd.clrScr();
  delay(10);
}
void DisplayDHT()
{ //dht11.
  dht DHT;
  DHT.read11(dht_dpin);
  lcd.clrScr();
  delay(1);
  lcd.setFont(SmallFont);
  lcd.print("DHT11 Sensor", CENTER, 1);
  lcd.print("Humdity:", CENTER, 12);
  lcd.setFont(BigNumbers);
  lcd.printNumF(DHT.humidity, 0, LEFT+20, 22);
  lcd.setFont(SmallFont);
  lcd.print("%", LEFT + 50, 35);
  lcd.update();
  delay(2000);//Don't try to access too frequently... in theory
  lcd.clrScr();
  delay(1);
  lcd.setFont(SmallFont);
  lcd.print("DHT11 Sensor", CENTER, 1);
  lcd.print(" Temperature:", CENTER, 12);
  lcd.setFont(BigNumbers);
  lcd.printNumF(DHT.temperature, 0, LEFT+20, 22);
  lcd.setFont(SmallFont);
  lcd.print("~C", LEFT + 50, 35);
  lcd.update();
  delay(2000);
  lcd.clrScr();
  delay(1);  
}

void setmytime()
{
  
  //clear variables
  
  char z = 0;
  int Hour =0;
  int Min =0;
  int Sec =0;
  int Day =0;
  int Month =0;
  int Year = 0;
 tmElements_t tm;
 //LCD
  lcd.clrScr();
 delay(10);
  lcd.setFont(SmallFont);
 lcd.print(" Set Time Date: ", LEFT, 0);
 lcd.print("HHMMDDMMYY", LEFT, 15);
  lcd.update();
  delay(5);
  int i = 0;
  while (i < 10)
  {
    char key = keypad.getKey();
    if (key)
   {
      settime[z] = key;
      z++;
      i++;
      lcd.print(settime, LEFT, 30);
      lcd.update();
    }
  }
  
  (sscanf(settime, "%02d%02d%02d%02d%02d", &Hour, &Min, &Day, &Month, &Year));
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
 tm.Day = Day;
 tm.Month = Month; 
 tm.Year =(Year+30);
 RTC.write(tm);
delay(50);
}

void SetAlarm()
{
  //clear variables
  char z = 0;

  //LCD
  lcd.clrScr();
  delay(10);
  lcd.setFont(SmallFont);
  lcd.print("SET Alarm", CENTER, 0);
  lcd.print("HHMM", LEFT + 5, 20);
  lcd.update();

  int i = 1;
  while (i < 5)
  {
    char key = keypad.getKey();
    if (key)
    {
      alarm[z] = key;
      z++;
      i++;
      lcd.print(alarm, LEFT + 5, 30);
      lcd.update();

    }
  }
}

void StopAlarm()
{ 
  digitalWrite(buzzer,LOW);  
  int i = 0;
  char x=0;
  while (i < 4)
  {
    char x = 3;
    alarm[i] = x;
     
      i++;
    }
  delay(10);
}

void sleepmode() 
{   
   Sleep sleep;
   //sleep mode for six hours
   //turn off
     lcd.enableSleep();
     delay(50);
     //sleepmode      
    sleep.pwrDownMode(); //set sleep mode
    //sleep for six hours 1000*60*60*6=21600000
    sleep.sleepDelay(21600000); //sleep 
    //sleep.sleepDelay(21600000); //sleep 
     //turn on LCD
   // Serial.println("wake");   
    lcd.disableSleep();  
    delay(50);     
  
}
