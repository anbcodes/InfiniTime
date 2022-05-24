#pragma once

#include <lvgl/src/lv_misc/lv_color.h>
#include "components/settings/Settings.h"

namespace Pinetime {
  namespace Colors {
    const lv_color_t Primary = LV_COLOR_MAKE(0, 100, 255);
    const lv_color_t Secondary = LV_COLOR_MAKE(0, 255, 100);
    const lv_color_t Neutral = LV_COLOR_GRAY;
    const lv_color_t Disabled = lv_color_hex(0x111111);
    const lv_color_t PrimaryText = LV_COLOR_WHITE;
    const lv_color_t SecondaryText = LV_COLOR_WHITE;
    const lv_color_t NeutralText = LV_COLOR_WHITE;
    const lv_color_t DisabledText = LV_COLOR_WHITE;
  }
  namespace Applications {
    lv_color_t Convert(Controllers::Settings::Colors color);
  }
}