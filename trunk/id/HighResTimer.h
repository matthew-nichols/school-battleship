#ifndef IDKNOTI_HIGHRESTIMER
#define IDKNOTI_HIGHRESTIMER

#include <windows.h>

namespace Idknoti
{

class HighResTimer
{
private:
	__int64 start;
public:
	void Start()
	{
		start = GetTicks();
	}

	// elapsed time in seconds
	double Elapsed()
	{
		return (double)(GetTicks() - start) / (double)Frequency();
	}

// These are less portable, and should be kept private
private:
	__int64 ElapsedTicks()
	{
		return GetTicks() - start;
	}

	static __int64 GetTicks()
	{
		LARGE_INTEGER tick;
		if (QueryPerformanceCounter(&tick))
		{
			return tick.QuadPart;
		}
		else
		{
			return 0;
		}

	}

	static __int64 Frequency()
	{
		LARGE_INTEGER tick;
		if (QueryPerformanceFrequency(&tick))
		{
			return tick.QuadPart;
		}
		else
		{
			return 0;
		}
	}
};

}

#endif
