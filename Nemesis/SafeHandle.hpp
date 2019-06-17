#pragma once

struct HandleDisposer
{
	auto operator()(const HANDLE handle) const -> VOID
	{
		if (handle != INVALID_HANDLE_VALUE || handle != nullptr)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handle = std::unique_ptr<void, HandleDisposer>;


class SafeHandle
{
public:
	/**
	 * \brief The handle which should be managed.
	 */
	std::shared_ptr<void> handle;

	/**
	 * \brief Initializes the shared pointer.
	 * \param handle The specified handle.
	 */
	explicit SafeHandle(HANDLE handle);
};
