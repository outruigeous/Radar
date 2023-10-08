int pos = 0; 
int servoPin = 13;
int trigPin = 26;
int echoPin = 27;
int dist()
{
    long duration, distance = -1; // initialize, like int sensor = 0, number doesn't mean anything

    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); // this is the peak of the trigger
    digitalWrite(trigPin, LOW); // this like pressing a button, like HIGH is key down and LOW is key up

    // if value is HIGH, pulseIn() waits for the pin to go from LOW to HIGH, starts timing, then waits for the pin to go LOW and stops timing. Returns the length of the pulse in microseconds or gives up and returns 0 if no complete pulse was received within the timeout.
    duration = pulseIn(echoPin, HIGH); 
    distance = (duration/2) * 0.0343; // distance = speed x time
    
    if (distance >= 20) {
        Serial.println("Out of range");
    }
    else {
        Serial.print(distance);
        Serial.println(" cm");
    }
        return distance;
}


void setup () {
    Serial.begin(9600);
    pinMode(servoPin, OUTPUT); // define this because we are not using the library
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}


void loop () {
    for (pos = 0; pos <= 180; pos ++) { // goes from 0 degrees to 180 degrees
    {
        mysweep(pos);
        delay(15); // waits 15ms for servo to reach the position
        dist();
    }
   
    }

    for (pos = 180; pos >=0; pos --) { // goes from 180 degrees to 0 degrees
        mysweep(pos);
        delay(15); // waits 15ms for the servo to reach the position
        dist();
    }
    
}

void mysweep (int p) // mysweep is a function, that we can define any parameters inside, like int p
{
    // trying to find what's the peak time through converting angle to microseconds 
    // (x, from this, from this, to this, to this)
    int peakTime = map (p, 0, 180, 500, 2600);
    // this is the pulse width
    int entirePauseWidth = 20000; 
    digitalWrite(servoPin, HIGH); // 3V
    delayMicroseconds(peakTime); 
    int lowTime = entirePauseWidth - p; // lowTime = entirePauseWidth - peakTime
    digitalWrite(servoPin, LOW); // 0V
    delayMicroseconds(lowTime);
}