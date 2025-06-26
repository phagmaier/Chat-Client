#pragma once
#include "client.h"
#include "constants.h"
#include "raygui.h"
#include "theme.h"
#include <cstring>
#include <raylib.h>

class Signup {
public:
  Signup(State &state, Font &font_header, Font &font_text, Client &db);

  void draw(std::string &usrName);

private:
  State &state_;
  Font &font_header;
  Font &font_text;
  Client &client_;

  Rectangle userBox_;
  Rectangle passBox_;
  Rectangle sendBtn_;
  Rectangle backBtn_;

  static constexpr int Lim = 100;
  char user_[Lim + 1]{};
  char pass_[Lim + 1]{};
  bool focusUser_ = true;
  bool focusPass_ = false;
  std::string error_;
  float textW;
};
