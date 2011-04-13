#ifndef IDKNOTI_DARKGDK_EVEN_BETTER_SOUND
#define IDKNOTI_DARKGDK_EVEN_BETTER_SOUND

#include <id/idDarkGDK.h>

namespace DarkGDKExt
{

class Sound
{
private:
	dbCSound s;
	static HandleAllocator<1, 65535> h;
	Sound() {}
	void DecRef()
	{
		if (--(h.RefCount(s.SoundNumber())) == 0)
		{
			h.Deallocate(s.SoundNumber());
			s.Delete();
		}
	}
	void AddRef() { ++(h.RefCount(s.SoundNumber())); }
public:
	Sound(const char* filename)
	{
		s.SoundNumber() = h.Allocate();
		AddRef();
		s.Load(filename);
	}

	Sound(Sound& other)
	{
		s = other.s;
		AddRef();
	}

	Sound& operator= (const Sound& other)
	{
		if (this == &other)
			return *this;

		DecRef();
		s = other.s;
		AddRef();

		return *this;
	}

	void Play() { s.Play(); }
	void Loop() { s.Loop(); }
	void Stop() { s.Stop(); }
	void Resume() { s.Resume(); }
	void Pause() { s.Pause(); }

	bool isPlaying() { return s.Playing(); }
	bool isLooping() { return s.Looping(); }
	bool isPaused() { return s.Paused(); }

	~Sound() { DecRef(); }
};

}

#endif
