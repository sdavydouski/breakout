#pragma once

#include <functional>

typedef std::function <void (int key, int scancode, int action, int mods)> KeyHandler;
