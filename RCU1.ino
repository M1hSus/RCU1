////// MAIN FILE //////

/*

  This is the firmware code for DIY RadiC-U1 walkie-talkies.
  You can modify it for good purposes :)

  MihSus Projects (2020 - 2025)
  
*/

#include <GyverPower.h>
#include <powerConstants.h>

#include <EEPROM.h>

#include <LiquidCrystal.h>

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define zoomerPin A1
#define brPin 10
#define LEDPin 2

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

RF24 radio(A3, A2);

//////// VARIABLES ////////

const byte address[][6] = { "1Node", "2Node", "3Node", "4Node", "5Node", "6Node" };

unsigned long timerBrightness;

int MODE = "init";
bool is_have_signal = false;
byte BAT = 3;
bool is_lowPowerMode_enabled = false;
bool is_blink_message_enabled = true;
bool is_blink_LED_enabled = true;

bool is_sound_enabled;  // EEPROM[0]
byte channel;           // EEPROM[1]
byte brDisplay;         // EEPROM[2]
byte ring;              // EEPROM[3]

bool is_have_message;
byte ReceivedMessage[32];
byte SentMessage[32];

//////// SYMBOLS ////////

char soundOn[] = {
  0b00000,
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b00100,
  0b00000
};

char soundOff[] = {
  0b00000,
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b00000,
  0b00000
};

char noSignal[]{
  0b11101,
  0b10111,
  0b10000,
  0b11111,
  0b10000,
  0b01010,
  0b00100,
  0b01010
};

char haveSignal[]{
  0b11111,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b00100,
  0b01110,
  0b00000,
};

char play[]{
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01100,
  0b01000,
  0b00000,
  0b00000
};

char maxBAT[]{
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
};

char middleBAT[]{
  0b00100,
  0b01110,
  0b01010,
  0b01010,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
};

char lowBAT[]{
  0b01000,
  0b11101,
  0b10101,
  0b10101,
  0b10100,
  0b10101,
  0b11100,
  0b00000,
};
//////// MONOPHONY ////////

void mp1(void) {
  lcd.setCursor(0, 1);
  lcd.write(char(4));
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 493, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 220, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 440, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 391, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 233, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 369, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 233, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 493, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 220, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 440, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 391, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 233, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 369, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 233, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 225.0);
  delay(250.0);
  tone(zoomerPin, 184, 75.0);
  delay(83.3333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 225.0);
  delay(250.0);
  tone(zoomerPin, 184, 75.0);
  delay(83.3333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 246, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 369, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 146, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 195, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 246, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 369, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 184, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 110, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 246, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 97, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 146, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 195, 150.0);
  delay(166.666666667);
  tone(zoomerPin, 123, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 195, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 92, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 293, 300.0);
  delay(333.333333333);
  tone(zoomerPin, 277, 300.0);
  timerBrightness = millis();
}

//////// CODE ////////

void setup() {
  power.hardwareDisable(PWR_I2C | PWR_USB | PWR_UART0);
  power.setSleepMode(IDLE_SLEEP);
  power.setSystemPrescaler(PRESCALER_2);

  lcd.begin(16, 2);
  lcd.createChar(0, soundOn);
  lcd.createChar(1, soundOff);
  lcd.createChar(2, noSignal);
  lcd.createChar(3, haveSignal);
  lcd.createChar(4, play);
  lcd.createChar(5, maxBAT);
  lcd.createChar(6, middleBAT);
  lcd.createChar(7, lowBAT);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("Ra");
  delay(100);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Radi");
  delay(100);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("RadiC-");
  delay(100);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("RadiC-U1");
  delay(500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("RadiC-U1");
  lcd.setCursor(0, 1);
  lcd.print("[              ]");
  lcd.setCursor(1, 1);
  lcd.print("====");
  delay(500);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);

  if (EEPROM[0] == 255) EEPROM.update(0, 1);
  if (EEPROM[1] == 255) EEPROM.update(1, 1);
  if (EEPROM[2] == 255) EEPROM.update(2, 3);
  if (EEPROM[3] == 255) EEPROM.update(3, 1);
  if (EEPROM[4] == 255) EEPROM.update(4, 1);
  if (EEPROM[5] == 255) EEPROM.update(5, 1);

  EEPROM.get(0, is_sound_enabled);
  EEPROM.get(1, channel);
  EEPROM.get(2, brDisplay);
  EEPROM.get(3, ring);
  EEPROM.get(4, is_blink_message_enabled);
  EEPROM.get(5, is_blink_LED_enabled);
  delay(500);
  lcd.print("=====");

  analogWrite(brPin, brDisplay * 10);

  if (radio.begin()) is_have_signal = true;  // активировать модуль
  radio.setPayloadSize(32);                  // размер пакета, в байтах
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[0]);
  radio.setChannel(channel * 20);   // выбираем канал (в котором нет шумов!)
  radio.setPALevel(RF24_PA_MAX);    // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS);  // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.setAutoAck(1);              // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(15, 10);         // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();         // разрешить отсылку данных в ответ на входящий сигнал
  radio.startListening();
  radio.powerUp();
  delay(500);
  lcd.print("=====");
  if (is_sound_enabled) {
    tone(zoomerPin, 1046, 100);
    delay(450);
    tone(zoomerPin, 1976, 100);
    delay(600);
    tone(zoomerPin, 1568, 150);
    delay(250);
    tone(zoomerPin, 78, 600);
  }
  delay(250);
  lcd.clear();
  MODE = "lobby";
  timerBrightness = millis();
}



void loop() {
  if (radio.available() && is_have_signal)
    if (MODE != "distance_test") receiving();

  static unsigned long timer150ms;
  static int tempA5;

  static unsigned long timerLED;

  if (is_blink_LED_enabled) {
    if (millis() - timerLED >= (!is_lowPowerMode_enabled ? 10000 : 15000)) {
      timerLED = millis();
      digitalWrite(LEDPin, HIGH);
    } else if (millis() - timerLED >= 5) digitalWrite(LEDPin, LOW);
  }

  if ((analogRead(5) - tempA5) >= 1) tempA5 = analogRead(5);
  if (tempA5 <= 685) BAT = 3;
  else if (tempA5 <= 700) BAT = 2;
  else if (tempA5 > 701) BAT = 1;
  
  if ((millis() - timerBrightness >= (!is_lowPowerMode_enabled ? 10000 : 5000))
      & (millis() - timerBrightness < (!is_lowPowerMode_enabled ? 15000 : 10000))) {
    analogWrite(brPin, 5);
  }
  if (button() > 0) {
    timerBrightness = millis();
    analogWrite(brPin, brDisplay * 10);
    lcd.display();
  }
  if (millis() - timerBrightness >= (!is_lowPowerMode_enabled ? 15000 : 10000) && MODE != "sleep") {
    analogWrite(brPin, 0);
    lcd.noDisplay();
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Have a message");
    MODE = "sleep";
  }

  static byte select;

  if (MODE == "sleep") {
    static unsigned long timerSleep;
    power.sleep(SLEEP_FOREVER);
    if (button() >= 1) {
      while (button() != 0) {}
      power.wakeUp();
      timerBrightness = millis();
      analogWrite(brPin, brDisplay * 10);
      lcd.display();
      lcd.clear();
      lcd.noCursor();
      MODE = "lobby";
    }
    if (is_have_message && !is_lowPowerMode_enabled && is_blink_message_enabled && (millis() - timerSleep >= 5000)) {
      timerSleep = millis();
      lcd.display();
      analogWrite(brPin, 2);
      delay(30);
      analogWrite(brPin, 4);
      delay(30);
      analogWrite(brPin, 5);
      delay(60);
      analogWrite(brPin, 4);
      delay(30);
      analogWrite(brPin, 2);
      delay(30);
      analogWrite(brPin, 0);
      delay(90);

      analogWrite(brPin, 2);
      delay(30);
      analogWrite(brPin, 4);
      delay(30);
      analogWrite(brPin, 5);
      delay(60);
      analogWrite(brPin, 4);
      delay(30);
      analogWrite(brPin, 2);
      delay(30);
      analogWrite(brPin, 0);
      lcd.noCursor();
    }
  }



  if (MODE == "lobby") {
    static bool is_labelView;
    static unsigned long timerLobby;

    if (millis() - timerLobby >= 3000) {
      timerLobby = millis();
      lcd.clear();
      if (!is_have_signal) lcd.write(char(2));
      else lcd.write(char(3));
      lcd.setCursor(2, 0);
      lcd.print("CH");
      lcd.print(channel);
      lcd.setCursor(6, 0);
      if (is_sound_enabled) lcd.write(char(0));
      else lcd.write(char(1));

      lcd.setCursor(14, 0);
      if (is_lowPowerMode_enabled) lcd.print("L");

      if (is_labelView) {
        lcd.setCursor(4, 1);
        lcd.print("RadiC-U1");
      } else {
        lcd.setCursor(1, 1);
        if (!is_have_message) lcd.print("No new message");
        else lcd.print("Have a message");
      }
      is_labelView = !is_labelView;

      lcd.setCursor(15, 0);
      if (BAT == 3) lcd.write(5);
      else if (BAT == 2) lcd.write(6);
      else if (BAT == 1) lcd.write(7);
    }
    if (button() == 1) {
      while (button() != 0) {}
      select = 1;
      MODE = "menu";
    }
  }



  if (MODE == "menu") {
    if (button() == 1) {
      while (button() != 0) {}
      if (select == 1) MODE = "sender";
      if (select == 2) {
        MODE = "senderqm";
        select = 1;
      }
      if (select == 3) MODE = "reader";
      if (select == 4) {
        is_sound_enabled = !is_sound_enabled;
        EEPROM.update(0, bool(is_sound_enabled));
      }
      if (select == 5) {
        is_lowPowerMode_enabled = !is_lowPowerMode_enabled;
        if (is_lowPowerMode_enabled) radio.setPALevel(RF24_PA_LOW);
        else radio.setPALevel(RF24_PA_MAX);
      }
      if (select == 6) {
        select = 1;
        MODE = "monophonyPlayer";
      }
      if (select == 7) {
        lcd.clear();
        MODE = "distance_test";
      }
      if (select == 8) {
        select = 1;
        MODE = "settings";
      }
      if (select == 9) {
        MODE = "aboutFirmware";
      }
    }
    if (button() == 2) {
      MODE = "lobby";
      lcd.clear();
    }
    if (button() == 3 && select != 1) {
      while (button() != 0) {};
      select--;
    }
    if (button() == 4 && select != 9) {
      while (button() != 0) {};
      select++;
    }

    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(4, 0);
      lcd.print("MENU");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.print("/9");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      switch (select) {
        case 1: lcd.print("Sender"); break;
        case 2: lcd.print("Sender Q-M"); break;
        case 3: lcd.print("Read message"); break;
        case 4:
          lcd.print("Sound:");
          if (is_sound_enabled) {
            lcd.setCursor(14, 1);
            lcd.print("ON");
          } else {
            lcd.setCursor(13, 1);
            lcd.print("OFF");
          } break;
        case 5:
          lcd.print("PowerSave:");
          if (is_lowPowerMode_enabled) {
            lcd.setCursor(14, 1);
            lcd.print("ON");
          } else {
            lcd.setCursor(13, 1);
            lcd.print("OFF");
          } break;
        case 6: lcd.print("Monophony"); break;
        case 7: lcd.print("Distance test"); break;
        case 8: lcd.print("Settings"); break;
        case 9: lcd.print("About firmware"); break;
      }
    }
  }



  if (MODE == "sender") {
    static byte senderCursorPos = 0;
    static unsigned long buttonDelay;

    if (button() == 1) {
      while (button() != 0) {}
      MODE = "TX";
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(0, 0);
      if (is_blink_LED_enabled) digitalWrite(LEDPin, HIGH);
      lcd.print("Sending message");
      lcd.setCursor(0, 1);
      lcd.print("[=======       ]");
      lcd.setCursor(1, 1);
      delay(250);
      lcd.print("=======");
      radio.stopListening();
      if (radio.write(&SentMessage, 32, true)) {
        lcd.clear();
        lcd.setCursor(6, 0);
        lcd.print("Sent!");
      } else {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Sending");
        lcd.setCursor(5, 1);
        lcd.print("Error!");
      }
      digitalWrite(LEDPin, LOW);
      delay(3000);
      radio.startListening();
      lcd.cursor();
      MODE = "sender";
    }
    if (button() == 2) {
      while (button() != 0) {}
      select = 1;
      MODE = "menu";
    }
    if (button() == 3) {
      if (millis() - buttonDelay >= 200) {
        buttonDelay = millis();
        SentMessage[senderCursorPos]--;
      }
      if (SentMessage[senderCursorPos] == 255) {
        SentMessage[senderCursorPos] = 40;
      }
    }
    if (button() == 4) {
      if (millis() - buttonDelay >= 200) {
        buttonDelay = millis();
        SentMessage[senderCursorPos]++;
      }
      if (SentMessage[senderCursorPos] == 40) {
        SentMessage[senderCursorPos] = 0;
      }
    }
    if (button() == 5) {
      while (button() != 0) {}
      senderCursorPos++;
      if (senderCursorPos == 33) senderCursorPos = 0;
    }
    if (millis() - timer150ms > 100) {
      timer150ms = millis();
      lcd.clear();
      byte tempSender = 0;
      for (tempSender; tempSender <= sizeof(SentMessage); tempSender++) {
        if (tempSender >= 16) lcd.setCursor(tempSender - 16, 1);
        switch (SentMessage[tempSender]) {
          case 0: lcd.print(" "); break;
          case 1: lcd.print("A"); break;
          case 2: lcd.print("B"); break;
          case 3: lcd.print("C"); break;
          case 4: lcd.print("D"); break;
          case 5: lcd.print("E"); break;
          case 6: lcd.print("F"); break;
          case 7: lcd.print("G"); break;
          case 8: lcd.print("H"); break;
          case 9: lcd.print("I"); break;
          case 10: lcd.print("J"); break;
          case 11: lcd.print("K"); break;
          case 12: lcd.print("L"); break;
          case 13: lcd.print("M"); break;
          case 14: lcd.print("N"); break;
          case 15: lcd.print("O"); break;
          case 16: lcd.print("P"); break;
          case 17: lcd.print("Q"); break;
          case 18: lcd.print("R"); break;
          case 19: lcd.print("S"); break;
          case 20: lcd.print("T"); break;
          case 21: lcd.print("U"); break;
          case 22: lcd.print("V"); break;
          case 23: lcd.print("W"); break;
          case 24: lcd.print("X"); break;
          case 25: lcd.print("Y"); break;
          case 26: lcd.print("Z"); break;
          case 27: lcd.print("."); break;
          case 28: lcd.print(","); break;
          case 29: lcd.print("?"); break;
          case 30: lcd.print("!"); break;
          case 31: lcd.print("1"); break;
          case 32: lcd.print("2"); break;
          case 33: lcd.print("3"); break;
          case 34: lcd.print("4"); break;
          case 35: lcd.print("5"); break;
          case 36: lcd.print("6"); break;
          case 37: lcd.print("7"); break;
          case 38: lcd.print("8"); break;
          case 39: lcd.print("9"); break;
          case 40: lcd.print("0"); break;
        }
      }
      lcd.setCursor(senderCursorPos, 0);
      if (senderCursorPos >= 16) lcd.setCursor(senderCursorPos - 16, 1);
      lcd.cursor();
    }
  }



  if (MODE == "senderqm") {
    if (button() == 1) {
      while (button() != 0) {}
      memset(SentMessage, 0, 32);
      switch (select) {
        case 1:
          // HELLO! HOW ARE YOU?
          SentMessage[0] = 8;
          SentMessage[1] = 5;
          SentMessage[2] = 12;
          SentMessage[3] = 12;
          SentMessage[4] = 15;
          SentMessage[5] = 30;
          SentMessage[6] = 0;
          SentMessage[7] = 8;
          SentMessage[8] = 15;
          SentMessage[9] = 23;
          SentMessage[10] = 0;
          SentMessage[11] = 1;
          SentMessage[12] = 18;
          SentMessage[13] = 5;
          SentMessage[14] = 0;
          SentMessage[15] = 25;
          SentMessage[16] = 15;
          SentMessage[17] = 21;
          SentMessage[18] = 29;
          break;
        case 2:
          // WHERE ARE YOU?
          SentMessage[0] = 23;
          SentMessage[1] = 8;
          SentMessage[2] = 5;
          SentMessage[3] = 18;
          SentMessage[4] = 5;
          SentMessage[5] = 0;
          SentMessage[6] = 1;
          SentMessage[7] = 18;
          SentMessage[8] = 5;
          SentMessage[9] = 0;
          SentMessage[10] = 25;
          SentMessage[11] = 15;
          SentMessage[12] = 21;
          SentMessage[13] = 29;
          break;
        case 3:
          // I AM FINE
          SentMessage[0] = 9;
          SentMessage[1] = 0;
          SentMessage[2] = 1;
          SentMessage[3] = 13;
          SentMessage[4] = 0;
          SentMessage[5] = 6;
          SentMessage[6] = 9;
          SentMessage[7] = 14;
          SentMessage[8] = 5;
          break;
        case 4:
          // I AM COMING TO YOU
          SentMessage[0] = 9;
          SentMessage[1] = 0;
          SentMessage[2] = 1;
          SentMessage[3] = 13;
          SentMessage[4] = 0;
          SentMessage[5] = 3;
          SentMessage[6] = 15;
          SentMessage[7] = 13;
          SentMessage[8] = 9;
          SentMessage[9] = 14;
          SentMessage[10] = 7;
          SentMessage[11] = 0;
          SentMessage[12] = 20;
          SentMessage[13] = 15;
          SentMessage[14] = 0;
          SentMessage[15] = 25;
          SentMessage[16] = 15;
          SentMessage[17] = 21;
          break;
        case 5:
          // YES!
          SentMessage[0] = 25;
          SentMessage[1] = 5;
          SentMessage[2] = 19;
          SentMessage[3] = 30;
          break;
        case 6:
          // NO!
          SentMessage[0] = 14;
          SentMessage[1] = 15;
          SentMessage[2] = 30;
          break;
        case 7:
          // TELL ME ABOUT IT
          SentMessage[0] = 20;
          SentMessage[1] = 5;
          SentMessage[2] = 12;
          SentMessage[3] = 12;
          SentMessage[4] = 0;
          SentMessage[5] = 13;
          SentMessage[6] = 5;
          SentMessage[7] = 0;
          SentMessage[8] = 1;
          SentMessage[9] = 2;
          SentMessage[10] = 15;
          SentMessage[11] = 21;
          SentMessage[12] = 20;
          SentMessage[13] = 0;
          SentMessage[14] = 9;
          SentMessage[15] = 20;
          break;
      }
      MODE = "sender";
    }
    if (button() == 2) {
      while (button() != 0) {}
      select = 2;
      MODE = "menu";
    }
    if (button() == 3 && select != 1) {
      while (button() != 0) {}
      select--;
    }
    if (button() == 4 && select != 7) {
      while (button() != 0) {}
      select++;
    }
    if (millis() - timer150ms > 100) {
      timer150ms = millis();
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("SENDER Q-M");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.print("/7");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      switch (select) {
        case 1:
          lcd.print("HELLO! HOW ARE YOU?");
          break;
        case 2:
          lcd.print("WHERE ARE YOU?");
          break;
        case 3:
          lcd.print("I AM FINE");
          break;
        case 4:
          lcd.print("I AM COMING TO YOU");
          break;
        case 5:
          lcd.print("YES!");
          break;
        case 6:
          lcd.print("NO!");
          break;
        case 7:
          lcd.print("TELL ME ABOUT IT");
          break;
      }
    }
  }


  if (MODE == "distance_test") {
    static byte step = 0;
    static bool tx_rx;
    static bool signal = true;
    static byte Scroll = 0;
    static const byte testMessage[] = { 1, 1, 1, 1 };
    static unsigned long timer200ms;
    if (button() == 1) {
      while (button() != 0) {}
      if (step == 0) step = 1;
    }
    if (button() == 2) {
      while (button() != 0) {}
      step = 0;
      Scroll = 0;
      memset(ReceivedMessage, 0, 32);
      lcd.clear();
      MODE = "menu";
    }
    if (button() == 3) {
      while (button() != 0) {}
      if (step == 1) {
        tx_rx = false;
        step = 2;
        radio.stopListening();
      }
    }
    if (button() == 4) {
      while (button() != 0) {}
      if (step == 1) {
        tx_rx = true;
        step = 2;
        radio.startListening();
      }
    }
    if (millis() - timer150ms >= 1000) {
      timer150ms = millis();
      if (step == 0) {
        lcd.clear();
        if (Scroll == 0) lcd.print("Select this mode");
        if (Scroll == 1) lcd.print("on another RadiC");
        if (Scroll == 2) lcd.print("and click OK");
        Scroll++;
        if (Scroll == 3) Scroll = 0;
      }
      if (step == 1) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Select mode:");
        lcd.setCursor(1, 1);
        lcd.print("UP=TX, DOWN=RX");
      }

      if (step == 2) {
        if (tx_rx == false) {
          radio.write(&testMessage, sizeof(testMessage));
          lcd.setCursor(1, 0);
          lcd.print(")))");
        }
      }
    }
    if (millis() - timer200ms >= 200) {
      timer200ms = millis();
      timerBrightness = millis();
      if (step == 2) {
        lcd.clear();
        lcd.write(char(3));
        lcd.setCursor(14, 0);
        if (tx_rx == false) {
          lcd.print("TX");
        } else {
          lcd.print("RX");
        }
      }
    }
    if (radio.available()) {
      if (step == 2) {
        radio.read(&ReceivedMessage, sizeof(ReceivedMessage));
        if (is_sound_enabled) tone(zoomerPin, 2000, 200);
        lcd.setCursor(1, 0);
        lcd.print("(((");
        lcd.setCursor(4, 1);
        lcd.print("SIGNAL!");
      }
    }
  }



  if (MODE == "settings") {
    if (button() == 1) {
      while (button() != 0) {}
      switch (select) {
        case 1:
          ring++;
          if (ring == 6) ring = 1;
          if (is_sound_enabled) {
            if (ring == 1) {
              tone(zoomerPin, 1046, 75);
              delay(75);
              tone(zoomerPin, 2000, 350);
            }
            if (ring == 2) {
              tone(zoomerPin, 3250, 175);
              delay(250);
              tone(zoomerPin, 3250, 175);
            }
            if (ring == 3) {
              tone(zoomerPin, 2750, 75);
              delay(100);
              tone(zoomerPin, 2750, 75);
              delay(100);
              tone(zoomerPin, 2750, 75);
              delay(100);
              tone(zoomerPin, 2750, 75);
            }
            if (ring == 4) {
              tone(zoomerPin, 2500, 100);
              delay(100);
              tone(zoomerPin, 3000, 100);
              delay(100);
              tone(zoomerPin, 2000, 100);
              delay(100);
              tone(zoomerPin, 2500, 100);
            }
            if (ring == 5) {
              tone(zoomerPin, 2500, 75);
              delay(75);
              tone(zoomerPin, 3000, 75);
              delay(75);
              tone(zoomerPin, 2000, 75);

              delay(75);
              tone(zoomerPin, 3000, 75);
              delay(75);
              tone(zoomerPin, 3500, 75);
              delay(75);
              tone(zoomerPin, 2500, 75);

              delay(75);
              tone(zoomerPin, 3500, 75);
              delay(75);
              tone(zoomerPin, 4000, 75);
              delay(75);
              tone(zoomerPin, 3000, 75);
            }
          }
          break;
        case 2:
          channel++;
          if (channel == 7) channel = 1;
          radio.setChannel(channel * 20);
          break;
        case 3:
          brDisplay++;
          if (brDisplay == 10) brDisplay = 1;
          analogWrite(brPin, brDisplay * 10);
          break;
        case 4:
          is_blink_message_enabled = !is_blink_message_enabled;
          break;
        case 5:
          is_blink_LED_enabled = !is_blink_LED_enabled;
          break;
      }
    }
    if (button() == 2) {
      while (button() != 0) {}
      EEPROM.update(1, channel);
      EEPROM.update(2, brDisplay);
      EEPROM.update(3, ring);
      EEPROM.update(4, bool(is_blink_message_enabled));
      EEPROM.update(5, bool(is_blink_LED_enabled));
      select = 5;
      MODE = "menu";
    }
    if (button() == 3) {
      while (button() != 0) {}
      if (select != 1) select--;
    }
    if (button() == 4) {
      while (button() != 0) {}
      if (select != 5) select++;
    }
    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("SETTINGS");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.print("/5");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      if (select == 1) {
        lcd.print("RingSound:");
        lcd.setCursor(15, 1);
        lcd.print(ring);
      }
      if (select == 2) {
        lcd.print("Channel:");
        lcd.setCursor(15, 1);
        lcd.print(channel);
      }
      if (select == 3) {
        lcd.print("Brightness:");
        lcd.setCursor(13, 1);
        lcd.print(brDisplay * 10);
        lcd.print("%");
      }
      if (select == 4) {
        lcd.print("Blink Disp:");
        lcd.setCursor(13, 1);
        lcd.print(is_blink_message_enabled ? "ON" : "OFF");
      }
      if (select == 5) {
        lcd.print("Blink LED:");
        lcd.setCursor(13, 1);
        lcd.print(is_blink_LED_enabled ? "ON" : "OFF");
      }
    }
  }



  if (MODE == "aboutFirmware") {
    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.print("OS:");
      lcd.setCursor(7, 0);
      lcd.print("RCU1 v1.3");
      lcd.setCursor(0, 1);
      lcd.print("By:");
      lcd.setCursor(10, 1);
      lcd.print("MihSus");
      if (button() == 2) {
        while (button() != 0) {}
        MODE = "menu";
      }
    }
  }



  if (MODE == "monophonyPlayer") {
    if (button() == 1) {
      while (button() != 0) {}
      if (is_sound_enabled) {
        switch (select) {
          case 1:
            mp1();
            break;
        }
      }
    }
    if (button() == 2) {
      while (button() != 0) {}
      select = 6;
      MODE = "menu";
    }
    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Monophony");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.setCursor(14, 0);
      lcd.print("/1");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      switch (select) {
        case 1:
          lcd.print("juki_batareyka");
          break;
      }
    }
  }



  if (MODE == "reader") {
    if (button() == 2) {
      while (button() != 0) {}
      is_have_message = false;
      MODE = "menu";
    }
    if (millis() - timer150ms > 100) {
      timer150ms = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      byte tempReader = 0;
      if (is_have_message) {
        for (tempReader; tempReader <= sizeof(ReceivedMessage); tempReader++) {
          if (tempReader >= 16) lcd.setCursor((tempReader - 16), 1);
          switch (ReceivedMessage[tempReader]) {
            case 0: lcd.print(" "); break;
            case 1: lcd.print("A"); break;
            case 2: lcd.print("B"); break;
            case 3: lcd.print("C"); break;
            case 4: lcd.print("D"); break;
            case 5: lcd.print("E"); break;
            case 6: lcd.print("F"); break;
            case 7: lcd.print("G"); break;
            case 8: lcd.print("H"); break;
            case 9: lcd.print("I"); break;
            case 10: lcd.print("J"); break;
            case 11: lcd.print("K"); break;
            case 12: lcd.print("L"); break;
            case 13: lcd.print("M"); break;
            case 14: lcd.print("N"); break;
            case 15: lcd.print("O"); break;
            case 16: lcd.print("P"); break;
            case 17: lcd.print("Q"); break;
            case 18: lcd.print("R"); break;
            case 19: lcd.print("S"); break;
            case 20: lcd.print("T"); break;
            case 21: lcd.print("U"); break;
            case 22: lcd.print("V"); break;
            case 23: lcd.print("W"); break;
            case 24: lcd.print("X"); break;
            case 25: lcd.print("Y"); break;
            case 26: lcd.print("Z"); break;
            case 27: lcd.print("."); break;
            case 28: lcd.print(","); break;
            case 29: lcd.print("?"); break;
            case 30: lcd.print("!"); break;
            case 31: lcd.print("1"); break;
            case 32: lcd.print("2"); break;
            case 33: lcd.print("3"); break;
            case 34: lcd.print("4"); break;
            case 35: lcd.print("5"); break;
            case 36: lcd.print("6"); break;
            case 37: lcd.print("7"); break;
            case 38: lcd.print("8"); break;
            case 39: lcd.print("9"); break;
            case 40: lcd.print("0"); break;
          }
        }
      } else {
        lcd.setCursor(4, 0);
        lcd.print("No have");
        lcd.setCursor(4, 1);
        lcd.print("Message!");
      }
    }
  }
}
//////// FUNCTIONS ////////

//////// Receiving Message ////////

void receiving(void) {
  power.wakeUp();
  timerBrightness = millis();
  MODE = "RX";
  lcd.display();
  analogWrite(brPin, brDisplay * 10);
  digitalWrite(LEDPin, HIGH);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Receiving");
  lcd.setCursor(3, 1);
  lcd.print("message...");
  radio.read(&ReceivedMessage, sizeof(ReceivedMessage));
  if (is_sound_enabled) {
    if (ring == 1) {
      tone(zoomerPin, 1046, 75);
      delay(75);
      tone(zoomerPin, 2000, 350);
    }
    if (ring == 2) {
      tone(zoomerPin, 3250, 175);
      delay(250);
      tone(zoomerPin, 3250, 175);
    }
    if (ring == 3) {
      tone(zoomerPin, 2750, 75);
      delay(100);
      tone(zoomerPin, 2750, 75);
      delay(100);
      tone(zoomerPin, 2750, 75);
      delay(100);
      tone(zoomerPin, 2750, 75);
    }
    if (ring == 4) {
      tone(zoomerPin, 2500, 100);
      delay(100);
      tone(zoomerPin, 3000, 100);
      delay(100);
      tone(zoomerPin, 2000, 100);
      delay(100);
      tone(zoomerPin, 2500, 100);
    }
    if (ring == 5) {
      tone(zoomerPin, 2500, 75);
      delay(75);
      tone(zoomerPin, 3000, 75);
      delay(75);
      tone(zoomerPin, 2000, 75);

      delay(75);
      tone(zoomerPin, 3000, 75);
      delay(75);
      tone(zoomerPin, 3500, 75);
      delay(75);
      tone(zoomerPin, 2500, 75);

      delay(75);
      tone(zoomerPin, 3500, 75);
      delay(75);
      tone(zoomerPin, 4000, 75);
      delay(75);
      tone(zoomerPin, 3000, 75);
    }
  }
  delay(1700);
  lcd.clear();
  lcd.setCursor(0, 0);
  byte tempGetter = 0;
  for (tempGetter; tempGetter <= sizeof(ReceivedMessage); tempGetter++) {
    if (is_blink_LED_enabled) digitalWrite(LEDPin, HIGH);
    if (ReceivedMessage[tempGetter] != 0) {
      if (is_sound_enabled) tone(zoomerPin, 2000, 75);
    }
    delay(75);
    if (is_blink_LED_enabled) digitalWrite(LEDPin, LOW);
    delay(75);
    lcd.blink();
    if (tempGetter >= 16) lcd.setCursor((tempGetter - 16), 1);
    switch (ReceivedMessage[tempGetter]) {
      case 0: lcd.print(" "); break;
      case 1: lcd.print("A"); break;
      case 2: lcd.print("B"); break;
      case 3: lcd.print("C"); break;
      case 4: lcd.print("D"); break;
      case 5: lcd.print("E"); break;
      case 6: lcd.print("F"); break;
      case 7: lcd.print("G"); break;
      case 8: lcd.print("H"); break;
      case 9: lcd.print("I"); break;
      case 10: lcd.print("J"); break;
      case 11: lcd.print("K"); break;
      case 12: lcd.print("L"); break;
      case 13: lcd.print("M"); break;
      case 14: lcd.print("N"); break;
      case 15: lcd.print("O"); break;
      case 16: lcd.print("P"); break;
      case 17: lcd.print("Q"); break;
      case 18: lcd.print("R"); break;
      case 19: lcd.print("S"); break;
      case 20: lcd.print("T"); break;
      case 21: lcd.print("U"); break;
      case 22: lcd.print("V"); break;
      case 23: lcd.print("W"); break;
      case 24: lcd.print("X"); break;
      case 25: lcd.print("Y"); break;
      case 26: lcd.print("Z"); break;
      case 27: lcd.print("."); break;
      case 28: lcd.print(","); break;
      case 29: lcd.print("?"); break;
      case 30: lcd.print("!"); break;
      case 31: lcd.print("1"); break;
      case 32: lcd.print("2"); break;
      case 33: lcd.print("3"); break;
      case 34: lcd.print("4"); break;
      case 35: lcd.print("5"); break;
      case 36: lcd.print("6"); break;
      case 37: lcd.print("7"); break;
      case 38: lcd.print("8"); break;
      case 39: lcd.print("9"); break;
      case 40: lcd.print("0"); break;
    }
  }
  digitalWrite(LEDPin, LOW);
  lcd.noBlink();
  delay(3000);
  MODE = "lobby";
  is_have_message = true;
}



byte button(void) {
  byte val = map(analogRead(A0), 0, 1023, 0, 10);
  switch (val) {
    case 0:
      return 5;
      break;
    case 1:
      return 3;
      break;
    case 3:
      return 4;
      break;
    case 4:
      return 2;
      break;
    case 7:
      return 1;
      break;
    default:
      return 0;
      break;
  }
}