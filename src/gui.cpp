#include "gui.h"

void runGui() {

  InitWindow(WIDTH, HEIGHT, "Chat App");
  SetTargetFPS(30);
  Font font_text = LoadFontEx("../Font/RobotoMono-VariableFont_wght.ttf",
                              Theme::textSize, 0, 0);
  ;
  Font font_heading = LoadFontEx("../Font/RobotoMono-VariableFont_wght.ttf",
                                 Theme::HeadingSize, 0, 0);

  State state = START;
  std::string currentRoom_;
  std::string usrName;

  asio::io_context ctx;
  auto client = Client(ctx);
  Start start = Start(state, font_heading);
  Signup signup = Signup(state, font_heading, font_text, client);
  Login login = Login(state, font_heading, font_text, client);
  Menu menu = Menu(state, font_heading, client);
  std::string room_name;
  ChatRoom room = ChatRoom(state, font_heading, font_text, client);

  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x33373BFF);
  GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xE0E0E0FF);
  GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x3C9CE8FF);
  GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x00A8E8FF);
  GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xFFFFFFFF);
  GuiSetFont(font_text);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground({24, 26, 27, 255});
    if (state == START) {
      start.draw();
    } else if (state == LOGIN) {
      login.draw(usrName);
    } else if (state == SIGNUP) {
      signup.draw(usrName);
    } else if (state == MENU) {
      menu.draw(room_name);
      if (state == ROOM) {
        room.open(room_name, usrName.c_str());
      }
    } else if (state == ROOM) {
      room.draw();
    }

    EndDrawing();
  }

  if (font_text.texture.id != GetFontDefault().texture.id) {
    UnloadFont(font_text);
  }
  if (font_heading.texture.id != GetFontDefault().texture.id) {
    UnloadFont(font_heading);
  }
  CloseWindow();
}
