#include "chatroom.h"
#include "theme.h"

ChatRoom::ChatRoom(State &s, Font &font_heading, Font &font_text, Db &d)
    : state_{s}, font_heading{font_heading}, font_text{font_text}, db_{d} {
  constexpr float pad = 32.0f;
  historyBox_ = {pad, 120, WIDTH - 2 * pad, HEIGHT - 300};
  inputBox_ = {pad, HEIGHT - 150, WIDTH - 220 - 2 * pad, 48};
  sendBtn_ = {inputBox_.x + inputBox_.width + 12, inputBox_.y, 120, 48};
  backBtn_ = {pad, 60, 100, 32};

  // float cw = MeasureTextEx(font_heading, "A", Theme::HeadingSize, 0).x;
  float text_w = MeasureTextEx(font_text, "A", Theme::textSize, 0).x;
  colLim_ = int((historyBox_.width - Theme::PAD) / text_w);
  rowLim_ = int(historyBox_.height / (Theme::textSize + Theme::PAD / 2));
}

void ChatRoom::open(const std::string &roomName, const char *user) {
  room_ = roomName;
  user_ = user;
  roomId_ = db_.getRoomId(roomName);
  history_ = db_.get_logs(rowLim_ * 2, roomId_);
  memset(input_, 0, sizeof(input_));

  textW = MeasureTextEx(font_heading, roomName.c_str(), Theme::HeadingSize,
                        Theme::spacing)
              .x;
}

void ChatRoom::draw() {
  DrawTextEx(font_heading, room_.c_str(), {WIDTH / 2.0f - textW / 2.0f, 80.f},
             Theme::HeadingSize, Theme::spacing, Theme::Accent);

  if (GuiButton(backBtn_, "Back")) {
    state_ = MENU;
    return;
  }

  drawHistory();
  bool send = GuiButton(sendBtn_, "Send");

  if (GuiTextBox(inputBox_, input_, InLim, true) &&
      (IsKeyPressed(KEY_ENTER) || send)) {
    if (input_[0]) {
      std::string line = std::string("[") + user_ + "]: " + input_;
      pushWrapped(line);
      db_.insertMessage(room_, user_, input_);
      std::memset(input_, 0, sizeof(input_));
    }
  }
}

void ChatRoom::drawHistory() const {
  DrawRectangleLinesEx(historyBox_, 2, Theme::Accent);

  int start = (int)history_.size() - rowLim_;
  if (start < 0)
    start = 0;

  Vector2 pos{historyBox_.x + Theme::PAD * 0.5f,
              historyBox_.y + Theme::PAD * 0.5f};

  for (int i = start; i < (int)history_.size(); ++i) {
    float fade = 1.0f - 0.4f * (history_.size() - 1 - i) / rowLim_;
    Color c = Fade(Theme::Fg, fade);
    DrawTextEx(font_text, history_[i].c_str(), pos, Theme::textSize,
               Theme::spacing, c);
    pos.y += Theme::HeadingSize + Theme::PAD / 2;
  }
}

void ChatRoom::pushWrapped(const std::string &s) {
  if ((int)s.size() <= colLim_) {
    history_.push_back(s);
    return;
  }

  for (size_t i = 0; i < s.size(); i += colLim_)
    history_.push_back(s.substr(i, colLim_));
}
