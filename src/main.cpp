#include <Arduino.h>
#include <NewPing.h>

#define EN_B  5
#define EN_A  6

const int16_t trigger_pin = 9;
const int16_t echo_pin = 10;
const int16_t max_distance = 30;

uint8_t jarak;
uint8_t nilai_infrared;

NewPing ultrasonic(trigger_pin, echo_pin, max_distance);

void moveForward(uint8_t pwm) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(EN_A, pwm);
  analogWrite(EN_B, pwm);
}

void backOff(uint8_t pwm) {
  PORTD |= (1<<4) | (1<<2);
  analogWrite(EN_A, pwm);
  analogWrite(EN_B, pwm);
}

void motorStop() {
  PORTD = 0x00;
}

void moveRight(uint8_t pwm_left, uint8_t pwm_right) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(EN_A, pwm_right);
  analogWrite(EN_B, pwm_left);
}

void moveLeft(uint8_t pwm_left, uint8_t pwm_right) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(EN_B, pwm_left);
  analogWrite(EN_A, pwm_right);
}

void checkDistace() {
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
}

void checkLineSensor() {
  Serial.print("Nilai garis: ");
  Serial.println(nilai_infrared);
}

void attackEnemie() {
  if (jarak > 0 && jarak <= 15 && nilai_infrared == 0) {
      moveForward(255);
  }
  else if (!jarak && nilai_infrared == 0) {
    moveLeft(0, 255);
  }
  else {
    motorStop();
    while (nilai_infrared) {
      backOff(255);
      delay(1000);
      return ;
    }
  }
}

void setup() {
  Serial.begin(57600);

  DDRB &= ~(1<<0);
  DDRD = 0xFC;
}

void loop() {
  jarak = ultrasonic.ping_cm();
  nilai_infrared = digitalRead(8);
  
  for (uint16_t time = 0; time < 3000; time++) {
    motorStop();
  }

  while(1) {
    attackEnemie();
  }  
}


