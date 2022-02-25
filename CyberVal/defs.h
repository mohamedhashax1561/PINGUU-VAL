#include <cstdint>

#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
//typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types:
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

#ifndef _WINDOWS_
typedef int8 BYTE;
typedef int16 WORD;
typedef int32 DWORD;
typedef int32 LONG;
#endif
typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;       // we want to use bool in our C programs
#endif

						// Some convenience macros to make partial accesses nicer
						// first unsigned macros:
#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

						// now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


						// Helper functions to represent some assembly instructions.

#ifdef __cplusplus

						// Fill memory block with an integer value
inline void memset32(void* ptr, uint32 value, int count)
{
	uint32* p = (uint32*)ptr;
	for (int i = 0; i < count; i++)
		*p++ = value;
}

// Generate a reference to pair of operands
template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }

// rotate left
template<class T> T __ROL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T high = value >> (nbits - count);
	value <<= count;
	value |= high;
	return value;
}

// rotate right
template<class T> T __ROR__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T low = value << (nbits - count);
	value >>= count;
	value |= low;
	return value;
}

// carry flag of left shift
template<class T> int8 __MKCSHL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	return (value >> (nbits - count)) & 1;
}

// carry flag of right shift
template<class T> int8 __MKCSHR__(T value, uint count)
{
	return (value >> (count - 1)) & 1;
}

// sign flag
template<class T> int8 __SETS__(T x)
{
	if (sizeof(T) == 1)
		return int8(x) < 0;
	if (sizeof(T) == 2)
		return int16(x) < 0;
	if (sizeof(T) == 4)
		return int32(x) < 0;
	return int64(x) < 0;
}

// overflow flag of subtraction (x-y)
template<class T, class U> int8 __OFSUB__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
	}
}

// overflow flag of addition (x+y)
template<class T, class U> int8 __OFADD__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
	}
}

// carry flag of subtraction (x-y)
template<class T, class U> int8 __CFSUB__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) < uint8(y);
	if (size == 2)
		return uint16(x) < uint16(y);
	if (size == 4)
		return uint32(x) < uint32(y);
	return uint64(x) < uint64(y);
}

// carry flag of addition (x+y)
template<class T, class U> int8 __CFADD__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) > uint8(x + y);
	if (size == 2)
		return uint16(x) > uint16(x + y);
	if (size == 4)
		return uint32(x) > uint32(x + y);
	return uint64(x) > uint64(x + y);
}

#else
						// The following definition is not quite correct because it always returns
						// uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
						// For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

						// No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

						// In the decompilation listing there are some objects declarared as _UNKNOWN
						// because we could not determine their types. Since the C compiler does not
						// accept void item declarations, we replace them by anything of our choice,
						// for example a char:

#define _UNKNOWN char
struct uint128_t {
	uint64_t low;
	uint64_t high;
};
static uint8_t rol1(uint8_t x, unsigned int count) {
	count %= 8;
	return (x << count) | (x >> (8 - count));
}
static uint16_t __ROL2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << count) | (x >> (16 - count));
}
static uint32_t __ROL4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << count) | (x >> (32 - count));
}
static uint64_t rol8(uint64_t x, unsigned int count) {
	count %= 64;
	return (x << count) | (x >> (64 - count));
}
static uint8_t ror1(uint8_t x, unsigned int count) {
	count %= 8;
	return (x << (8 - count)) | (x >> count);
}
static uint16_t __ROR2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << (16 - count)) | (x >> count);
}
static uint32_t __ROR4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << (32 - count)) | (x >> count);
}
static uint64_t ror8(uint64_t x, unsigned int count) {
	count %= 64;
	return (x << (64 - count)) | (x >> count);
}
#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif


//#define Lala(s) LI_FN(OutputDebugStringA)(##s);



//===========================================================================
typedef LONG(WINAPI* RealNtFlushInstructionCache)(HANDLE ProcessHandle, PVOID BaseAddress, ULONG NumberOfBytesToFlush);

RealNtFlushInstructionCache NewNtFlushInstructionCache = NULL;
//===========================================================================
typedef struct _PEB_LDR_DATA {
	UINT8 _PADDING_[12];
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB {
#ifdef _WIN64
	UINT8 _PADDING_[24];
#else
	UINT8 _PADDING_[12];
#endif
	PEB_LDR_DATA* Ldr;
} PEB, * PPEB;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	VOID* DllBase;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _UNLINKED_MODULE
{
	HMODULE hModule;
	PLIST_ENTRY RealInLoadOrderLinks;
	PLIST_ENTRY RealInMemoryOrderLinks;
	PLIST_ENTRY RealInInitializationOrderLinks;
	PLDR_DATA_TABLE_ENTRY Entry;
} UNLINKED_MODULE;

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

std::vector<UNLINKED_MODULE> UnlinkedModules;

struct FindModuleHandle
{
	HMODULE m_hModule;
	FindModuleHandle(HMODULE hModule) : m_hModule(hModule)
	{
	}
	bool operator() (UNLINKED_MODULE const& Module) const
	{
		return (Module.hModule == m_hModule);
	}
};

void RelinkModuleToPEB(HMODULE hModule)
{
	std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));

	if (it == UnlinkedModules.end())
	{
		//DBGOUT(TEXT("Module Not Unlinked Yet!"));
		return;
	}

	RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks);
	RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks);
	RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks);
	UnlinkedModules.erase(it);
}

void UnlinkModuleFromPEB(HMODULE hModule)
{
	std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));
	if (it != UnlinkedModules.end())
	{
		//DBGOUT(TEXT("Module Already Unlinked!"));
		return;
	}

#ifdef _WIN64
	PPEB pPEB = (PPEB)__readgsqword(0x60);
#else
	PPEB pPEB = (PPEB)__readfsdword(0x30);
#endif

	PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
	PLDR_DATA_TABLE_ENTRY Current = NULL;

	while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL)
	{
		Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if (Current->DllBase == hModule)
		{
			UNLINKED_MODULE CurrentModule = { 0 };
			CurrentModule.hModule = hModule;
			CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderLinks.Blink->Flink;
			CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderLinks.Blink->Flink;
			CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderLinks.Blink->Flink;
			CurrentModule.Entry = Current;
			UnlinkedModules.push_back(CurrentModule);

			UNLINK(Current->InLoadOrderLinks);
			UNLINK(Current->InInitializationOrderLinks);
			UNLINK(Current->InMemoryOrderLinks);

			break;
		}

		CurrentEntry = CurrentEntry->Flink;
	}
}

bool HideThread(HANDLE hThread)
{
	__try
	{
		typedef NTSTATUS(NTAPI* pNtSetInformationThread)
			(HANDLE, UINT, PVOID, ULONG);
		NTSTATUS Status;

		// Get NtSetInformationThread
		pNtSetInformationThread NtSIT = (pNtSetInformationThread)
			GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")),
				"NtSetInformationThread");

		// Shouldn't fail
		if (NtSIT == NULL)
			return false;

		// Set the thread info
		if (hThread == NULL)
			Status = NtSIT(GetCurrentThread(),
				0x11, // HideThreadFromDebugger
				0, 0);
		else
			Status = NtSIT(hThread, 0x11, 0, 0);

		if (Status != 0x00000000)
			return false;
		else
			return true;
	}
	__except (1)
	{
		return false;
	}	
}

struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

std::string GetWeaponName(int id)
{
	switch (id)
	{
	default: return std::to_string(id);
		break;
	case 12974010:  return "Knife";
		break;
	case 12837525:  return "Classic";
		break;
	case 12937503:  return "Shorty";
		break;
	case 12930964:  return "Sheriff";
		break;
	case 12914022:  return "Frenzy";
		break;
	case 12926216:  return "Ghost";
		break;
	case 12966437:  return "Stinger";
		break;
	case 12958939:  return "Spectre";
		break;
	case 12907906:  return "Bucky";
		break;
	case 12904179:  return "Judge";
		break;
	case 12890466:  return "Bulldog";
		break;
	case 12948439:  return "Guardian";
		break;
	case 12894734:  return "Phantom";
		break;
	case 12883393:  return "Vandal";
		break;
	case 12955348:  return "Marshal";
		break;
	case 12939459:  return "Operator";
		break;
	case 12879411:  return "Ares";
		break;
	case 12876183:  return "Odin";
		break;
	case 12837517:  return "Botgun";
		break;
	case 12854284: return "Spike";
		break;
	case 12838426: return "Dark Cover";
		break;
	case 12838754: return "Paranoia";
		break;
	case 12838605: return "Shrouded Step";
		break;
	case 12838903: return "Omen Ult";
		break;
	case 12831216: return "Curveball";
		break;
	case 12831434: return "Blaze";
		break;
	case 12831167: return "Hot Hands";
		break;
	case 12831631: return "Phoenix Ult";
		break;
	case 12819422: return "Boom Bot";
		break;
	case 12819691: return "Blast Pack";
		break;
	case 12819238: return "Paint Shells";
		break;
	case 12819860: return "Raze Ult";
		break;
	case 12837644: return "Leer";
		break;
	case 12838144: return "Reyna Ult";
		break;
	case 12836935: return "Barrier Orb";
		break;
	case 12836780: return "Slow Orb";
		break;
	case 12837180: return "Healing Orb";
		break;
	case 12837291: return "Sage Revive";
		break;

	case 12824892: return "Regrowth";
		break;
	case 12825324: return "Trailblazer";
		break;
	case 12825016: return "Guiding Light";
		break;
	case 12825732: return "Skye Ult";
		break;

	case 12827769: return "Owl Drone";
		break;
	case 12827345: return "Shock Bolt";
		break;
	case 12827830: return "Recon Bolt";
		break;
	case 12828094: return "Sova Ult";
		break;
	case 12830376: return "Snake Bite";
		break;
	case 12829945: return "Toxic Cloud";
		break;
	case 12830146: return "Toxic Screen";
		break;
	case 12830528: return "Viper Ult";
		break;

	case 12835907: return "Fakeout";
		break;
	case 12836352: return "Blindside";
		break;
	case 12836058: return "Gatecrash";
		break;
	case 12836456: return "Yuro Ult";
		break;

	case 12832970: return "Astra Fly";
		break;
	case 12832457: return "Astra Form";
		break;
	case 12832162: return "Nebula";
		break;
	case 12832042: return "Gravity Well";
		break;
	case 12832359: return "Nova Pulse";
		break;


	case 12818640: return "Aftershock";
		break;
	case 12818895: return "Flashpoint";
		break;
	case 12818783: return "Fault Line";
		break;
	case 12818998: return "Breach Ult";
		break;

	case 12833437: return "Stim Beacon";
		break;
	case 12833569: return "Incendiary";
		break;
	case 12833236: return "Sky Smoke";
		break;
	case 12833705: return "Brim Ult";
		break;

	case 12821278: return "Trademark";
		break;
	case 12822190: return "Headhunter";
		break;
	case 12821734: return "Redezvous";
		break;
	case 12822646: return "Chamber Ult";
		break;

	case 12826209: return "Trapwire";
		break;
	case 12826104: return "Cyber Cage";
		break;
	case 12826589: return "Spycam";
		break;
	case 12826597: return "Spycam (Active)";
		break;
	case 12827016: return "Cypher Ult";
		break;

	case 12839338: return "Cloudburst";
		break;
	case 12839565: return "Updraft";
		break;
	case 12839522: return "Tailwind";
		break;
	case 12839609: return "Jett Ult";
		break;

	case 12824204: return "Fragment";
		break;
	case 12823808: return "Flashdrive";
		break;
	case 12823956: return "Zeropoint";
		break;
	case 12824350: return "KayO Ult";
		break;

	case 12828617: return "Nanoswarm";
		break;
	case 12829229: return "Alarmbot";
		break;
	case 12828822: return "Turret";
		break;
	case 12829497: return "KJ Ult";
		break;

	case 12834115: return "Fast Lane";
		break;
	case 12834426: return "Relay Bolt";
		break;
	case 12834271: return "High Gear";
		break;
	case 12834747: return "Neon Ult";
		break;

	case 12854307: return "Defuser";
		break;
	case 12840221: return "Orb";
		break;

	case 0: return "AFK";
		break;
	}
}

std::string GetCharacterName(int id)
{
	switch (id)
	{
	case 12831861: return "ASTRA";
		break;
	case 12839233: return "JETT";
		break;
	case 12821164: return "CHAMBER";
		break;
	case 12828461: return "KILLJOY";
		break;
	case 12819166: return "RAZE";
		break;
	case 12837583: return "REYNA";
		break;
	case 12836716: return "SAGE";
		break;
	case 12824834: return "SKYE";
		break;
	case 12834049: return "NEON";
		break;
	case 12829776: return "VIPER";
		break;
	case 12818547: return "BREACH";
		break;
	case 12833178: return "BRIMSTONE";
		break;
	case 12826043: return "CYPHER";
		break;
	case 12838374: return "OMEN";
		break;
	case 12830864: return "PHOENIX";
		break;
	case 12827255: return "SOVA";
		break;
	case 12835854: return "YORU";
		break;
	case 12823740: return "KAY/O";
		break;
	case 12837536: return "BOT";
		break;
	case 12837942: return "MED BOT";
		break;
	case 12837930: return "HARD BOT";
		break;
	case 12832898: return "Astral Form";
		break;
	default:
		return std::to_string(id);
		break;
	}
}

int roundto127(int a)
{
	if (a < -127)
	{
		return -127;
	}
	else if (a > 127)
	{
		return 127;
	}
	else
	{
		return (int)a;
	}
}