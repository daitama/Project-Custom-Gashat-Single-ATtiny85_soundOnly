#include <SoftwareSerial.h>

#include <avr/io.h>

#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 0

// #define LED_PIN 1

#define GASHAT_OFF       0
#define GASHAT_NAME      1
#define GAME_CLEAR       2
#define GAME_OVER        3
#define LEVEL_1          4
#define LEVEL_2          5
#define LEVEL_3          6
#define GASHAT_IN        7
#define GASHAT_OUT       8
#define DRIVER_CLOSE     9
#define CRITICAL_STRIKE 12
#define CRITICAL_READY  13
#define CRITICAL_FINISH 14
#define GENRE           15
#define BUGGLE_UP       16

#define ON  LOW
#define OFF HIGH

SoftwareSerial mySerial(1, 2); // RX, TX

// State variables
uint8_t before_button1 = OFF;
uint8_t before_button2 = OFF;
uint8_t before_button3 = OFF;

uint8_t current_button1 = OFF;
uint8_t current_button2 = OFF;
uint8_t current_button3 = OFF;

uint8_t single_mode_flag = false;
uint8_t game_clear_flag = false;
uint8_t critical_mode_flag = false;

void set_action(uint8_t action){
    byte message[] = {0x7E, 0xFF, 0x06, 0x0F, 0x00, 0x01,action, 0xEF};
    mySerial.write(message, sizeof(message));

    // digitalWrite(LED_PIN, HIGH);
    // delay(10);
}

void setup() {
    mySerial.begin(9600); // set SoftwareSerial for DFPlayerMP3
    byte message_volume[] = {0x7E, 0xFF, 0x06, 0x6, (byte)0, (byte)0, (byte)25, 0xEF};
    mySerial.write(message_volume, sizeof(message_volume));

    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(BUTTON_3_PIN, INPUT_PULLUP);

    // pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // Read the current state of the buttons
    current_button1 = digitalRead(BUTTON_1_PIN);
    current_button2 = digitalRead(BUTTON_2_PIN);
    current_button3 = digitalRead(BUTTON_3_PIN);
    
    // Compare states and determine action
    if (before_button1 == OFF && before_button2 == OFF && before_button3 == OFF) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            set_action(LEVEL_1);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            set_action(GASHAT_IN);
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            if (single_mode_flag == OFF) {
                set_action(GASHAT_NAME);
            } else {
                set_action(game_clear_flag ? GAME_CLEAR : GAME_OVER);
                game_clear_flag = !game_clear_flag;
            }
            single_mode_flag = !single_mode_flag;
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            set_action(GASHAT_IN);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            set_action(LEVEL_1);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            set_action(GASHAT_IN);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            if (critical_mode_flag == OFF) {
                set_action(CRITICAL_READY);
            } else {
                set_action(CRITICAL_STRIKE);
            }
            critical_mode_flag = !critical_mode_flag;
        }
    }if (before_button1 == ON && before_button2 == OFF && before_button3 == OFF) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            set_action(LEVEL_2);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            set_action(LEVEL_2);
        }
    }if (before_button1 == OFF && before_button2 == ON && before_button3 == OFF) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            set_action(LEVEL_3);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            set_action(BUGGLE_UP);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            set_action(LEVEL_3);
        }
    }if (before_button1 == OFF && before_button2 == OFF && before_button3 == ON) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            set_action(LEVEL_1);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            set_action(GASHAT_IN);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            if (critical_mode_flag == OFF) {
                set_action(CRITICAL_READY);
            } else {
                set_action(CRITICAL_STRIKE);
            }
            critical_mode_flag = !critical_mode_flag;
        }
    }if (before_button1 == ON && before_button2 == ON && before_button3 == OFF) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            set_action(DRIVER_CLOSE);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            set_action(DRIVER_CLOSE);
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            if (critical_mode_flag == OFF) {
                set_action(CRITICAL_READY);
            } else {
                set_action(CRITICAL_STRIKE);
            }
            critical_mode_flag = !critical_mode_flag;
        }
    }if (before_button1 == ON && before_button2 == OFF && before_button3 == ON) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            set_action(LEVEL_2);
        }
    }if (before_button1 == OFF && before_button2 == ON && before_button3 == ON) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            // No change
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            // No change
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            set_action(LEVEL_3);
        }
    }if (before_button1 == ON && before_button2 == ON && before_button3 == ON) {
        if (current_button1 == OFF && current_button2 == OFF && current_button3 == OFF) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == OFF) {
            set_action(CRITICAL_FINISH);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == OFF) {
            set_action(GENRE);
        } else if (current_button1 == OFF && current_button2 == OFF && current_button3 == ON) {
            set_action(GASHAT_OUT);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == OFF) {
            // No change
        } else if (current_button1 == ON && current_button2 == OFF && current_button3 == ON) {
            set_action(CRITICAL_FINISH);
        } else if (current_button1 == OFF && current_button2 == ON && current_button3 == ON) {
            set_action(GENRE);
        } else if (current_button1 == ON && current_button2 == ON && current_button3 == ON) {
            // No change
        }
    }

    // Update before state for the next loop iteration
    before_button1 = current_button1;
    before_button2 = current_button2;
    before_button3 = current_button3;

    delay(100);
    // digitalWrite(LED_PIN, LOW);
}
