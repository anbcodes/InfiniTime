#pragma once


#include "Screen.h"
#include "components/motor/MotorController.h"
#include <array>
#include <string>

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class Keyboard : public Screen {
      public:
        ~Keyboard() override;

        Keyboard(DisplayApp* app, Controllers::MotorController& motorController);

        void OnButtonEvent(lv_obj_t* obj, lv_event_t event);

        bool OnTouchEvent(Pinetime::Applications::TouchEvents event) override;

      private:
        lv_obj_t *result, *returnButton, *buttonMatrix;

        bool caps = false;

        uint8_t screen = 0;

        static char text[31];
        static uint8_t position;

        Controllers::MotorController& motorController;
      };

    }
  }
}