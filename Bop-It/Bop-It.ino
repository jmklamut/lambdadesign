#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20, 16, 2);
int score = 0;
bool game = true;

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
  delay(500);
}

void incorrect(){
  lcd.clear();
  lcd.print("You Lose");
  score = 0;
  delay(500);
  game = false;
}

bool changedPot(float vPotStart)
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

/*
  randomSeed(millis());

  int number = randomSeed(1,5); // random input 
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

  delay(250);

  if(action == 1){
      lcd.clear();
      lcd.print("Stack it!");
      //TODO: check correct sensor is pushed and not other sensors
      
  }
  else if(action == 2){
    lcd.clear();
    lcd.print("Slice it!");
    //TODO: check correct sensor is pushed and not other sensors
  }
  else if(action == 3){
    lcd.clear();
    lcd.print("Flip it!");
    //TODO: check correct sensor is pushed and not other sensors
  }
  else if(action == 4){
    lcd.clear();
    lcd.print("Air it!");
    //TODO: check correct sensor is pushed and not other sensors
  }

  delay(250);

  if(condition == 1){
    success();
  }
  else if(condition == -1){
    incorrect();
  }

  if(game == false){
    //TODO: restart the game
  }
  else(
    //TODO: don't restart
  )
*/

//testing
  float value = analogRead(A2);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcg.print(value);
  delay(500);




}

