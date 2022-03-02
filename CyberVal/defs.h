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
	case 13189488:  return "Knife";
		break;
	case 13046148:  return "Classic";
		break;
	case 13150386:  return "Shorty";
		break;
	case 13143847:  return "Sheriff";
		break;
	case 13125721:  return "Frenzy";
		break;
	case 13138332:  return "Ghost";
		break;
	case 13181514:  return "Stinger";
		break;
	case 13173864:  return "Spectre";
		break;
	case 13119610:  return "Bucky";
		break;
	case 13115571:  return "Judge";
		break;
	case 13101466:  return "Bulldog";
		break;
	case 13161746:  return "Guardian";
		break;
	case 13105985:  return "Phantom";
		break;
	case 13093635:  return "Vandal";
		break;
	case 13169314:  return "Marshal";
		break;
	case 13152342:  return "Operator";
		break;
	case 13089569:  return "Ares";
		break;
	case 13086236:  return "Odin";
		break;
	case 13046140:  return "Botgun";
		break;
	case 13062907: return "Spike";
		break;
	case 13047049: return "Dark Cover";
		break;
	case 13047377: return "Paranoia";
		break;
	case 13047228: return "Shrouded Step";
		break;
	case 13047526: return "Omen Ult";
		break;
	case 13039839: return "Curveball";
		break;
	case 13040057: return "Blaze";
		break;
	case 13039790: return "Hot Hands";
		break;
	case 13040254: return "Phoenix Ult";
		break;
	case 13028045: return "Boom Bot";
		break;
	case 13028314: return "Blast Pack";
		break;
	case 13027861: return "Paint Shells";
		break;
	case 13028483: return "Raze Ult";
		break;
	case 13046267: return "Leer";
		break;
	case 13046767: return "Reyna Ult";
		break;
	case 13045558: return "Barrier Orb";
		break;
	case 13045403: return "Slow Orb";
		break;
	case 13045803: return "Healing Orb";
		break;
	case 13045914: return "Sage Revive";
		break;

	case 13033515: return "Regrowth";
		break;
	case 13033947: return "Trailblazer";
		break;
	case 13033639: return "Guiding Light";
		break;
	case 13034355: return "Skye Ult";
		break;

	case 13036392: return "Owl Drone";
		break;
	case 13035968: return "Shock Bolt";
		break;
	case 13036453: return "Recon Bolt";
		break;
	case 13036717: return "Sova Ult";
		break;
	case 13038999: return "Snake Bite";
		break;
	case 13038568: return "Toxic Cloud";
		break;
	case 13038769: return "Toxic Screen";
		break;
	case 13039151: return "Viper Ult";
		break;

	case 13044530: return "Fakeout";
		break;
	case 13044975: return "Blindside";
		break;
	case 13044681: return "Gatecrash";
		break;
	case 13045079: return "Yuro Ult";
		break;

	case 13041593: return "Astra Fly";
		break;
	case 13041080: return "Astra Form";
		break;
	case 13040785: return "Nebula";
		break;
	case 13040665: return "Gravity Well";
		break;
	case 13040982: return "Nova Pulse";
		break;


	case 13027263: return "Aftershock";
		break;
	case 13027518: return "Flashpoint";
		break;
	case 13027406: return "Fault Line";
		break;
	case 13027621: return "Breach Ult";
		break;

	case 13042060: return "Stim Beacon";
		break;
	case 13042192: return "Incendiary";
		break;
	case 13041859: return "Sky Smoke";
		break;
	case 13042328: return "Brim Ult";
		break;

	case 13029901: return "Trademark";
		break;
	case 13030813: return "Headhunter";
		break;
	case 13030357: return "Redezvous";
		break;
	case 13031269: return "Chamber Ult";
		break;

	case 13034832: return "Trapwire";
		break;
	case 13034727: return "Cyber Cage";
		break;
	case 13035212: return "Spycam";
		break;
	case 13035220: return "Spycam (Active)";
		break;
	case 13035639: return "Cypher Ult";
		break;

	case 13047961: return "Cloudburst";
		break;
	case 13048188: return "Updraft";
		break;
	case 13048145: return "Tailwind";
		break;
	case 13048232: return "Jett Ult";
		break;

	case 13032827: return "Fragment";
		break;
	case 13032431: return "Flashdrive";
		break;
	case 13032579: return "Zeropoint";
		break;
	case 13032973: return "KayO Ult";
		break;

	case 13037240: return "Nanoswarm";
		break;
	case 13037852: return "Alarmbot";
		break;
	case 13037445: return "Turret";
		break;
	case 13038120: return "KJ Ult";
		break;

	case 13042738: return "Fast Lane";
		break;
	case 13043049: return "Relay Bolt";
		break;
	case 13042894: return "High Gear";
		break;
	case 13043370: return "Neon Ult";
		break;

	case 13062930: return "Defuser";
		break;
	case 13048844: return "Orb";
		break;

	case 0: return "AFK";
		break;
	}
}

std::string GetCharacterName(int id)
{
	switch (id)
	{
	case 13040168: return "ASTRA";
		break;
	case 13047856: return "JETT";
		break;
	case 13029446: return "CHAMBER";
		break;
	case 13036743: return "KILLJOY";
		break;
	case 13027404: return "RAZE";
		break;
	case 13046206: return "REYNA";
		break;
	case 13045339: return "SAGE";
		break;
	case 13033116: return "SKYE";
		break;
	case 13042446: return "NEON";
		break;
	case 13038058: return "VIPER";
		break;
	case 13026811: return "BREACH";
		break;
	case 13041531: return "BRIMSTONE";
		break;
	case 13034325: return "CYPHER";
		break;
	case 13046997: return "OMEN";
		break;
	case 13039171: return "PHOENIX";
		break;
	case 13035537: return "SOVA";
		break;
	case 13044267: return "YORU";
		break;
	case 13032022: return "KAY/O";
		break;
	case 13046159: return "BOT";
		break;
	case 13046565: return "MED BOT";
		break;
	case 13046553: return "HARD BOT";
		break;
	case 13041521: return "Astral Form";
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
