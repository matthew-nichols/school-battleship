#ifndef IDKNOTI_DARKGDK_EVEN_BETTER_MUSIC
#define IDKNOTI_DARKGDK_EVEN_BETTER_MUSIC

#include <id/idDarkGDK.h>

namespace DarkGDKExt
{

class Music
{
private:
	dbCMusic m;
	static HandleAllocator<1, 65535> h;
	Music() {}
	void DecRef()
	{
		if (--(h.RefCount(m.MusicNumber())) == 0)
		{
			h.Deallocate(m.MusicNumber());
			m.Delete();
		}
	}
	void AddRef() { ++(h.RefCount(m.MusicNumber())); }
public:
	Music(const char* filename)
	{
		m.MusicNumber() = h.Allocate();
		AddRef();
		m.Load(filename);
	}

	Music(Music& other)
	{
		m = other.m;
		AddRef();
	}

	Music& operator= (const Music& other)
	{
		if (this == &other)
			return *this;

		DecRef();
		m = other.m;
		AddRef();

		return *this;
	}

	void Play() { m.Play(); }
	void Loop() { m.Loop(); }
	void Stop() { m.Stop(); }
	void Resume() { m.Resume(); }
	void Pause() { m.Pause(); }

	bool isPlaying() { return m.Playing(); }
	bool isLooping() { return m.Looping(); }
	bool isPaused() { return m.Paused(); }

	~Music() { DecRef(); }
};

}

#endif
