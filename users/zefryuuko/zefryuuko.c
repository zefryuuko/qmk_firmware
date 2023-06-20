#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "zefryuuko.h"

// KEY CODES
__attribute__ ((weak))  bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) { return false; }
    switch (keycode) {
        case Z_RGB_S:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_RALT)) rgb_matrix_reload_from_eeprom();
                else eeconfig_update_rgblight_current();
            } else unregister_code16(keycode);
            break;
        case Z_PRTSC:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LCTL)){
                    unregister_code(KC_LCTL);
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    register_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_4);
                } else {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    register_code(KC_3);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_3);
                }
            } else unregister_code16(keycode);
            break;
    }
    
    return true;
}

#ifdef ENCODER_ENABLE
    void encoder_rotate_volume(bool clockwise) {
        if (clockwise) {
        tap_code(KC_VOLU);
        } else {
        tap_code(KC_VOLD);
        }
    }

    void encoder_rotate_hue(bool clockwise) {
        if (clockwise) {
        rgb_matrix_increase_hue_noeeprom();
        } else {
        rgb_matrix_decrease_hue_noeeprom();
        }
    }

    void encoder_rotate_sat(bool clockwise) {
        if (clockwise) {
        rgb_matrix_increase_sat_noeeprom();
        } else {
        rgb_matrix_decrease_sat_noeeprom();
        }
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_set_keys(const uint8_t index[], int length, uint8_t red, uint8_t green, uint8_t blue) {
        for (uint8_t i=0; i < length; i++) {
            rgb_matrix_set_color(index[i], red, green, blue);
        }
    }
#endif

#endif