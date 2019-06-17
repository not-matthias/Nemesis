#include "stdafx.h"

#include "Config.hpp"

Config::Config(const std::wstring_view app_name, const std::wstring_view file_name) : app_name(app_name), file_name(file_name)
{
}

auto Config::Set(std::wstring_view key, std::wstring_view value) const -> BOOL
{
	return WritePrivateProfileString(app_name.data(), key.data(), value.data(), file_name.data()) > 0;
}

auto Config::Get(std::wstring_view key) const -> std::wstring
{
	std::wstring buffer (MAX_PATH, '\0');
	
	//
	// Get the string from the config
	//
	const auto characters_copied = GetPrivateProfileStringW(app_name.data(), key.data(), nullptr, buffer.data(), buffer.size(), file_name.data());
	if(characters_copied <= 0)
	{
		return std::wstring();
	}
	
	//
	// Resize the buffer
	//
	buffer.resize(characters_copied);

	return buffer;
}
