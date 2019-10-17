#pragma once
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

class CMax
{
public:
	static const int8   Int8   = 127;
	static const uint8  uInt8  = 255;
	static const int16  Int16  = 32767;
	static const uint16 uInt16 = 65535;
	static const int32  Int32  = 2147483647;
	static const uint32 uInt32 = 4294967295;
	static const int64  Int64  = 9223372036853775807;
	static const uint64 uInt64 = 18446744073709551615;
};