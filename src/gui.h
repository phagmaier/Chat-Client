#pragma once
#include "constants.h"
#include "theme.h"

#include "chatroom.h"
#include "client.h"
#include "login.h"
#include "menu.h"
#include "signup.h"
#include "start.h"

std::unordered_map<std::string, int> parse_rooms(std::string &str);
void runGui();
