const int ledPins[] = {11,10, 9, 8}; // Red, Blue, Yellow, Green (Read from left to right like wiring)
const int numLeds = 4;
int sequence[100];
int level = 1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));
  Serial.println("=== LED Memory Game ===");
  delay(2000);
}

void loop() {
  // Generate sequence step for current level
  sequence[level - 1] = random(0, numLeds);

  // Play the sequence
  Serial.print("\nLevel ");
  Serial.print(level);
  Serial.println(": Watch the LEDs!");
  delay(1000);

  // blinking LED(s)
  for (int i = 0; i < level; i++) {
    int pin = ledPins[sequence[i]];
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(250);
  }

  // Get user input from Serial Monitor
  Serial.println("Your turn! Type the sequence (0-3 for each LED) and press Enter:");
  
  for (int i = 0; i < level; i++) {
    while (Serial.available() == 0) {
      // Wait for user to type
    }
    // Read single character '0' - '3'
    int userChoice = Serial.read() - '0';
    // Clear out any trailing newline/carriage return characters
    while (Serial.available() > 0) { Serial.read(); }

    if (userChoice != sequence[i]) {
      Serial.println("Wrong! Game Over. Restarting...");
      // all LEDs blink
      for (int flash = 0; flash < 3; flash++) {
        for (int p = 0; p < numLeds; p++) digitalWrite(ledPins[p], HIGH);
        delay(200);
        for (int p = 0; p < numLeds; p++) digitalWrite(ledPins[p], LOW);
        delay(200);
      }
      level = 1;
      delay(2000);
      return;
    }
  }

  Serial.println("Correct! Next level...");
  level++;
  delay(1500);
}

