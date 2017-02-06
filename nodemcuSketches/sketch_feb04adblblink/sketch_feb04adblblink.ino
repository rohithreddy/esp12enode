const short int BUILTIN_LED1 = 2;
const short int BUILTIN_LED2 = 16;


void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED1, OUTPUT);
  pinMode(BUILTIN_LED2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUILTIN_LED1, LOW); // Turn the LED ON by making the voltage LOW digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED off by making the voltage HIGH delay(1000); // Wait for a second 
  digitalWrite(BUILTIN_LED1, HIGH); // Turn the LED off by making the voltage HIGH 
  digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW 
  delay(2000); // Wait for two seconds
  digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED ON by making the voltage LOW digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED off by making the voltage HIGH delay(1000); // Wait for a second 
  digitalWrite(BUILTIN_LED1, LOW); // Turn the LED off by making the voltage HIGH 
  digitalWrite(BUILTIN_LED1, HIGH); // 
}
