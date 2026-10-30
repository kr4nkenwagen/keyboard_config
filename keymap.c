#include QMK_KEYBOARD_H
#include "raw_hid.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
        //left side row 1
        KC_TAB,
        KC_Q,
        KC_W,
        KC_E,
        KC_R,
        KC_T,
        //upper ext keys
        KC_VOLU,
        KC_BRIU,
        //right side row 1
        KC_Y,
        KC_U,
        KC_I,
        KC_O,
        KC_P,
        KC_BSPC,
        //left side row 2
        KC_ESC,
        MT(MOD_LCTL, KC_A),
        MT(MOD_LSFT, KC_S),
        MT(MOD_LGUI, KC_D),
        MT(MOD_LALT, KC_F),
        KC_G,
        //lower ext keys
        KC_VOLD,
        KC_BRID,
        //right side row 2
        MT(MOD_RCTL, KC_H),
        MT(MOD_RSFT, KC_J),
        MT(MOD_RGUI, KC_K),
        MT(MOD_RALT, KC_L),
        KC_SCLN,
        KC_QUOT,
        //left side row 3
        XXXXXXX,
        KC_Z,
        KC_X,
        KC_C,
        KC_V,
        KC_B,
        //right side row 3
        KC_N,
        KC_M,
        KC_COMM,
        KC_DOT,
        KC_SLSH,
        KC_PRINT_SCREEN,
        //left thumb cluster
        KC_ESC,
        MO(1),
        KC_SPC,
        //right thumb cluster
        KC_ENT,
        MO(2),
        XXXXXXX
  ),

    [1] = LAYOUT_split_3x6_3_ex2(
        //left side row 1
        KC_ESC,
        KC_1,
        KC_2,
        KC_3,
        KC_4,
        KC_5,
        //upper ext keys
        KC_VOLU,
        KC_BRIU,
        //lright side row 1
        KC_6,
        KC_7,
        KC_8,
        KC_9,
        KC_0,
        KC_BSPC,
        //left side row 2
        KC_LCTL,
        XXXXXXX,
        KC_PRINT_SCREEN,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        //lower ext keys
        KC_VOLD,
        KC_BRID,
        //right side row 2
        KC_LEFT,
        KC_DOWN,
        KC_UP,
        KC_RIGHT,
        XXXXXXX,
        XXXXXXX,
        //left side row 3
        KC_LSFT,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        //right side row 3
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        XXXXXXX,
        //left side thumb cluster
        KC_LGUI,
        _______,
        KC_SPC,
        //right side thumb cluster
        KC_ENT,
        MO(3),
        KC_RALT
  ),

    [2] = LAYOUT_split_3x6_3_ex2(
        //left side row 1
        KC_TAB,
        KC_EXLM,
        KC_AT,
        KC_HASH,
        KC_DLR,
        KC_PERC,
        //upper ext keys
        QK_MOUSE_WHEEL_UP,
        KC_MEDIA_PLAY_PAUSE,
        //right side row 1
        KC_CIRC,
        KC_AMPR,
        KC_ASTR,
        KC_LPRN,
        KC_RPRN,
        KC_BSPC,
        //left side row 2
        KC_LCTL,
        QK_MOUSE_CURSOR_LEFT,
        QK_MOUSE_CURSOR_DOWN,
        QK_MOUSE_CURSOR_UP,
        QK_MOUSE_CURSOR_RIGHT,
        XXXXXXX,
        //lower ext keys
        QK_MOUSE_WHEEL_DOWN,
        KC_MUTE,
        //right side row 2
        KC_MINS,
        KC_EQL,
        KC_LBRC,
        KC_RBRC,
        KC_BSLS,
        KC_GRV,
        //left side row 3
        KC_LSFT,
        KC_UNDO,
        KC_CUT,
        KC_COPY,
        KC_PASTE,
        XXXXXXX,
        //right side row 3
        KC_UNDS,
        KC_PLUS,
        KC_LCBR,
        KC_RCBR,
        KC_PIPE,
        KC_TILD,
        //left side thumb cluster
        QK_MOUSE_BUTTON_1,
        _______,
        KC_SPC,
        //right side thumb cluster
        KC_ENT,
        _______,
        QK_MOUSE_BUTTON_2
  )
};

// k4-keymap: tell the computer which layer is on, as it changes ('K' '4' LAYER over raw HID, usage
// page 0xFF60), and when it asks ("K4").
static void k4_send_layer(uint8_t layer) {
    uint8_t report[32] = {'K', '4', layer};
    raw_hid_send(report, sizeof(report));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    k4_send_layer(get_highest_layer(state));
    return state;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length >= 2 && data[0] == 'K' && data[1] == '4') k4_send_layer(get_highest_layer(layer_state));
}
