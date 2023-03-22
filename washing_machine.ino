#include<LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int motor=8;//motor pin//
int button_wash=9;//button to start the washing//
int button_dry=10;//button to start the drying //
int set_zero=11;//button uesd to set the time 0//
int set=12;//button to set the time //
float time=0;//variable to store the value of time//
int dry=13;//output pin for dryer motor //
int set_time,zero,rem_time,time2;//variable to store the some important value// 
float current_time;// variable to store the current time when entering in the function//
//_________________________________________________//
void setup()
{
  pinMode(dry,OUTPUT);
  pinMode(set,INPUT_PULLUP);
  pinMode(motor,OUTPUT);
  pinMode(button_wash,INPUT_PULLUP);
  pinMode(button_dry,INPUT_PULLUP);
  pinMode(set_zero,INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Welcome");
}
void loop() 
{
   int wash,dry,zero;
   wash=digitalRead(9);// to read the digital value present on the pin number 9// 
   dry=digitalRead(10);// to read the digital value present on the pin number 10//
   set_time=digitalRead(12);// to read the digital vlaue present on the pin number 12//
   zero=digitalRead(11);// to read the digital value present on the pin number 11//
   delay(1000);
   if(wash==0){
     start_wash();
   }
   else if(dry==0){
     start_dry();
   }
   else if(set_time==0){
     time1();
   }
   else if(zero==0){
     time=0;             
  }
   else{
    if(time==0){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Set timer:");
     }
     else{
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("timer set");
     
     }
   }
}
//_____________________________________________________________________//
//function for start the washing//
//____________________________________________________________________//
 void start_wash(){
   rem_time=1;time2=time;
  current_time = millis();
   if((millis()-current_time)<time){
    lcd.clear();
    lcd.print("Washing start");
    lcd.setCursor(0,1);
    lcd.print("time_rem:");
    lcd.print(time2);
    lcd.print("m");
     while((millis()-current_time)<=time*60000){
      digitalWrite(motor,1);
      if(digitalRead(11)==0){
        break;
      }
      if((millis()-current_time)==rem_time*60000){
        time2=time2-1;
        rem_time=rem_time+1;
        lcd.setCursor(0,1);
        lcd.print("time_rem:");
        lcd.print(time2);
        lcd.print("m");
      }
    }
    delay(300);
    digitalWrite(motor,0);
    rem_time=1;
    time=0;
    lcd.clear();
    lcd.print("Washing stop");
   }
   else{
     digitalWrite(motor,0);
     lcd.clear();
     lcd.print("Timer not set");
     lcd.setCursor(0,1);
     lcd.print("(wash)");
   }
 }
//________________________________________________________________//
// function for drying the cloths//
//_______________________________________________________________//
 void start_dry()
 {
    rem_time=1;
    time2=time;      
    current_time=millis();
   if((millis()-current_time)<time){
     lcd.clear();
     lcd.print("drying start");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print("time_rem:");
     lcd.print(time2);
     lcd.print("m");    
    while((millis()-current_time)<=time*60000){
     digitalWrite(dry,1);
     if(digitalRead(11)==0){
       break;
     }
     if((millis()-current_time)==rem_time*60000){
        time2=time2-1;
        rem_time=rem_time+1;
        lcd.setCursor(0,1);
        lcd.print("time_rem:");
        lcd.print(time2);
        lcd.print("m");
      }
    }
    delay(300);   
    rem_time=1;
    time=0; 
    digitalWrite(dry,0);
    lcd.clear();
    lcd.print("Drying stop");     
   }
  else{
     digitalWrite(dry,0);
    lcd.clear();
    lcd.print("Timer not set");
    lcd.setCursor(0,1);
    lcd.print("(dry)");
   }
 }
// ______________________________________________________//
// function to set the timmer for drying and washing
//______________________________________________________//
 void time1()
 {
   while(set_time==0){
    time=time+1;
    lcd.clear();
    lcd.print(time);
    set_time=digitalRead(12);
    delay(1000);
   }
 }
//______________________________________________________// 
