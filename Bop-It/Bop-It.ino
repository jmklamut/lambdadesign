#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
int score = 0;
bool game = true;
bool input = false;
bool playing_game = false;
bool cool_it = false;
bool slice_it = false;
bool flip_it = false;
bool press_it = false;

const int background_tone[] = {400, 300, 250, 200, -1, 300, 350};
const unsigned long background_duration[] = {200, 200, 150, 250, 100, 200, 250, 250};
const int background_tone_size = 7;

const int defeat_tone[] = {200, 175, 150, 125};
const unsigned long defeat_duration[] = {300, 300, 300, 300};
const int defeat_tone_size = 4;

const int victory_tone[] = {300, 225, 350, 375, -1, 375, -1, 375};
const unsigned long victory_duration[] = {150, 150, 150, 100, 50, 100, 50, 300};
const int victory_tone_size = 8;

const int success_tone[] = {300, 350, 400, 450};
const unsigned long success_duration[] = {150, 150, 150, 150};
const int success_tone_size = 4;

const int cool_tone[] = {500, -1, 500};
const unsigned long cool_duration[] = {100, 100, 100};
const int cool_tone_size = 3;

const int button_tone[] = {-1, 200, -1};
const unsigned long button_duration[] = {100, 100, 100};
const int button_tone_size = 3;

const int slide_tone[] = {150, 200, 250, 300, 350, 400};
const unsigned long slide_duration[] = {50, 50, 50, 50, 50, 50};
const int slide_tone_size = 6;

const int flip_tone[] = {150, 200, 250, 300, 350, 400};
const unsigned long flip_duration[] = {50, 50, 50, 50, 50, 50};
const int flip_tone_size = 6;



void success(){
  lcd.clear();
 // digitalWrite(6, HIGH);
  score++;
  lcd.print(score);
}

void incorrect(){
  lcd.clear();
  lcd.print("You Lose");
  score = 0;
  game = false;
  delay(1000);
}

bool sliced(float vPotStart)
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

void play_tone(int sounds[], unsigned long duration[], int size){
  //unsigned long last_tone_start = millis();
  int current_tone = 0;

  while (current_tone >= 0 && current_tone < size) {
    tone(9, sounds[current_tone], duration[current_tone]);
    delay(duration[current_tone]);
    noTone(9);
    current_tone++;
  }
}

void sliceTone()
{
  tone(9, 1000);
  delay(100);
  noTone(9);
  delay(100);
  tone(9,1000);
  delay(100);
  noTone(9);
  delay(100);
  tone(9,1000);
  delay(100);
  noTone(9);

}

void flipTone()
{
  tone(9, 2000);
  delay(100);
  noTone(9);
  delay(100);
  tone(9,2000);
  delay(100);
  noTone(9);

}

void stackTone()
{
  tone(9, 600);
  delay(100);
  noTone(9);
  delay(100);
  tone(9,600);
  delay(100);
  noTone(9);
  delay(100);
  tone(9,600);
  delay(100);
  noTone(9);
  tone(9, 600);
  delay(100);
  noTone(9);

}

void coolTone()
{
  tone(9, 1500);
  delay(200);
  noTone(9);

}





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(8, INPUT_PULLUP);
 // pinMode(7, INPUT_PULLUP);
  //pinMode(6, OUTPUT);
  
}

void loop() {

  int count = 0;

  float vPotStart = analogRead(A0);
  float flipVoltage = analogRead(A1);

    
  int number = round(random(1,5)); // random input 
  int action = -1; //action needed
  int condition = 0; // if action met, condition 1, else condition -1, 0 defalut value

  lcd.clear();
  if(number == 1){
    action = 1; //button input
    lcd.print("Stack It");
    stackTone();
  }
  else if(number == 2){
    action = 2; //slider input
    lcd.print("Slice It");
    sliceTone();
  }
  else if(number == 3){
    action = 3; // rotary decoder input
    lcd.print("Flip It");
    flipTone();
  }
  else{
    action = 4; // pressure sensor input
    lcd.print("Cool It");
    coolTone();
  }

  bool cool_it = false;
  bool slice_it = false;
  bool flip_it = false;
  bool press_it = false;

  while(!input){
    if(flipped(flipVoltage)){
      lcd.clear();
      lcd.print("Flip");
      flip_it = true;
      input = true;
    //  play_tone(flip_tone, flip_duration, flip_tone_size);
      delay(500);
    }
    else if(sliced(vPotStart)){
      lcd.clear();
      lcd.print("Sliced");
      slice_it = true;
      input = true;
     // play_tone(slide_tone, slide_duration, slide_tone_size);
      delay(500);
    }
    else if(fanOn()){
      lcd.clear();
      lcd.print("Fan");
      cool_it = true;
      input = true;
      //play_tone(cool_tone, cool_duration, cool_tone_size);
      delay(500);
    }
    else if(pushedButton()){
      lcd.clear();
      lcd.print("Stacked");
      press_it = true;
      input = true;
      //play_tone(button_tone, button_duration, button_tone_size);
      delay(500);
    }
  }

  input = false;

  if((flip_it && (action == 3)) || (slice_it && (action == 2)) || (press_it && (action == 1)) || (cool_it && (action == 4))){
    success();
    delay(1000);
  }
  else{
    incorrect();
    delay(1000);
  }
  delay(5000);
  
  
  // put your main code here, to run repeatedly:
  /*
  if(!digitalRead(8) && playing_game == false){
    playing_game = true;
    lcd.clear();
    lcd.print("Starting game . . .");
    delay(1000);
  }
  else if(playing_game == false){
    lcd.setCursor(0,0);
    lcd.print("Press Button");
    lcd.setCursor(0,1);
    lcd.print("To Start");
  }
  
  
  while(playing_game){
    */
    /*
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
            play_tone(flip_tone, flip_duration, flip_tone_size);
            delay(500);
          }
          else if(sliced(vPotStart)){
            lcd.clear();
            lcd.print("Sliced");
            condition = -1;
            input = true;
            play_tone(slide_tone, slide_duration, slide_tone_size);
            delay(500);
          }
          else if(fanOn()){
            lcd.clear();
            lcd.print("Fan");
            condition = -1;
            input = true;
            play_tone(cool_tone, cool_duration, cool_tone_size);
            delay(500);

          }
          else if(pushedButton()){
            lcd.clear();
            lcd.print("Stacked");
            condition = 1;
            input = true;
            play_tone(button_tone, button_duration, button_tone_size);
            delay(500);
          }
          delay(200);
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
            play_tone(flip_tone, flip_duration, flip_tone_size);
            delay(500);
          }
          else if(sliced(vPotStart)){
            lcd.clear();
            lcd.print("Sliced");
            condition = 1;
            input = true;
            play_tone(slide_tone, slide_duration, slide_tone_size);
            delay(500);
          }
          else if(fanOn()){
            lcd.clear();
            lcd.print("Fan");
            condition = -1;
            input = true;
            play_tone(cool_tone, cool_duration, cool_tone_size);
            delay(500);

          }
          else if(pushedButton()){
            lcd.clear();
            lcd.print("Stacked");
            condition = -1;
            input = true;
            play_tone(button_tone, button_duration, button_tone_size);
            delay(500);
          }
          delay(200);
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
            condition = 1;
            input = true;
            play_tone(flip_tone, flip_duration, flip_tone_size);
            delay(500);
          }
          else if(sliced(vPotStart)){
            lcd.clear();
            lcd.print("Sliced");
            condition = -1;
            input = true;
            play_tone(slide_tone, slide_duration, slide_tone_size);
            delay(500);
          }
          else if(fanOn()){
            lcd.clear();
            lcd.print("Fan");
            condition = -1;
            input = true;
            play_tone(cool_tone, cool_duration, cool_tone_size);
            delay(500);
          }
          else if(pushedButton()){
            lcd.clear();
            lcd.print("Stacked");
            condition = -1;
            input = true;
            play_tone(button_tone, button_duration, button_tone_size);
            delay(500);
          }
          delay(200);
        }
      //TODO: check correct sensor is pushed and not other sensors
    }
    else if(action == 4){
      lcd.clear();
      lcd.print("Cool it!");
      delay(200);
        while(!input){
          if(flipped(flipVoltage)){
            lcd.clear();
            lcd.print("Flip");
            condition = -1;
            input = true;
            play_tone(flip_tone, flip_duration, flip_tone_size);
            delay(500);
          }
          else if(sliced(vPotStart)){
            lcd.clear();
            lcd.print("Sliced");
            condition = -1;
            input = true;
            play_tone(slide_tone, slide_duration, slide_tone_size);
            delay(500);
          }
          else if(fanOn()){
            lcd.clear();
            lcd.print("Cooled it");
            condition = 1;
            input = true;
            play_tone(cool_tone, cool_duration, cool_tone_size);
            delay(500);
          }
          else if(pushedButton()){
            lcd.clear();
            lcd.print("Pushed");
            condition = -1;
            input = true;
            play_tone(button_tone, button_duration, button_tone_size);
            delay(500);
          }
          delay(500);
        }
      
      //TODO: check correct sensor is pushed and not other sensors
    }

    if(condition == 1){
      success();
      play_tone(success_tone, success_duration, success_tone_size);
    }
    else if(condition == -1){
      play_tone(defeat_tone, defeat_duration, defeat_tone_size);
      incorrect();
      playing_game = false;
    }  
    input = false;
 // }
 */

}








