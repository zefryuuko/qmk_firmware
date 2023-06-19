/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "zefryuuko.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        Z_HYPR,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RALT, MO(_FN),  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        QK_BOOT, KC_BRMD, KC_BRMU, _______, _______, RGB_VAD, RGB_VAI, _______, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, RGB_TOG,          Z_RGB_S,
        EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        uint8_t mods_state = get_mods();
            switch(get_highest_layer(layer_state)) {
                case _FN:
                    if (mods_state & MOD_BIT(KC_RALT)) encoder_rotate_sat(clockwise);
                    else encoder_rotate_hue(clockwise);
                    break;
                default:
                    encoder_rotate_volume(clockwise);
                    break;
        }

    
        return false;
    }
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        
        // FN Indicator
        if (get_highest_layer(layer_state) == _FN) {
            rgb_matrix_set_keys(LED_LIST_ALL, ARRAYSIZE(LED_LIST_ALL), RGB_OFF);
            rgb_matrix_set_color(LED_FN, RGB_WHITE);

            // Display Brightness (macOS)
            rgb_matrix_set_color(LED_F1, RGB_WHITE);
            rgb_matrix_set_color(LED_F2, RGB_WHITE);

            // RGB Brightness
            rgb_matrix_set_color(LED_F5, RGB_WHITE);    // Brightness Down
            rgb_matrix_set_color(LED_F6, RGB_WHITE);    // Brightness Up

            // Media Buttons
            rgb_matrix_set_color(LED_F9, RGB_WHITE);    // Mute
            rgb_matrix_set_color(LED_F10, RGB_WHITE);   // Prev
            rgb_matrix_set_color(LED_F11, RGB_WHITE);   // Play/Pause
            rgb_matrix_set_color(LED_F12, RGB_WHITE);   // Next

            // RGB LED Mode Toggle
            rgb_matrix_set_color(LED_1, RGB_WHITE);     // TODO: Toggle Backlight
            rgb_matrix_set_color(LED_2, RGB_WHITE);     // TODO: Toggle Side Lighting
        }
    }
#endif