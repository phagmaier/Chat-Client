#pragma once
#include <raylib.h>

namespace Theme {
// colours
constexpr Color Bg = {24, 26, 27, 255};
constexpr Color Fg = {224, 224, 224, 255};
constexpr Color Accent = {0, 192, 255, 255};

// spacing & sizes
constexpr float PAD = 24.0f; // ← new: generic inner padding
constexpr int HeadingSize = 48;
constexpr int textSize = 20;
constexpr float CardW = 300;
constexpr float CardH = 90;
constexpr float Gap = 32; // vertical gap between cards
constexpr int body = 32;
constexpr int spacing = 0;

inline Rectangle card(float cx, float y) {
  return {cx - CardW * 0.5f, y, CardW, CardH};
}
} // namespace Theme
