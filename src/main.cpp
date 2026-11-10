#include <Arduino.h>

struct Encoder {
  uint8_t pinA;
  uint8_t pinB;
  uint8_t previousState;
  int8_t quarterSteps;
  const char *name;
};

const uint8_t INNER_A_PIN = 4;
const uint8_t INNER_B_PIN = 5;
const uint8_t OUTER_A_PIN = 3;
const uint8_t OUTER_B_PIN = 2;
const uint8_t BUTTON_PIN = 6;

const int8_t ENCODER_STEPS_PER_DETENT = 4;
const unsigned long BUTTON_DEBOUNCE_MS = 25;

const int8_t transitionTable[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};

Encoder innerEncoder = {INNER_A_PIN, INNER_B_PIN, 0, 0, "SMALL KNOB"};
Encoder outerEncoder = {OUTER_A_PIN, OUTER_B_PIN, 0, 0, "LARGE KNOB"};

bool buttonRawState = HIGH;
bool buttonStableState = HIGH;
unsigned long buttonLastChangedAt = 0;

uint8_t readEncoderState(const Encoder &encoder) {
  return (digitalRead(encoder.pinA) << 1) | digitalRead(encoder.pinB);
}

void initializeEncoder(Encoder &encoder) {
  pinMode(encoder.pinA, INPUT_PULLUP);
  pinMode(encoder.pinB, INPUT_PULLUP);
  encoder.previousState = readEncoderState(encoder);
}

void printEncoderEvent(const char *name, const char *direction) {
  Serial.print(name);
  Serial.print(',');
  Serial.println(direction);
}

void updateEncoder(Encoder &encoder) {
  const uint8_t currentState = readEncoderState(encoder);
  const uint8_t transition = (encoder.previousState << 2) | currentState;
  encoder.quarterSteps -= transitionTable[transition];
  encoder.previousState = currentState;

  if (encoder.quarterSteps >= ENCODER_STEPS_PER_DETENT) {
    encoder.quarterSteps -= ENCODER_STEPS_PER_DETENT;
    printEncoderEvent(encoder.name, "CW");
  } else if (encoder.quarterSteps <= -ENCODER_STEPS_PER_DETENT) {
    encoder.quarterSteps += ENCODER_STEPS_PER_DETENT;
    printEncoderEvent(encoder.name, "CCW");
  }
}

void updateButton() {
  const bool reading = digitalRead(BUTTON_PIN);
  const unsigned long now = millis();

  if (reading != buttonRawState) {
    buttonRawState = reading;
    buttonLastChangedAt = now;
  }

  if ((now - buttonLastChangedAt) >= BUTTON_DEBOUNCE_MS &&
      buttonStableState != buttonRawState) {
    buttonStableState = buttonRawState;
    Serial.println(buttonStableState == LOW ? "BUTTON,PRESSED" : "BUTTON,RELEASED");
  }
}

void setup() {
  Serial.begin(115200);

  initializeEncoder(innerEncoder);
  initializeEncoder(outerEncoder);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  buttonRawState = digitalRead(BUTTON_PIN);
  buttonStableState = buttonRawState;
  buttonLastChangedAt = millis();

  Serial.println("DUAL_ROTARY_ENCODER,READY");
}

void loop() {
  updateEncoder(innerEncoder);
  updateEncoder(outerEncoder);
  updateButton();
}
