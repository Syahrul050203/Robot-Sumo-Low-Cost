#include <Arduino.h>
#include <NewPing.h>

// #define EN_B  5
// #define IN_4  2
// #define IN_3  3
// #define IN_2  4
// #define IN_1  7
// #define EN_A  6

const int16_t trigger_pin = 9;
const int16_t echo_pin = 10;

const int max_distance = 200;

NewPing ultrasonic(trigger_pin, echo_pin, max_distance);

void moveForward(int16_t pwm) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(PORTD6, pwm);
  analogWrite(PORTD5, pwm);
}
void backOff(int16_t pwm) {
  PORTD |= (1<<4) | (1<<2);
  analogWrite(PORTD6, pwm);
  analogWrite(PORTD5, pwm);
}

void motorStop() {
  PORTD = 0x00;
}

void moveRight(int16_t pwm_left, int16_t pwm_right) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(PORTD6, pwm_right);
  analogWrite(PORTD5, pwm_left);
}

void moveLeft(int16_t pwm_left, int16_t pwm_right) {
  PORTD |= (1<<7) | (1<<3);
  analogWrite(PORTD5, pwm_left);
  analogWrite(PORTD6, pwm_right);
}



void setup() {
  Serial.begin(57600);

  DDRB &= ~(1<<0);
  DDRD = 0xFC;
}

void loop() {
  uint16_t jarak = ultrasonic.ping_cm();
  uint8_t nilai_infrared = digitalRead(PORTD0);
  
  //coba sensor
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  if (nilai_infrared) 
    Serial.println("Posisi : Dalam Arena");
  else 
    Serial.println("Posisi : Garis Tepi Arena");



  delay(500);
}


