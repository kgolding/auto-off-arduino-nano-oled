#include <Arduino.h>
#include <JC_Button.h> // https://github.com/JChristensen/JC_Button
#include <OneBitDisplay.h>

#define STEP_MINS 30
#define MAX_ON_MINS 300
#define MAX_ON_MS long(MAX_ON_MINS) * 60 * 1000
#define OFF_DELAY_MS 6000
#define BTN_GREEN 12
#define BTN_RED 11
#define RELAY 9

Button BtnGreen(BTN_GREEN);
Button BtnRed(BTN_RED);

OBDISP obd;

#include "display.h"

void setup()
{
  BtnGreen.begin();
  BtnRed.begin();

  pinMode(RELAY, OUTPUT);

  digitalWrite(RELAY, LOW);

  Serial.begin(9600);

  Serial.println("Started");
  // int obdI2CInit(OBDISP *pOBD, int iType, int iAddr, int bFlip, int bInvert, int bWire, int sda, int scl, int reset, int32_t iSpeed)
  obdI2CInit(&obd, OLED_128x64, -1, 0, 0, 1, -1, -1, -1, 400000L);
  displayIntro(&obd);
}

enum states_t
{
  OFF,
  ON,
  WARN,
  OFF_DELAYED
};

states_t STATE = OFF;
long switchOffAt = 0;

long secondsRemaining()
{
  return (switchOffAt - millis()) / 1000;
}

void extendTime()
{
  Serial.println("Extend time");
  switchOffAt += long(STEP_MINS) * 60 * 1000;
  if (switchOffAt > MAX_ON_MS) {
    switchOffAt = MAX_ON_MS;
  }
  STATE = ON;
}

void switchOn()
{
  Serial.println("Relay ON");
  digitalWrite(RELAY, HIGH);
  STATE = ON;
  switchOffAt = millis() + long(STEP_MINS) * 60 * 1000;
}

void switchOff()
{
  Serial.println("Relay OFF");
  digitalWrite(RELAY, LOW);
  STATE = OFF;
  switchOffAt = 0;
}

void loop()
{
  states_t lastState = STATE;
  static long lastUpdate = millis();

  BtnGreen.read();
  BtnRed.read();

  if (BtnRed.wasPressed() && STATE != OFF)
  {
    Serial.println("RED Button");
    STATE = OFF_DELAYED;
    switchOffAt = millis() + OFF_DELAY_MS;
  }
  else if (BtnGreen.wasPressed())
  {
    Serial.println("GREEN Button");
    switch (STATE)
    {
    case OFF:
    case OFF_DELAYED:
      switchOn();
      break;
    case ON:
    case WARN:
      extendTime();
      break;
    }
  }

  long secs = secondsRemaining();
  switch (STATE)
  {
  case OFF:
    break;
  case ON:
    if (secs < 120)
    {
      Serial.print(secs);
      Serial.println(" < 120 = WARN");
      STATE = WARN;
    }
    break;
  case WARN:
    if (secs < 1)
    {
      Serial.print(secs);
      Serial.println(" < 1 = OFF_DELAYED");
      STATE = OFF_DELAYED;
      switchOffAt = millis() + OFF_DELAY_MS; // Add extra time
    }
    break;
  case OFF_DELAYED:
    if (switchOffAt - millis() < 100)
    {
      switchOff();
    }
  }

  if (lastState != STATE)
  {
    Serial.print("STATE has changed ");
    Serial.println(STATE);
  }

  // Display status
  lastUpdate = millis();
  switch (STATE)
  {
  case OFF:
    if (lastState != STATE)
    {
      displayIntro(&obd);
    }
    break;
  case ON:
    displayOn(&obd, secs);
    break;
  case WARN:
    displayWarn(&obd, secs);
    break;
  case OFF_DELAYED:
    displayOffDelay(&obd, secs);
  }

  if (millis() - lastUpdate > 1000)
  {
    lastUpdate = millis();
    switch (STATE)
    {
    case OFF:
      Serial.println("OFF");
      break;
    case ON:
      Serial.print("ON: ");
      Serial.print(secs, DEC);
      Serial.println(" seconds remaining");
      break;
    case WARN:
      Serial.print("WARN: ");
      Serial.print(secs, DEC);
      Serial.println(" seconds remaining");
      break;
    case OFF_DELAYED:
      Serial.print("OFF Delayed: ");
      Serial.print(secs, DEC);
      Serial.println(" seconds remaining");
    }
  }
}
