#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int potPins[5] = {A0, A1, A2, A3, A4};
int servoChannels[4] = {0, 1, 2, 3, 4};
int previousPulse[4] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(10);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int potValue = analogRead(potPins[i]);
    int targetPulse = map(potValue, 0, 1023, 0, 300);
    slowMove(i, previousPulse[i], targetPulse, 3);
    previousPulse[i] = targetPulse;
  }
  delay(5);
}

void slowMove(int channel, int fromPulse, int toPulse, int delayTime) {
  if (fromPulse == toPulse) return;

  int step = (fromPulse < toPulse) ? 1 : -1;

  for (int p = fromPulse; p != toPulse; p += step) {
    pwm.setPWM(channel, 0, p);
    delay(delayTime);
  }
  pwm.setPWM(channel, 0, toPulse);
}
