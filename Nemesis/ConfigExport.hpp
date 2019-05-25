#pragma once

#include <string>
#include <Windows.h>

#include "Config.hpp"

inline Config config("Nemesis", "Nemesis.ini");

auto SetConfigValueExport(std::string_view key, std::string_view value) -> BOOL;

auto GetConfigValueExport(std::string_view key) -> std::string;