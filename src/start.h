
#pragma once
#include "constants.h"
#include "raygui.h"
#include "theme.h"

class Start {
public:
  Start(State &state, Font &font);
  void draw();

private:
  State &state_;
  Font &font_;
  Rectangle loginCard_;
  Rectangle signupCard_;
  float textW;
};
