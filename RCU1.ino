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

#include "button.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

RF24 radio(A3, A2);

//////// VARIABLES ////////

byte address[][6] = { "1Node", "2Node", "3Node", "4Node", "5Node", "6Node" };
const int zoomerPin = A1;
const int brPin = 10;

unsigned long timerLobby;
bool is_labelView;
unsigned long timerBrightness;
unsigned long timer150ms;
byte senderCursorPos = 0;
byte tempSender;

int MODE = "init";
bool is_have_signal = false;
byte select;

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
  0b00000,
  0b00100,
  0b00000,
  0b01010,
  0b00100,
  0b10001,
  0b01110,
  0b00000
};

char play[] {
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01100,
  0b01000,
  0b00000,
  0b00000
};

char lock[] {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b11011,
  0b11111,
  0b00000
};
//////// MONOPHONY ////////

void mp1(void) {
  lcd.setCursor(0,1);
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
  lcd.begin(16, 2);

  lcd.createChar(0, soundOn);
  lcd.createChar(1, soundOff);
  lcd.createChar(2, noSignal);
  lcd.createChar(3, haveSignal);
  lcd.createChar(4, play);
  lcd.createChar(5, lock);
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
  lcd.setCursor(3, 1);
  lcd.print("Starting.");
  delay(500);
  digitalWrite(13, LOW);

  if (EEPROM[0] == 255) {
    EEPROM.update(0, 1);
  }
  if (EEPROM[1] == 255) {
    EEPROM.update(1, 1);
  }
  if (EEPROM[2] == 255) {
    EEPROM.update(2, 3);
  }
  if (EEPROM[3] == 255) {
    EEPROM.update(3, 1);
  }
  EEPROM.get(0, is_sound_enabled);
  EEPROM.get(1, channel);
  EEPROM.get(2, brDisplay);
  EEPROM.get(3, ring);
  delay(500);
  lcd.print(".");

  analogWrite(brPin, brDisplay * 10);

  if (radio.begin()) is_have_signal = true;  // активировать модуль
  radio.setPayloadSize(32);                  // размер пакета, в байтах
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[0]);
  radio.setChannel(channel * 20);   // выбираем канал (в котором нет шумов!)
  radio.setPALevel(RF24_PA_MAX);    // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS);  // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.setAutoAck(1);              // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(5, 10);          // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();         // разрешить отсылку данных в ответ на входящий сигнал
  radio.startListening();
  radio.powerUp();
  delay(500);
  lcd.print(".");
  if (is_sound_enabled) {
    tone(zoomerPin, 1046, 100);
    delay(450);
    tone(zoomerPin, 1976, 100);
    delay(600);
    tone(zoomerPin, 1568, 150);
    delay(250);
    tone(zoomerPin, 78, 600);
  }
  lcd.clear();
  select = 1;
  MODE = "lobby";
  timerBrightness = millis();
}

void loop() {
  if (radio.available() && is_have_signal) receiving();

  if ((millis() - timerBrightness >= 10000) & (millis() - timerBrightness < 15000)) {
    analogWrite(brPin, 5);
  }
  if (button() > 0) {
    timerBrightness = millis();
    analogWrite(brPin, brDisplay * 10);
    lcd.display();
  }
  if (millis() - timerBrightness >= 15000) {
    analogWrite(brPin, 0);
    lcd.noDisplay();
    MODE = "sleep";
  }



  if (MODE == "sleep") {
    power.setSleepMode(STANDBY_SLEEP); // режим сна (по умолчанию POWERDOWN_SLEEP)
    if (button() >= 1) {
      while (button() != 0) {}
      power.wakeUp();
      timerBrightness = millis();
      analogWrite(brPin, brDisplay * 10);
      lcd.display();
      lcd.noCursor();
      MODE = "lobby";
    }
  }



  if (MODE == "lobby") {
    if (millis() - timerLobby >= 3000) {
      timerLobby = millis();
      lcd.clear();
      if (!is_have_signal) lcd.write(char(2));
      else lcd.write(char(3));
      lcd.setCursor(2, 0);
      lcd.print("CH");
      lcd.print(channel);
      lcd.setCursor(15, 0);
      if (is_sound_enabled) lcd.write(char(0));
      else lcd.write(char(1));

      if (is_labelView) {
        lcd.setCursor(4, 1);
        lcd.print("RadiC-U1");
      } else {
        lcd.setCursor(1, 1);
        if (!is_have_message) lcd.print("No new message");
        else lcd.print("Have a message");
      }
      is_labelView = !is_labelView;
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
      if (select == 1) {
        MODE = "sender";
      }
      if (select == 2) {
        MODE = "senderqm";
        select = 1;
      }
      if (select == 3) {
        MODE = "reader";
      }
      if (select == 4) {
        is_sound_enabled = !is_sound_enabled;
        EEPROM.update(0, bool(is_sound_enabled));
      }
      if (select == 5) {
        select = 1;
        MODE = "settings";
      }
      if (select == 6) {
        select = 1;
        MODE = "monophonyPlayer";
      }
      if (select == 7) {
        MODE = "aboutFirmware";
      }
    }
    if (button() == 2) {MODE = "lobby"; lcd.clear();}
    if (button() == 3 && select != 1) { while (button() != 0) {}; select--; }
    if (button() == 4 && select != 7) { while (button() != 0) {}; select++; }

    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(4, 0);
      lcd.print("MENU");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.print("/7");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      switch (select) {
        case 1:
          lcd.print("Sender");
          break;
        case 2:
          lcd.print("Sender Q-M");
          break;
        case 3:
          lcd.print("Read message");
          break;
        case 4:
          lcd.print("Sound:");
          if (is_sound_enabled) {
            lcd.setCursor(14, 1);
            lcd.print("ON");
          } else {
            lcd.setCursor(13, 1);
            lcd.print("OFF");
          }
          break;
        case 5:
          lcd.print("Settings");
          break;
        case 6:
          lcd.print("Monophony");
          break;
        case 7:
          lcd.print("About firware");
          break;
      }
    }
  }



  if (MODE == "sender") {
    if (button() == 1) {
      while (button() != 0) {}
      MODE = "TX";
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(5, 0);
      lcd.print("Sending");
      lcd.setCursor(2, 1);
      lcd.print("Message...");
      delay(500);
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
      while (button() != 0) {}
      SentMessage[senderCursorPos]--;
      if (SentMessage[senderCursorPos] == 255) {
        SentMessage[senderCursorPos] = 40;
      }
    }
    if (button() == 4) {
      while (button() != 0) {}
      SentMessage[senderCursorPos]++;
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
      }
    }
    if (button() == 2) {
      while (button() != 0) {}
      EEPROM.update(1, channel);
      EEPROM.update(2, brDisplay);
      EEPROM.update(3, ring);
      select = 5;
      MODE = "menu";
    }
    if (button() == 3) {
      while (button() != 0) {}
      if (select != 1) select--;
    }
    if (button() == 4) {
      while (button() != 0) {}
      if (select != 3) select++;
    }
    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SETTINGS");
      lcd.setCursor(13, 0);
      lcd.print(select);
      lcd.print("/3");
      lcd.setCursor(0, 1);
      lcd.write(165);
      lcd.setCursor(2, 1);
      if (select == 1) {
        lcd.print("RingSound:");
        lcd.setCursor(15,1);
        lcd.print(ring);
      }
      if (select == 2) {
        lcd.print("Channel:");
        lcd.setCursor(15,1);
        lcd.print(channel);
      }
      if (select == 3) {
        lcd.print("Brightness:");
        lcd.setCursor(13,1);
        lcd.print(brDisplay * 10);
        lcd.setCursor(15, 1);
        lcd.print("%");
      }
    }
  }



  if (MODE == "aboutFirmware") {
    if (millis() - timer150ms >= 150) {
      timer150ms = millis();
      delay(50);
      lcd.clear();
      lcd.print("OS:");
      lcd.setCursor(12, 0);
      lcd.print("RCU1");
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
    if (button() == 2) {while (button() != 0) {} is_have_message = false; MODE = "menu";}
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
      }
      else {
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
    if (ReceivedMessage[tempGetter] != 0) {
      if (is_sound_enabled) tone(zoomerPin, 2000, 75);
    }
    delay(150);
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
  lcd.noBlink();
  delay(5000);
  MODE = "lobby";
  is_have_message = true;
}