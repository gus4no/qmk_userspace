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
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif // VIA_ENABLE

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 700
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y // inverts vertical scrolling
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 400
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
#endif // POINTING_DEVICE_ENABLE

#define AUTO_SHIFT_TIMEOUT 160
#define NO_AUTO_SHIFT_TAB
#define NO_AUTO_SHIFT_ALPHA
#define CHORDAL_HOLD
#define ONESHOT_TAP_TOGGLE 2
#undef MASTER_RIGHT
#define MASTER_LEFT
#define QUICK_TAP_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define COMBO_MUST_TAP_PER_COMBO
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_COUNT 7
#define TAPPING_TERM_PER_KEY
#define ONESHOT_TIMEOUT 1000
// Smaller = faster scrolling (less movement per tick)
#define CHARYBDIS_SCROLL_DIVISOR_H 80
#define CHARYBDIS_SCROLL_DIVISOR_V 70
#define WHEEL_EXTENDED_SUPPORT
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 1
#define MOUSE_EXTENDED_REPORT
