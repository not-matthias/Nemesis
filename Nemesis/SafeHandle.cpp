#include "stdafx.h"

#include "SafeHandle.hpp"

SafeHandle::SafeHandle(HANDLE handle)
{
	this->handle = unique_handle(handle);
}
