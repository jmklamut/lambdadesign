#include <LiquidCrystal_I2C.h>

//variables used in the game
LiquidCrystal_I2C lcd(0x27, 16, 2);
int score = 0;
int final_score = 0;
bool input = false;
bool playing_game = false;
bool cool_it = false;
bool slice_it = false;
bool flip_it = false;
bool press_it = false;
unsigned long threshold = 4000;

//tones for play_tone function
const int defeat_tone[] = {200, 175, 150, 125};
const unsigned long defeat_duration[] = {300, 300, 300, 300};
const int defeat_tone_size = 4;

const int victory_tone[] = {300, 225, 350, 375, -1, 375, -1, 375};
const unsigned long victory_duration[] = {150, 150, 150, 100, 50, 100, 50, 300};
const int victory_tone_size = 8;

const int success_tone[] = {300, 350, 400, 450};
const unsigned long success_duration[] = {150, 150, 150, 150};
const int success_tone_size = 4;

//don't end up using these cool_tone, button_tone, slide_tone, flip_tone
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


//when succesful input
void success(){
  lcd.clear();
 // digitalWrite(6, HIGH);
  play_tone(success_tone, success_duration, success_tone_size);
  lcd.setCursor(0,0);
  lcd.print("Success!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  score++; //increase score
  lcd.print(score);
  if(score == 99){ // if the user reaches 99, they win
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You Win!");
    digitalWrite(7, HIGH); // turn on green led
    play_tone(victory_tone, victory_duration, victory_tone_size);
    playing_game == false; //reset 
    threshold = 4000; //reset
    score = 0;
    delay(4000);
  }
}

//when incorrect input, player loses
void incorrect(){
  final_score = score;
  lcd.clear();
  play_tone(defeat_tone, defeat_duration, defeat_tone_size);
  digitalWrite(6, HIGH); //turn on red led
  lcd.print("You Lose");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(final_score);
  delay(4000);
  score = 0; //reset
  playing_game = false; //reset
  threshold = 4000; //reset
  lcd.clear();
}

// if a slice is detected return true
bool sliced(float vPotStart)
{
  float newV = analogRead(A0);
  if(abs(newV - vPotStart) > 100) //change is greater than 100
  {
    return true;
  }
  else
  {
    return false;
  }

}

//if a flip is detected return true
bool flipped(float flipVoltage)
{
  float newVoltage = analogRead(A1);

  if(abs(newVoltage - flipVoltage) > 200) //change greater than 200
  {
    return true;
  }
  else
    return false;
  
}

//button is pushed return true
bool pushedButton()
{
  return !digitalRead(8);
}

// if the fan detects a voltage, return true
bool fanOn()
{
  return analogRead(A2)>60; //change greater than 60
}

// will play the arrays of sounds using the sound duration and size
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

//slicetone, fliptone, stacktone, cooltone are used when that action needs to be preformed
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




//sets up ardunio
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  randomSeed(analogRead(A3));


  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  
}

void loop() {

  //resets leds
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  //waits for user to press button to start game
  while(playing_game == false){
    if((digitalRead(8) == HIGH)){
      lcd.setCursor(0,0);
      lcd.print("Press Button");
      lcd.setCursor(0,1);
      lcd.print("To Start");
    }
    else if(digitalRead(8) == LOW){
      playing_game = true;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Starting...");
      delay(1000);
    }
  }
  
  //if playing game
  while(playing_game){
    float vPotStart = analogRead(A0);
    float flipVoltage = analogRead(A1);

    //chooses an action for user to perform
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

    //time that has passed in the game
    unsigned long start_time = millis();

  //if there isn't an input detected and time hasn't run out
    while(!input && ((millis() - start_time) < threshold)){
      
      //true if flip is detected(input is previous position of potentiometer)
      if(flipped(flipVoltage)){
        //lcd.clear();
       // lcd.print("Flip");
        flip_it = true;
        input = true;
        //play_tone(flip_tone, flip_duration, flip_tone_size);
       // delay(10000);
      }
      
      //true if slice is detected(input is previous position of potentiometer)
      if(sliced(vPotStart)){
        //lcd.clear();
       // lcd.print("Sliced");
        slice_it = true;
        input = true;
       //play_tone(slide_tone, slide_duration, slide_tone_size);
       // delay(10000);
      }
      ///true if fan voltage detected
      else if(fanOn()){
       // lcd.clear();
      //  lcd.print("Fan");
        cool_it = true;
        input = true;
       // play_tone(cool_tone, cool_duration, cool_tone_size);
      //  delay(10000);
      }
      //turn if button is pushed
      else if(pushedButton()){
       // lcd.clear();
       // lcd.print("Stacked");
        press_it = true;
        input = true;
        //play_tone(button_tone, button_duration, button_tone_size);
       // delay(10000);
      }
      delay(100);
    }

    //decreases the threshold
    threshold = threshold - 50;
    if (threshold < 650){
      threshold = 650; // threshold limit
    }

  // if no input and time runs out
    if(input == false){
      incorrect();
      delay(1000);
    }
    // if input is detected it matches the action
    if((flip_it && (action == 3)) || (slice_it && (action == 2)) || (press_it && (action == 1)) || (cool_it && (action == 4))){
      success();
      delay(1000);
    }
    //if input is detected but wrong input
    else if(input == true){
      incorrect();
      delay(1000);
    }
    //resets for next incoming input
    input = false;
  }

  //Code below here is protyped code
  //}
  
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








