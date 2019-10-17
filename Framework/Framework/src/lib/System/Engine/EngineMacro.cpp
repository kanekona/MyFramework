#include "EngineMacro.h"

#if WINDOWS_BUILD
#include <Windows.h>
#endif

#if ENGINE_DEBUG
bool KLEnsure(bool flag)
{
	if (flag)
	{
		__debugbreak();
	}
	return flag;
}
bool KLEnsure(bool flag, const char* msg)
{
	if (flag)
	{
		printf("%s", msg);
#if WINDOWS_BUILD
		OutputDebugString(msg);
#endif
		__debugbreak();
	}
	return flag;
}
bool KLCheck(bool flag)
{
	if (flag)
	{
		exit(1);
	}
	return flag;
}
bool KLCheck(bool flag, const char* msg)
{
	if (flag)
	{
		printf("%s", msg); 
#if WINDOWS_BUILD
		OutputDebugString(msg);
#endif
		exit(1);
	}
	return flag;
}
#endif