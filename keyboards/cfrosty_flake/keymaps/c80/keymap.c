#include QMK_KEYBOARD_H

#define RF_MAX_COUNT 120

static uint16_t rf_fire_count = 0;
static uint16_t rf_key_code;
static uint16_t rf_timer;
static uint16_t rf_delay;

static uint16_t led_timer;
static bool led_status = false;

static bool rapid_fire = false;

enum rf_states {
  OFF = 1,
  DELAY_SETUP,
  KEYCODE_SETUP,
  RUNNING
};

static enum rf_states rf_state=OFF;

enum custom_keycodes {
  RAPIDF = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Standard ANSI layer */
    LAYOUT_tkl_ansi(
          KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS,
          KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
          KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,            KC_UP,
          KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(2),   MO(3),   KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT
     ),
    /* Layer 1: Change GRV to ESC */
    LAYOUT_tkl_ansi(
          KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS,
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
          KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,            KC_UP,
          KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(2),   MO(3),   KC_GRV,    KC_LEFT, KC_DOWN, KC_RGHT
     ),
     /* Layer 2: FN Layer */
    LAYOUT_tkl_ansi(
          KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS,
          KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,    KC_INS,  KC_HOME, KC_PGUP,
          KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS,   KC_DEL,  KC_END,  KC_PGDN,
          KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP,          KC_TRNS,
          KC_TRNS,          KC_TRNS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_END,  KC_PGDN,          KC_TRNS,            KC_UP,
          KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_LEFT, KC_DOWN, KC_RGHT
     ),

    /* Layer 3: Layout selector */
    LAYOUT_tkl_ansi(
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              KC_NO,   KC_NO,   KC_NO,
          KC_NO,   DF(0),   DF(1),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RAPIDF,  KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
          KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,   TG(4),   KC_NO,   KC_NO,   KC_NO,            KC_NO,              KC_NO,
          KC_NO,   KC_NO,   KC_NO,                              TG(2),                              KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO
     ),

    /* Layer 4: Mouse selector */
    LAYOUT_tkl_ansi(
          TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_BTN3, KC_BTN4, KC_BTN5, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ACL0, KC_ACL1, KC_ACL2, KC_NO,     KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_BTN1, KC_MS_U, KC_BTN2, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO,   KC_NO,            KC_NO,
          KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,     KC_NO,
          KC_NO,   KC_NO,   KC_NO,                              KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO
     )
};

void clean_rapid_fire(void) {
  rf_fire_count = 0;
  rapid_fire = false;
  rf_state = OFF;
  writePin(C5, 1);      // caps lock
  writePin(B7, 1);      // num lock
  led_status = false;
}

void do_rapid_fire(void) {
  if (! rapid_fire ) {
    return ;
  }

  if (timer_elapsed(rf_timer) > rf_delay) {
    wait_ms(rand() % 100);
    tap_code_delay(rf_key_code, 60 + rand() % 50);
    rf_timer = timer_read();

    if (++rf_fire_count > RF_MAX_COUNT) {
      clean_rapid_fire();
    }
  }
}

void before_run_rapid_fire(void) {
  writePin(C5, 0);      // caps lock
  writePin(B7, 1);      // num lock
  rf_timer = timer_read();
  srand(timer_read());
  rapid_fire = true;
}

void init_rapid_fire(void) {
  writePin(B7, 1);      // num lock
  led_status = true;
  led_timer = timer_read();
  rf_delay = 1000;
  rf_state = DELAY_SETUP;
}

void rf_delay_setup(uint16_t keycode) {
  switch(keycode) {
    case KC_1:
      rf_delay += 1000;
      break;
    case KC_2:
      rf_delay += 500;
      break;
    case KC_3:
      rf_delay += 250;
      break;
    case KC_Q:
      if (rf_delay >= 1500) {
        rf_delay -= 1000;
      }
      break;
    case KC_W:
      if (rf_delay >= 1000) {
        rf_delay -= 500;
      }
      break;
    case KC_E:
      if (rf_delay >= 750) {
        rf_delay -= 250;
      }
      break;
  }
  // blink
  // rgblight_sethsv_noeeprom(190 - (rf_delay / 50), 255, 255);
}

bool process_rapid_fire(uint16_t keycode){
  if (rf_state == OFF) {
    return true;
  }

  switch (rf_state) {
    case DELAY_SETUP:
      if (keycode == KC_ENT) {
        writePin(B7, 0);      // num lock
        rf_state = KEYCODE_SETUP;
      } else {
        rf_delay_setup(keycode);
      }
      break;
    case KEYCODE_SETUP:
      if (keycode >= KC_A && keycode <= KC_0) {
        rf_key_code = keycode;
        rf_state = RUNNING;
        before_run_rapid_fire();
      }
      break;
    case OFF:
    case RUNNING:
      break;
  }

  if (keycode == KC_ESC) {
    clean_rapid_fire();
    return false;
  }

  return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case RAPIDF:
      init_rapid_fire();
      return false;
  }

  if (record->event.pressed) {
    return process_rapid_fire(keycode);
  }

  return true;

}

void led_blink(void) {
  int led_pin;
  if (rf_state == DELAY_SETUP) {
    led_pin = B7;
  }else if(rf_state == RUNNING) {
    led_pin = C5;
  }else {
    return ;
  }

  uint16_t t_delay = led_status ? 700 : 300;

  if (timer_elapsed(led_timer) > t_delay) {
     led_status = !led_status;
     writePin(led_pin, led_status);
     led_timer = timer_read();
  }
}

// void keyboard_post_init_user(void) {
//     writePin(B7, 0); // num lock
//     writePin(C5, 0); // caps lock
//     writePin(C6, 0); // scroll lock
// }

void matrix_scan_user(void) {
  do_rapid_fire();
  led_blink();
}