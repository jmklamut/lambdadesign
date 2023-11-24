#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
int score = 0;
bool game = true;
bool input = true;

const int background_tone[] = {400, 300, 250, 200, -1, 300, 350};
const unsigned long background_duration[] = {200, 200, 150, 250, 100, 200, 250, 250};

const int defeat_tone[] = {200, 175, 150, 125};
const unsigned long defeat_duration[] = {300, 300, 300, 300};

const int victory_tone[] = {300, 225, 350, 375, -1, 375, -1, 375};
const unsigned long victory_duration[] = {150, 150, 150, 100, 50, 100, 50, 300};

const int success_tone[] = {300, 350, 400, 450};
const unsigned long success_duration[] = {150, 150, 150, 150};

const int reopen_tone[] = {500, -1, 500};
const unsigned long reopen_duration[] = {100, 100, 100};

const int button_tone[] = {-1, 200, -1};
const unsigned long button_duration[] = {100, 100, 100};

const int slide_tone[] = {150, 200, 250, 300, 350, 400};
const unsigned long slide_duration[] = {50, 50, 50, 50, 50, 50};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(8, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  
}

void success(){
  lcd.clear();
  digitalWrite(6, HIGH);
  score++;
  lcd.print(score);
}

void incorrect(){
  lcd.clear();
  lcd.print("You Lose");
  score = 0;
  game = false;
}

bool slice(float vPotStart)
{
  float newV = analogRead(A0);
  if(abs(newV - vPotStart) > 20)
  {
    return true;
  }
  else
  {
    return false;
  }

}

bool flipped(float flipVoltage)
{
  float newVoltage = analogRead(A1);

  if((newVoltage - flipVoltage) > 20)
  {
    return true;
  }
  else
    return false;
  
}

bool pushedButton()
{
  return !digitalRead(8);
}

bool fanOn()
{
  return analogRead(A2)>60;
}


void loop() {
  // put your main code here, to run repeatedly:
  float vPotStart = analogRead(A0);
  float flipVoltage = analogRead(A1);

  
  int number = random(1,5); // random input 
  int action = -1; //action needed
  int condition = 0; // if action met, condition 1, else condition -1, 0 defalut value

  if(number == 1){
    action = 1; //button input
  }
  else if(number == 2){
    action = 2; //slider input
  }
  else if(number == 3){
    action = 3; // rotary decoder input
  }
  else{
    action = 4; // pressure sensor input
  }


  if(action == 1){
      lcd.clear();
      lcd.print("Stack it!");
      delay(200);
      while(!input){
        if(flipped(flipVoltage)){
          lcd.clear();
          lcd.print("Flip");
          condition = -1;
          input = true;
        }
        else if(sliced(VPotStart)){
          lcd.clear();
          lcd.print("Sliced");
          condition = -1;
          input = true;

        }
        else if(fanOn()){
          lcd.clear();
          lcd.print("Fan");
          condition = -1;
          input = true;

        }
        else if(pushedButton()){
          lcd.clear();
          lcd.print("Pushed");
          condition = 1;
          input = true
        }
        else{
          lcd.clear();
          lcd.print("No read");
        }
      }
      //TODO: check correct sensor is pushed and not other sensors
      
  }
  else if(action == 2){
    lcd.clear();
    lcd.print("Slice it!");
    delay(200);
      while(!input){
        if(flipped(flipVoltage)){
          lcd.clear();
          lcd.print("Flip");
          condition = -1;
          input = true;
        }
        else if(sliced(VPotStart)){
          lcd.clear();
          lcd.print("Sliced");
          condition = -1;
          input = true;

        }
        else if(fanOn()){
          lcd.clear();
          lcd.print("Fan");
          condition = -1;
          input = true;

        }
        else if(pushedButton()){
          lcd.clear();
          lcd.print("Pushed");
          condition = 1;
          input = true
        }
        else{
          lcd.clear();
          lcd.print("No read");
        }
      }
    
    //TODO: check correct sensor is pushed and not other sensors
  }
  else if(action == 3){
    lcd.clear();
    lcd.print("Flip it!");
    delay(200);
      while(!input){
        if(flipped(flipVoltage)){
          lcd.clear();
          lcd.print("Flip");
          condition = -1;
          input = true;
        }
        else if(sliced(VPotStart)){
          lcd.clear();
          lcd.print("Sliced");
          condition = -1;
          input = true;

        }
        else if(fanOn()){
          lcd.clear();
          lcd.print("Fan");
          condition = -1;
          input = true;

        }
        else if(pushedButton()){
          lcd.clear();
          lcd.print("Pushed");
          condition = 1;
          input = true
        }
        else{
          lcd.clear();
          lcd.print("No read");
        }
      }
    //TODO: check correct sensor is pushed and not other sensors
  }
  else if(action == 4){
    lcd.clear();
    lcd.print("Air it!");
    delay(200);
      while(!input){
        if(flipped(flipVoltage)){
          lcd.clear();
          lcd.print("Flip");
          condition = -1;
          input = true;
        }
        else if(sliced(VPotStart)){
          lcd.clear();
          lcd.print("Sliced");
          condition = -1;
          input = true;

        }
        else if(fanOn()){
          lcd.clear();
          lcd.print("Fan");
          condition = -1;
          input = true;

        }
        else if(pushedButton()){
          lcd.clear();
          lcd.print("Pushed");
          condition = 1;
          input = true
        }
        else{
          lcd.clear();
          lcd.print("No read");
        }
      }
    
    //TODO: check correct sensor is pushed and not other sensors
  }

  if(condition == 1){
    success();
  }
  else if(condition == -1){
    incorrect();
  }

  if(game == false){
    //TODO: restart the game
  }
  
  input = false;
    //TODO: don't restart
  


//testing
/*
  float value = analogRead(A2);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcg.print(value);
  delay(500);
  */




}

