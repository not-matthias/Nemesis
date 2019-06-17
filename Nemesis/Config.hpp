#pragma once

#include <string>
#include <Windows.h>

class Config
{
	/**
	 * \brief The name of the application.
	 */
	std::wstring_view app_name;
	
	/**
	 * \brief The path to the config file.
	 */
	std::wstring_view file_name;

public:

	/**
	 * \brief Initializes the variables.
	 * \param app_name the application name
	 * \param file_name the config path
	 */
	explicit Config(std::wstring_view app_name, std::wstring_view file_name);

	/**
	 * \brief Sets the key and value in the config.
	 * \param key the specified key
	 * \param value the specified value for the key
	 * \return true if successful
	 */
	auto Set(std::wstring_view key, std::wstring_view value) const -> BOOL;

	/**
	 * \brief Gets the value of the key from the config.
	 * \param key the key of the value
	 * \return the value
	 */
	auto Get(std::wstring_view key) const -> std::wstring;
};
