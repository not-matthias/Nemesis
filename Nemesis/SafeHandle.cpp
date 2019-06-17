#include "stdafx.h"

#include "SafeHandle.hpp"

SafeHandle::SafeHandle(const HANDLE handle) : handle(handle, HandleDisposer{})
{
}


auto SafeHandle::Get() const -> HANDLE
{
	return handle.get();
}

auto SafeHandle::IsValid() const -> BOOL
{
	return handle.get() != INVALID_HANDLE_VALUE || handle != nullptr;
}
