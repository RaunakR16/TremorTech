// Pin number for vibrator
const int transistorPin = 9;

// Pin number for GSR sensor
const int gsr_pin = A0;


const int minIntensity = 50; // Min intensity level
const int maxIntensity = 100; // Max intensity level

// Time variables
unsigned long vibrationStartTime = 0; // Start time of vibration
const unsigned long vibrationDuration = 10000; // Duration of vibration in ms (10 seconds)

void setup() 
{
  pinMode(transistorPin, OUTPUT); // vibrator pin as output
  Serial.begin(9600); // serial communication
}

void loop() 
{
  int gsr_value = analogRead(gsr_pin); // Read the analog input from the GSR sensor
  delay(1000); // Adjust the delay based on how smoothly we want to take the GSR value
  Serial.println(gsr_value); // Print the GSR value to the serial monitor

  // Check if GSR sensor value is lower than 400
  if (gsr_value < 500) 
  {
    // Start vibration if it's not already started
    if (vibrationStartTime == 0) 
    {
      vibrationStartTime = millis(); // save the start time of vibration
    }
    
    // Calculate elapsed time since vibration started
    unsigned long elapsedTime = millis() - vibrationStartTime;
    
    // Checking if vibration duration has elapsed
    if (elapsedTime < vibrationDuration) 
    {
      // Adjust range (minIntensity-maxIntensity) based on time using a sine wave
      int timePeriod = 10000; // Time period for one cycle (in ms)
      int intensityRange = maxIntensity - minIntensity; // Range of intensity values
      int intensity = minIntensity + intensityRange / 2 + intensityRange / 2 * sin(2 * PI * millis() / timePeriod); // Sine wave function for intensity variation over time
      analogWrite(transistorPin, intensity);
      delay(1); // Adjust the delay based on how smoothly we want to change the intencity
    } 
    else 
    {
      // If vibration duration has elapsed, turn off vibration
      analogWrite(transistorPin, 0);
      vibrationStartTime = 0; // Reset the vibration start time for the next cycle
    }
  } 
  else 
  {
    // If GSR sensor value is not lower than 400, turn off vibration
    analogWrite(transistorPin, 0);
    vibrationStartTime = 0; // Reset the vibration start time
  }
}
