#include "stdafx.h"

#include "ConfigExport.hpp"

auto SetConfigValueExport(const std::string_view key, const std::string_view value) -> BOOL
{
	return config.Set(key, value);
}

auto GetConfigValueExport(const std::string_view key) -> std::string
{
	return config.Get(key);
}
