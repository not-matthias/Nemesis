#pragma once

struct HandleDisposer
{
	void operator()(const HANDLE handle) const
	{
		if (handle != INVALID_HANDLE_VALUE || handle != nullptr)
		{
			CloseHandle(handle);
		}
	}
};

class SmartHandle
{
	/**
	 * \brief The handle which should be managed.
	 */
	std::shared_ptr<VOID> handle;

public:

	/**
	 * \brief Initializes the shared pointer.
	 * \param handle The specified handle.
	 */
	SmartHandle(HANDLE handle);

	/**
	 * \brief Returns the managed handle.
	 * \return The managed handle.
	 */
	auto Get() const -> HANDLE;

	/**
	 * \brief Checks whether the handle is valid.
	 * \return True if it's valid.
	 */
	auto IsValid() const -> BOOL;
};
