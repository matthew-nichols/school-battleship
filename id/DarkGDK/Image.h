#ifndef IDKNOTI_DARKGDK_EVEN_BETTER_IMAGE
#define IDKNOTI_DARKGDK_EVEN_BETTER_IMAGE

#include <id/idDarkGDK.h>

namespace DarkGDKExt
{

class Image
{
private:
	dbCImage i;
	static HandleAllocator<1, 65535> h;
	Image() {}
	void DecRef()
	{
		if (--(h.RefCount(i.ImageNumber())) == 0)
		{
			h.Deallocate(i.ImageNumber());
			i.Delete();
		}
	}
	void AddRef() { ++(h.RefCount(i.ImageNumber())); }
public:
	Image(const char* filename)
	{
		i.ImageNumber() = h.Allocate();
		AddRef();
		i.Load(filename, 1);
	}

	Image(const Image& other)
	{
		i = other.i;
		++(h.RefCount(i.ImageNumber()));
	}

	Image(Bitmap& bitmap)
	{
		i.ImageNumber() = h.Allocate();
		AddRef();
		int temp = dbCurrentBitmap();
		bitmap.MakeCurrent();
		i.Get(0, 0, bitmap.Width(), bitmap.Height(), 1);
		dbSetCurrentBitmap(temp);
	}

	Image& operator=(const Image& other)
	{
		if (this == &other)
			return *this;

		DecRef();
		i = other.i;
		++(h.RefCount(i.ImageNumber()));

		return *this;
	}

	void Paste(int x, int y)
	{
		i.Paste(x, y, 1);
	}

	void Paste(Idknoti::Vec2i v)
	{
		i.Paste(v, 1);
	}

	void PasteOpaque(int x, int y)
	{
		i.Paste(x, y);
	}

	void PasteOpaque(Idknoti::Vec2i v)
	{
		i.Paste(v);
	}

	int Width()
	{
		return i.GetWidth();
	}
	
	int Height()
	{
		return i.GetHeight();
	}

	~Image() { DecRef(); }
};

}

#endif