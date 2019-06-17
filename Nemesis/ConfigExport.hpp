#pragma once

#include <Windows.h>

#include "Config.hpp"

inline Config config(L"Nemesis", L"./Nemesis.ini");

auto SetConfigValueExport(LPCWSTR key, LPCWSTR value) -> BOOL;

auto GetConfigValueExport(LPCWSTR key) -> LPCWSTR;
