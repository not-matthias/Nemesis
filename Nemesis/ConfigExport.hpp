#pragma once

#include <Windows.h>

#include "Config.hpp"

inline Config config("Nemesis", "./Nemesis.ini");

auto SetConfigValueExport(LPCSTR key, LPCSTR value) -> BOOL;

auto GetConfigValueExport(LPCSTR key) -> LPCSTR;
