#include "stdafx.h"

#include "Config.hpp"

Config::Config(const std::string_view app_name, const std::string_view file_name)
{
	this->app_name = app_name;
	this->file_name = file_name;
}

Config::~Config() = default;

auto Config::Set(std::string_view key, std::string_view value) const -> BOOL
{
	return WritePrivateProfileString(app_name.data(), key.data(), value.data(), file_name.data());
}

auto Config::Get(std::string_view key) const -> std::string
{
	std::string buffer (MAX_PATH, '\0');
	DWORD characters_copied;

	//
	// Get the string from the config
	//
	if((characters_copied = GetPrivateProfileString(app_name.data(), key.data(), nullptr, buffer.data(), buffer.size(), file_name.data())) <= 0)
	{
		return std::string();
	}
	
	//
	// Resize the buffer
	//
	buffer.resize(characters_copied);

	return buffer;
}
