#pragma once

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])

#define Z_HYPR HYPR_T(KC_ESC)

enum custom_user_layers {
    _BASE,
    _FN,
};

enum custom_user_keycodes {
    Z_RGB_S = SAFE_RANGE,   // Save/reset RGB config
    Z_PRTSC,                // macOS Screenshot (cmd+shift+3/4)
    Z_TBKLT,                // Toggle keyboard backlight
    Z_TSDLT,                // Toggle keyboard side lighting
    NEW_SAFE_RANGE
};

#ifdef ENCODER_ENABLE
    void encoder_rotate_volume(bool clockwise);
    void encoder_rotate_hue(bool clockwise);
    void encoder_rotate_sat(bool clockwise);
#endif

#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_set_keys(const uint8_t index[], int length, uint8_t red, uint8_t green, uint8_t blue);
#endif