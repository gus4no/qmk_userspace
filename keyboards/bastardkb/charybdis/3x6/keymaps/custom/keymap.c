/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
// #define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
    KC_TRNS, KC_Q,               KC_W,               KC_F,                KC_P,                 KC_B,               KC_J,           KC_L,               KC_U,           KC_Y,               KC_SCLN,            KC_TRNS,
    KC_TRNS, MT(MOD_LALT, KC_A), MT(MOD_LSFT, KC_R), LT(1, KC_S),         MT(MOD_LGUI, KC_T),   KC_G,               KC_M,           MT(MOD_RGUI, KC_N), LT(2, KC_E),    MT(MOD_RSFT, KC_I), MT(MOD_RCTL, KC_O), KC_TRNS,
    KC_TRNS, KC_Z,               KC_X,               KC_C,                MT(MOD_MEH, KC_D),    KC_V,               KC_K,           MT(MOD_MEH, KC_H),  KC_COMMA,       KC_DOT,             KC_SLASH,           KC_TRNS,
                                                     KC_TRNS,             MT(MOD_LGUI, KC_ENT), KC_TAB,             KC_BSPC,        KC_SPACE
  ),
  [LAYER_LOWER] = LAYOUT(
    QK_BOOT, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS,     KC_TRNS,                                 KC_PIPE,        KC_7,           KC_8,           KC_9,           KC_BSLS,       QK_BOOT,
    KC_TRNS, KC_TRNS, KC_LEFT_SHIFT,  KC_TRNS, KC_LEFT_GUI, KC_TRNS,                                 KC_EQUAL,       KC_4,           KC_5,           KC_6,           KC_MINUS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS,     KC_TRNS,                                 KC_PLUS,        KC_1,           KC_2,           KC_3,           KC_UNDS,       KC_TRNS,
                                      KC_TRNS, KC_TRNS,    KC_TRNS,                                  KC_TRNS, KC_0
  ),
  [LAYER_RAISE] = LAYOUT(
    QK_BOOT, KC_TRNS, KC_LBRC,     KC_UP,          KC_RBRC,        KC_MNXT,                                KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,        KC_TRNS, QK_BOOT,
    KC_TRNS, KC_TRNS, KC_LEFT,     KC_DOWN,        KC_RIGHT,       KC_MPLY,                                KC_TRNS, KC_RIGHT_GUI, KC_TRNS, KC_RIGHT_SHIFT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_VOLD,     KC_MUTE,        KC_VOLU,        KC_MPRV,                                KC_TRNS, KC_RIGHT_ALT, KC_TRNS, KC_RIGHT_CTRL,  KC_TRNS, KC_TRNS,
                                   KC_TRNS,        KC_TRNS,        KC_GRAVE,                               KC_TRNS, KC_TRNS
  ),
  [LAYER_POINTER] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_RBRC), DPI_MOD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, LGUI(KC_LBRC), DPI_RMOD,
                               KC_TRNS, KC_TRNS, DRGSCRL,                               KC_TRNS, KC_TRNS
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // --- accumulation method example ---
    static int16_t cum_dx = 0;
    static int16_t cum_dy = 0;

    // Add the current report deltas
    cum_dx += mouse_report.x;
    cum_dy += mouse_report.y;
    if (abs(cum_dx) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(cum_dy) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
        cum_dx = 0;
        cum_dy = 0;
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif


const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  '*', '*', '*', '*', '*'
);

const uint16_t PROGMEM combo0[] = { KC_W, KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_U, KC_Y, KC_L, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo4[] = { MT(MOD_RGUI, KC_N), LT(2, KC_E), COMBO_END};
const uint16_t PROGMEM combo5[] = { LT(2, KC_E), MT(MOD_RSFT, KC_I), COMBO_END};
const uint16_t PROGMEM combo6[] = { MT(MOD_LSFT, KC_R), MT(MOD_RSFT, KC_I), COMBO_END};
const uint16_t PROGMEM combo7[] = { MT(MOD_LSFT, KC_R), LT(1, KC_S), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ESCAPE),
    COMBO(combo1, KC_ESCAPE),
    COMBO(combo2, KC_QUOTE),
    COMBO(combo3, KC_GRAVE),
    COMBO(combo4, KC_LBRC),
    COMBO(combo5, KC_RBRC),
    COMBO(combo6, OSM(MOD_LSFT)),
    COMBO(combo7, KC_TAB)
};

#ifdef COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    // If you want all combos to be tap-only, just uncomment the next line
    // return true

    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LALT, KC_A):
            return TAPPING_TERM + 50;
        case MT(MOD_LSFT, KC_R):
            return TAPPING_TERM -25;
        case LT(1, KC_S):
            return TAPPING_TERM -25;
        case MT(MOD_RSFT, KC_I):
            return TAPPING_TERM -25;
        case LT(5, KC_SPACE):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   // --- Reset auto pointer timer if a mouse button is clicked ---
    switch (keycode) {
        case KC_BTN1:
        case KC_BTN2:
        case KC_BTN3:
          if (layer_state_is(LAYER_POINTER)) {
            auto_pointer_layer_timer = timer_read();
          }
          break;
    }

  return true;
}


uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_S):
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}
