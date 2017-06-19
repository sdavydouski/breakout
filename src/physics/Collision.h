#pragma once

#include "Direction.h"
#include <glm/vec2.hpp>
#include <tuple>

using Collision = std::tuple<bool, Direction, glm::vec2>;
