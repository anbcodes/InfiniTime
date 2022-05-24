#include "Keyboard.h"
#include <string>
#include <stack>
#include <cfloat>
#include <cmath>
#include <map>
#include <memory>

using namespace Pinetime::Applications::Screens;

// Anonymous Namespace for all the structs

static void eventHandler(lv_obj_t* obj, lv_event_t event) {
  auto calc = static_cast<Keyboard*>(obj->user_data);
  calc->OnButtonEvent(obj, event);
}

char Keyboard::text[31] = {0};
uint8_t Keyboard::position = 0;

Keyboard::~Keyboard() {
  lv_obj_clean(lv_scr_act());
}

static const char* buttonMap1[] = {
  "a", "b", "c", "d", "\n",
  "e", "f", "g", "h", "\n",
  "i", "j", "k", "^", "\n",
  "m", "n", "o", " ", "",
};

static const char* buttonMap1Caps[] = {
  "A", "B", "C", "D", "\n",
  "E", "F", "G", "H", "\n",
  "I", "J", "K", "^", "\n",
  "M", "N", "O", " ", "",
};

static const char* buttonMap2[] = {
  "p", "q", "r", "s", "\n",
  "t", "u", "v", "w", "\n",
  "x", "y", "z", "^", "\n",
  ".", "0", "1", " ", "",
};


static const char* buttonMap2Caps[] = {
  "P", "Q", "R", "S", "\n",
  "T", "U", "V", "W", "\n",
  "X", "Y", "Z", "^", "\n",
  "@", "2", "3", " ", "",
};

Keyboard::Keyboard(DisplayApp* app, Controllers::MotorController& motorController) : Screen(app), motorController {motorController} {
  result = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_long_mode(result, LV_LABEL_LONG_BREAK);
  lv_label_set_text(result, text);
  lv_obj_set_size(result, 180, 60);
  lv_obj_set_pos(result, 0, 0);

  returnButton = lv_btn_create(lv_scr_act(), nullptr);
  lv_obj_set_size(returnButton, 52, 52);
  lv_obj_set_pos(returnButton, 186, 0);
  lv_obj_t* returnLabel;
  returnLabel = lv_label_create(returnButton, nullptr);
  lv_label_set_text(returnLabel, "<=");
  lv_obj_align(returnLabel, nullptr, LV_ALIGN_CENTER, 0, 0);
  returnButton->user_data = this;
  lv_obj_set_event_cb(returnButton, eventHandler);

  buttonMatrix = lv_btnmatrix_create(lv_scr_act(), nullptr);
  lv_btnmatrix_set_map(buttonMatrix, buttonMap1);
  lv_obj_set_size(buttonMatrix, 240, 180);
  lv_obj_set_pos(buttonMatrix, 0, 60);
  lv_obj_set_style_local_pad_all(buttonMatrix, LV_BTNMATRIX_PART_BG, LV_STATE_DEFAULT, 0);
  buttonMatrix->user_data = this;
  lv_obj_set_event_cb(buttonMatrix, eventHandler);
}

void Keyboard::OnButtonEvent(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (obj == buttonMatrix) {
      const char* buttonstr = lv_btnmatrix_get_active_btn_text(obj);

      if (buttonstr == "^") {
        caps = !caps;
        if (caps) {
          lv_btnmatrix_set_map(buttonMatrix, screen == 0 ? buttonMap1Caps : buttonMap2Caps);
        } else {
          lv_btnmatrix_set_map(buttonMatrix, screen == 0 ? buttonMap1 : buttonMap2);
        }
        return;
      }

      if (position >= 30) {
        motorController.RunForDuration(10);
        return;
      }
      text[position] = *buttonstr;
      position++;
    } else if (obj == returnButton) {
      if (position > 1) {

        position--;
      } else {
        position = 0;
        lv_label_set_text(result, "");
        return;
      }
    }

    text[position] = '\0';
    lv_label_set_text(result, text);
  }
}

bool Keyboard::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  if (event == Pinetime::Applications::TouchEvents::LongTap) {
    position = 0;
    lv_label_set_text(result, "");
    return true;
  }
  if (event == Pinetime::Applications::TouchEvents::SwipeLeft) {
    lv_btnmatrix_set_map(buttonMatrix, caps ? buttonMap2Caps : buttonMap2);
    screen = 1;
    return true;
  }
  if (event == Pinetime::Applications::TouchEvents::SwipeRight) {
    lv_btnmatrix_set_map(buttonMatrix, caps ? buttonMap1Caps : buttonMap1);
    screen = 0;
    return true;
  }
  return false;
}