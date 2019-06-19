#include "stdafx.h"

#include "SmartHandle.hpp"

SmartHandle::SmartHandle(const HANDLE handle) : handle(handle, HandleDisposer{})
{
}

auto SmartHandle::Get() const -> HANDLE
{
	return handle.get();
}

auto SmartHandle::IsValid() const -> BOOL
{
	return handle.get() != INVALID_HANDLE_VALUE || handle != nullptr;
}
