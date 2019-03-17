#include "Dump.hpp"

Dump::Dump(DWORD Pid)
{
	Memory *pMemory = new Memory(Pid);
}

Dump::~Dump()
{
}
