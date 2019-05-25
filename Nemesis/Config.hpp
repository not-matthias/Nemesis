#pragma once

#include <string>
#include <Windows.h>

class Config
{
	/**
	 * \brief The name of the application.
	 */
	std::string_view app_name;
	
	/**
	 * \brief The path to the config file.
	 */
	std::string_view file_name;

public:

	/**
	 * \brief Initializes the variables.
	 * \param app_name the application name
	 * \param file_name the config path
	 */
	explicit Config(std::string_view app_name, std::string_view file_name);

	/**
	 * \brief The default destructor.
	 */
	~Config();

	/**
	 * \brief Sets the key and value in the config.
	 * \param key the specified key
	 * \param value the specified value for the key
	 * \return true if successful
	 */
	auto Set(std::string_view key, std::string_view value) const -> BOOL;

	/**
	 * \brief Gets the value of the key from the config.
	 * \param key the key of the value
	 * \return the value
	 */
	auto Get(std::string_view key) const -> std::string;
};
