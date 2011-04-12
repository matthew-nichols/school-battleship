#ifndef IDNKOTI_DARKGDK_EXTENSIONS_HANDLE_ALLOCATOR_CLASS_THINGY
#define IDNKOTI_DARKGDK_EXTENSIONS_HANDLE_ALLOCATOR_CLASS_THINGY

#include <id/idDarkGDK.h>
#include <set>
#include <cassert>

namespace DarkGDKExt
{

template <int iID_Start, int iID_End>
class HandleAllocator
{
private:
	size_t ref[iID_End - iID_Start + 1];
	std::set<int> freeHandles;
	int handleNum; // keeps track of how far freeHandles go; it stores in range [iID_Start, handleNum)
public:
	HandleAllocator()
	{
		handleNum = iID_Start;
		for (int i = iID_Start; i <= iID_End; i++)
			ref[i - iID_Start] = 0;
	}

	int Allocate()
	{
		if (freeHandles.empty())
		{
			int i = handleNum;
			++handleNum;
			assert(i <= iID_End);
			return i;
		}
		else
		{
			std::set<int>::iterator it = freeHandles.begin();
			int i = *it;
			freeHandles.erase(it);
			return i;
		}
	}

	void Deallocate(int iID)
	{
		assert(iID_Start <= iID);
		assert(iID < handleNum);
		assert(ref[iID - iID_Start] == 0);

		if (iID + 1 == handleNum)
			--handleNum;
		else
			freeHandles.insert(iID);
	}	

	size_t& RefCount(int iID)
	{
		return ref[iID - iID_Start];
	}

	size_t* GetRefCountPtr(int iID)
	{
		return ref + iID - iID_Start;
	}
};

}

#endif