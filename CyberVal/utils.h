#pragma once 

#include <Psapi.h>

bool is_bad_ptr(uintptr_t* ptr) {
	if (!ptr || (uint64_t)ptr > 0xffffffffffff)
		return true;

	__try
	{
		volatile auto result = *ptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return true;
	}
	return false;
}

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace utils {
	static BOOL IsValidPointer(uintptr_t address)
	{
		if (!is_bad_ptr((uintptr_t*)address))
			return TRUE;
		else
			return FALSE;
	}

	MODULEINFO GetModuleInfo(char* szModule)
	{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}


	void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int byteNum)
	{
		//used to change our file access type, stores the old
		//access type and restores it after memory is written
		unsigned long OldProtection;
		//give that address read and write permissions and store the old permissions at oldProtection
		VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &OldProtection);

		//write the memory into the program and overwrite previous value
		memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);

		//reset the permissions of the address back to oldProtection after writting memory
		VirtualProtect((LPVOID)(addressToWrite), byteNum, OldProtection, NULL);
	}


	uintptr_t FindPattern(const char* pattern)
	{
		MODULEINFO info;
		K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &info, sizeof(info));

		auto MmBase = (uintptr_t)info.lpBaseOfDll;
		auto MmSize = info.SizeOfImage;

		char* pat = const_cast<char*>(pattern);
		uintptr_t firstMatch = 0;
		auto base = MmBase;
		uintptr_t rangeEnd = base + MmSize;

		for (auto pCur = base; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(BYTE*)pat == '\?' || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(BYTE*)pat == '\?')
					pat += 2;
				else
					pat += 3;
			}
			else
			{
				pat = const_cast<char*>(pattern);
				firstMatch = 0;
			}
		}

		return 0;
	}


    
}