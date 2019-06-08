#include "stdafx.h"

#include "ConfigExport.hpp"

/**
 * \brief Sets the key and value in the config.
 * \param key the specified key
 * \param value the specified value for the key
 * \return true if successful
 */
auto SetConfigValueExport(const LPCSTR key, const LPCSTR value) -> BOOL
{
	return config.Set(key, value);
}

/**
 * \brief Gets the value of the key from the config.
 * \param key the key of the value
 * \return the value
 */
auto GetConfigValueExport(const LPCSTR key) -> LPCSTR
{
	return config.Get(key).c_str();
}
