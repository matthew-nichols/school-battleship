#ifndef IDKNOTI_DARKGDK_EVEN_BETTER_BITMAP
#define IDKNOTI_DARKGDK_EVEN_BETTER_BITMAP

#include <id/idDarkGDK.h>

namespace DarkGDKExt
{

class Bitmap
{
private:
	dbCBitmap b;
	static HandleAllocator<1, 32> h;
	Bitmap() {}
	void DecRef()
	{
		if (--(h.RefCount(b.BitmapNumber())) == 0)
		{
			h.Deallocate(b.BitmapNumber());
			b.Delete();
		}
	}
	void AddRef() { ++(h.RefCount(b.BitmapNumber())); }
public:
	Bitmap(const char* filename)
	{
		b.BitmapNumber() = h.Allocate();
		AddRef();
		b.Load(filename);
	}

	Bitmap(int width, int height)
	{
		b.BitmapNumber() = h.Allocate();
		AddRef();
		b.Create(width, height);
	}

	Bitmap(const Bitmap& other)
	{
		b = other.b;
		AddRef();
	}
	
	Bitmap& operator=(const Bitmap& other)
	{
		if (this != &other)
		{
			DecRef();
			b = other.b;
			AddRef();
		}
		return *this;
	}

	void Flip() { b.Flip(); }
	void Mirror() { b.Mirror(); }

	void MakeCurrent() { b.SetCurrent(); }

	int Width() { return b.Width(); }
	int Height() { return b.Height(); }
	int Depth() { return b.Depth(); }

	bool isMirrored() { return b.Mirrored(); }
	bool isFlipped() { return b.Flipped(); }

	~Bitmap() { DecRef(); }
};

}

#endif
