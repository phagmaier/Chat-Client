#include "signup.h"
#include "theme.h"

Signup::Signup(State &state, Font &font_header, Font &font_text, Db &db)
    : state_{state}, font_header{font_header}, font_text{font_text}, db_{db} {
  const float cx = WIDTH * 0.5f;
  const float topY = 220.0f;

  constexpr float boxW = 400, boxH = 48;
  userBox_ = {cx - boxW / 2, topY, boxW, boxH};
  passBox_ = {cx - boxW / 2, topY + 80, boxW, boxH};
  sendBtn_ = {cx + boxW / 2 - 120, topY + 80 + 60, 120, 46};
  backBtn_ = {userBox_.x, sendBtn_.y, sendBtn_.width, sendBtn_.height};
  textW =
      MeasureTextEx(font_header, "REGISTER", Theme::HeadingSize, Theme::spacing)
          .x;
}

void Signup::draw(std::string &usrName) {

  DrawTextEx(font_header, "REGISTER", {WIDTH / 2.0f - textW / 2.0f, 80.f},
             Theme::HeadingSize, Theme::spacing, Theme::Accent);

  const int labelSize = 20;
  DrawTextEx(font_text, "Username", {userBox_.x, userBox_.y - labelSize - 8},
             Theme::textSize, Theme::spacing, Theme::Fg);

  DrawTextEx(font_text, "Password", {passBox_.x, passBox_.y - labelSize - 8},
             Theme::textSize, Theme::spacing, Theme::Fg);

  if (GuiTextBox(userBox_, user_, Lim, focusUser_)) {
    focusUser_ = true;
    focusPass_ = false;
  }

  if (GuiTextBox(passBox_, pass_, Lim, focusPass_)) {
    focusUser_ = false;
    focusPass_ = true;
  }

  if (IsKeyPressed(KEY_TAB)) {
    focusUser_ = !focusUser_;
    focusPass_ = !focusPass_;
  }

  bool send = GuiButton(sendBtn_, "Send") || IsKeyPressed(KEY_ENTER);

  if (GuiButton(backBtn_, "Back")) {
    state_ = START;
  }

  else if (send && user_[0] && pass_[0]) {
    if (db_.isUnique(user_)) {
      state_ = MENU;
      usrName = user_;
      db_.createUser(user_, pass_);
      std::memset(pass_, 0, sizeof(pass_));
    } else {
      error_ = "Sign Up failed";
    }
  }

  if (!error_.empty()) {
    DrawTextEx(font_text, error_.c_str(), {passBox_.x, passBox_.y + 150},
               Theme::textSize, 0, RED);
  }
}
