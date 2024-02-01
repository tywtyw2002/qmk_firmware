#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_60_ansi(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT,
      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
      KC_LCTL, KC_LALT, KC_LGUI,     KC_SPC,       KC_RGUI, MO(1), MO(3), KC_GRV
    ),

  // 1: Function Layer
  LAYOUT_60_ansi(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
      KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_INS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_APP, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_END, KC_PGDN, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
  // 2: Mouse Layer
  LAYOUT_60_ansi(
      TO(0), KC_BTN3, KC_BTN4, KC_BTN5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO,
      KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO,
      KC_NO
  ),
  // 3: PN Layer
LAYOUT_60_ansi(
      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,     TG(4),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,
      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
      KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    QK_BOOT,  KC_NO,    TG(2),    KC_NO,    KC_NO,    KC_NO,              KC_NO,
      KC_NO,     KC_NO,    KC_NO,                                  TG(1),                                  KC_NO,    KC_NO,    KC_NO,    KC_NO
  ),
// 4: MIDI LAYER
LAYOUT_60_ansi(
      TO(0),     MI_C4,   MI_Cs4,  MI_D4,   MI_Ds4,  MI_E4,   MI_F4,   MI_Fs4,  MI_G4,   MI_Gs4,  MI_A4,   MI_As4,  MI_B4,   KC_NO,
      KC_NO,     MI_C3,   MI_Cs3,  MI_D3,   MI_Ds3,  MI_E3,   MI_F3,   MI_Fs3,  MI_G3,   MI_Gs3,  MI_A3,   MI_As3,  MI_B3,   KC_NO,
      KC_NO,     MI_C2,   MI_Cs2,  MI_D2,   MI_Ds2,  MI_E2,   MI_F2,   MI_Fs2,  MI_G2,   MI_Gs2,  MI_A2,   MI_As2,            KC_NO,
      KC_NO,               MI_C1,   MI_Cs1,  MI_D1,   MI_Ds1,  MI_E1,   MI_F1,   MI_Fs1,  MI_G1,   MI_Gs1,  MI_A1,             KC_NO,
      KC_NO,     KC_NO,    KC_NO,                                  KC_NO,                                  KC_NO,    KC_NO,    KC_NO,    KC_NO
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

