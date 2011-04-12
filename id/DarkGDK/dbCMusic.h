#ifndef IDKNOTI_DARKGDK_DB_CMUSIC_CLASS
#define IDKNOTI_DARKGDK_DB_CMUSIC_CLASS

#include <id/idDarkGDK.h>

class dbCMusic
{
private:
	int _musicNum;
public:
	dbCMusic() { _musicNum = 0; }
	dbCMusic(int iMusic) { _musicNum = iMusic; }
	dbCMusic(const char* szFilename, int iMusic) { _musicNum = iMusic; Load(szFilename); }
	dbCMusic(int iTrackNumber, int iMusic) { _musicNum = iMusic; LoadCD(iTrackNumber); }

	int& MusicNumber() { return _musicNum; }
	const int& MusicNumber() const { return _musicNum; }

	void Load(const char* szFilename) { dbLoadMusic((LPSTR)szFilename, _musicNum); }
	void LoadCD(int iTrackNumber) { dbLoadCDMusic(iTrackNumber, _musicNum); }
	void Delete() { dbDeleteMusic(_musicNum); }

	void Play() { dbPlayMusic(_musicNum); }
	void Loop() { dbLoopMusic(_musicNum); }
	void Stop() { dbStopMusic(_musicNum); }
	void Pause() { dbPauseMusic(_musicNum); }
	void Resume() { dbResumeMusic(_musicNum); }

	void SetVolume(int iVolume) { dbSetMusicVolume(_musicNum, iVolume); }
	void SetSpeed(int iSpeed) { dbSetMusicSpeed(_musicNum, iSpeed); }

	int Exist() { dbMusicExist(_musicNum); }
	int Playing() { dbMusicPlaying(_musicNum); }
	int Looping() { dbMusicLooping(_musicNum); }
	int Paused() { dbMusicPaused(_musicNum); }
	int Volume() { dbMusicVolume(_musicNum); }
	int Speed() { dbMusicSpeed(_musicNum); }
};

#endif