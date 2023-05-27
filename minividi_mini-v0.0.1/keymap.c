/*
 *
 * MOTIONSOUND MIDIVIDI MINI
 * NUMPAD MECHANICAL KEYBOARD MIDI CONTROLLER
 *
 * For Disguise, Hippo, or other MIDI-controller capable software
 * Programmed by Jared McCammon, Motionsound
 * email: jared@motionsound.org
 * web: https://www.motionsound.org
 *
 * Designed using Murphpad DIY Keyboard Kit by Mechwild
 * Programmed and Flashed using QMK
 *
 */

 // CODE BEGINS

#include QMK_KEYBOARD_H
#include "midi.h"
extern MidiDevice midi_device;

// Defines layer names

enum layer_names {
    _PAGE1,
    _PAGE2,
    _PAGE3,
    _PAGE4,
    _RGB
};

// Defines variables

static char current_alpha_oled = '\0';
static uint8_t midiControlValue = 127;
static char midiKnobStep = 1;

// Midi CC Stuff

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

enum custom_keycodes {
    MIDI_CC1 = SAFE_RANGE,
    MIDI_CC2,
    MIDI_CC3,
    MIDI_CC4,
    MIDI_CC5,
    MIDI_CC6,
    MIDI_CC7,
    MIDI_CC8,
    MIDI_CC9,
    MIDI_CC10,
    MIDI_CC11,
    MIDI_CC12,
    MIDI_CC13,
    MIDI_CC14,
    MIDI_CC15,
    MIDI_CC16,
    MIDI_CC17,
    MIDI_CC18,
    MIDI_CC19,
    MIDI_CC20,
    MIDI_CC21,
    MIDI_CC22,
    MIDI_CC23,
    MIDI_CC24
};

//
//


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise && midiControlValue <= 126) {
          midiControlValue += midiKnobStep;
            midi_send_cc(&midi_device, 55, 0x0C, midiControlValue);
        } else if (midiControlValue >= 1) {
          midiControlValue -= midiKnobStep;
            midi_send_cc(&midi_device, 55, 0x0C, midiControlValue);
        }
        return false;
    } else if (index == 1) {
        if (clockwise && midiControlValue <= 126) {
          midiControlValue += midiKnobStep;
            midi_send_cc(&midi_device, 56, 0x0C, midiControlValue);
        } else if (midiControlValue >= 1) {
          midiControlValue -= midiKnobStep;
            midi_send_cc(&midi_device, 56, 0x0C, midiControlValue);
        }
        return false;
    }
    return false;
}

//
// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_PAGE1] = LAYOUT(
                  MI_C,   MI_Cs,   MI_D,   MI_ON,
                  MI_Ds,  MI_E, MI_F, MI_Fs,
                  MI_G,   MI_Gs,    MI_A,   MI_As,
        MI_OCTD,  MI_B1,   MI_C1,   MI_Cs1,   _______,
        _______, MI_D1,   MI_Ds1,   MI_E1,   MI_F1,
        TO(_PAGE2),  MI_Fs1,   MI_G1, MI_Gs1, _______,

                  MI_A1,   MI_As1,   MI_B1

    ),


    [_PAGE2] = LAYOUT(
                  MI_C2,   MI_Cs2,   MI_D2,   MI_ON,
                  MI_Ds2,  MI_E2, MI_F2, MI_Fs2,
                  MI_G2,   MI_Gs2,    MI_A2,   MI_As2,
        MI_OCTD,  MI_B2,   MI_C3,   MI_Cs3,   _______,
        TO(_PAGE1), MI_D3,   MI_Ds3,   MI_E3,   MI_F3,
        TO(_PAGE3),  MI_Fs3,   MI_G3, MI_Gs3, _______,

                  MI_A3,   MI_As3,   MI_B3


    ),
    [_PAGE3] = LAYOUT(
                  MI_C4,   MI_Cs4,   MI_D4,   MI_ON,
                  MI_Ds4,  MI_E4, MI_F4, MI_Fs4,
                  MI_G4,   MI_Gs4,    MI_A4,   MI_As4,
        MI_OCTD,  MI_B4,   MI_C5,   MI_Cs5,   _______,
        TO(_PAGE2), MI_D5,   MI_Ds5,   MI_E5,   MI_F5,
        TO(_PAGE4),  MI_Fs5,   MI_G5, MI_Gs5, _______,

                  MI_A5,   MI_As5,   MI_B5
    ),

    [_PAGE4] = LAYOUT(
                  MIDI_CC1,   MIDI_CC2,   MIDI_CC3,   MI_ON,
                  MIDI_CC4,  MIDI_CC5, MIDI_CC6, MIDI_CC7,
                  MIDI_CC8,   MIDI_CC9,    MIDI_CC10,   MIDI_CC11,
        MI_OCTD,  MIDI_CC12,   MIDI_CC13,   MIDI_CC14,   _______,
        TO(_PAGE3), MIDI_CC15,   MIDI_CC16,   MIDI_CC17,   MIDI_CC18,
        TO(_RGB),  MIDI_CC19,   MIDI_CC20, MIDI_CC21, _______,

                  MIDI_CC22,   MIDI_CC23,   MIDI_CC24

    ),
    [_RGB] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        MI_OCTD, RGB_RMOD, RGB_TOG, RGB_MOD, _______,
        TO(_PAGE4), RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_SAD,  _______, RGB_SAI, _______,

                 _______, _______, _______

    )
};

// END keymap
//


//
// Record keystrokes

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case MIDI_CC1:
            if (record->event.pressed) {
                current_alpha_oled = '1';
                midi_send_cc(&midi_device, midi_config.channel, 1, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 1, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC2:
            if (record->event.pressed) {
                current_alpha_oled = '2';
                midi_send_cc(&midi_device, midi_config.channel, 2, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 2, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC3:
            if (record->event.pressed) {
                current_alpha_oled = '3';
                midi_send_cc(&midi_device, midi_config.channel, 3, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 3, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC4:
            if (record->event.pressed) {
                current_alpha_oled = '4';
                midi_send_cc(&midi_device, midi_config.channel, 4, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 4, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC5:
            if (record->event.pressed) {
                current_alpha_oled = '5';
                midi_send_cc(&midi_device, midi_config.channel, 5, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 5, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC6:
            if (record->event.pressed) {
                current_alpha_oled = '6';
                midi_send_cc(&midi_device, midi_config.channel, 6, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 6, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC7:
            if (record->event.pressed) {
                current_alpha_oled = '7';
                midi_send_cc(&midi_device, midi_config.channel, 7, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 7, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC8:
            if (record->event.pressed) {
                current_alpha_oled = '8';
                midi_send_cc(&midi_device, midi_config.channel, 8, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 8, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC9:
            if (record->event.pressed) {
                current_alpha_oled = '9';
                midi_send_cc(&midi_device, midi_config.channel, 9, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 9, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC10:
            if (record->event.pressed) {
                current_alpha_oled = 'a';
                midi_send_cc(&midi_device, midi_config.channel, 10, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 10, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC11:
            if (record->event.pressed) {
                current_alpha_oled = 'b';
                midi_send_cc(&midi_device, midi_config.channel, 11, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 11, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC12:
            if (record->event.pressed) {
                current_alpha_oled = 'd';
                midi_send_cc(&midi_device, midi_config.channel, 12, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 12, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC13:
            if (record->event.pressed) {
                current_alpha_oled = 'e';
                midi_send_cc(&midi_device, midi_config.channel, 13, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 13, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC14:
            if (record->event.pressed) {
                current_alpha_oled = 'f';
                midi_send_cc(&midi_device, midi_config.channel, 14, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 14, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC15:
            if (record->event.pressed) {
                current_alpha_oled = 'g';
                midi_send_cc(&midi_device, midi_config.channel, 15, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 15, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC16:
            if (record->event.pressed) {
                current_alpha_oled = 'h';
                midi_send_cc(&midi_device, midi_config.channel, 16, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 16, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC17:
            if (record->event.pressed) {
                current_alpha_oled = 'i';
                midi_send_cc(&midi_device, midi_config.channel, 17, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 17, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC18:
            if (record->event.pressed) {
                current_alpha_oled = 'j';
                midi_send_cc(&midi_device, midi_config.channel, 18, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 18, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC19:
            if (record->event.pressed) {
                current_alpha_oled = 'k';
                midi_send_cc(&midi_device, midi_config.channel, 19, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 19, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC20:
            if (record->event.pressed) {
                current_alpha_oled = 'l';
                midi_send_cc(&midi_device, midi_config.channel, 20, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 20, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC21:
            if (record->event.pressed) {
                current_alpha_oled = 'm';
                midi_send_cc(&midi_device, midi_config.channel, 21, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 21, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC22:
            if (record->event.pressed) {
                current_alpha_oled = 'n';
                midi_send_cc(&midi_device, midi_config.channel, 22, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 22, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC23:
            if (record->event.pressed) {
                current_alpha_oled = 'o';
                midi_send_cc(&midi_device, midi_config.channel, 23, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 23, MIDI_CC_OFF);
            }
            return true;
      case MIDI_CC24:
            if (record->event.pressed) {
                current_alpha_oled = 'p';
                midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_OFF);
            }
            return true;
        case MI_C:
            if (record->event.pressed) {
                current_alpha_oled = '1';
            } else {
            }
            break;
        case MI_Cs:
            if (record->event.pressed) {
                current_alpha_oled = '2';
            } else {
            }
            break;
        case MI_D:
            if (record->event.pressed) {
                current_alpha_oled = '3';
            } else {
            }
            break;
        case MI_Ds:
            if (record->event.pressed) {
                current_alpha_oled = '4';
            } else {
            }
            break;

        default:
            break;
    }
    return true;
}

//END Record keystrokes
//

//
// OLED Configuration

#ifdef OLED_ENABLE

bool oled_task_user(void) {

    // Layer Status
    oled_write_P(PSTR("Page: "), false);

    switch (get_highest_layer(layer_state)) {
        case _PAGE1:
            oled_write_P(PSTR("1\n"), false);
            break;
        case _PAGE2:
            oled_write_P(PSTR("2\n"), false);
            break;
        case _PAGE3:
            oled_write_P(PSTR("3\n"), false);
            break;
        case _PAGE4:
            oled_write_P(PSTR("4\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Current Cue
    switch (biton32(layer_state)) {
      case _PAGE1:
          oled_write_P(PSTR("Cue: "), false);
          if (current_alpha_oled == '\0') {
              oled_write_char('*', false);
          } else {
              oled_write_char(current_alpha_oled, false);
          }
          break;
      case _PAGE2:
          oled_write_P(PSTR("Cue: "), false);
          if (current_alpha_oled == '\0') {
              oled_write_char('*', false);
          } else {
              oled_write_char(current_alpha_oled, false);
          }
          break;
      case _PAGE3:
          oled_write_P(PSTR("Cue: "), false);
          if (current_alpha_oled == '\0') {
              oled_write_char('*', false);
          } else {
              oled_write_char(current_alpha_oled, false);
          }
          break;
      case _PAGE4:
          oled_write_P(PSTR("Cue: "), false);
          if (current_alpha_oled == '\0') {
              oled_write_char('*', false);
          } else {
              oled_write_char(current_alpha_oled, false);
          }
          break;
  }

    // Host Keyboard LED Status
    // led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif

// END OLED Config
//
