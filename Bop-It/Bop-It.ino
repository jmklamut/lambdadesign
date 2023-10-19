void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  

}

int randomNumber(){
  randomNumber = random(1,5);
  return randomNumber;

}

void loop() {
  // put your main code here, to run repeatedly:


}
