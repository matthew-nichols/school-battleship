#ifndef IDKNOTI_DARKGDK_DB_CSOUND_CLASS
#define IDKNOTI_DARKGDK_DB_CSOUND_CLASS

#include <id/idDarkGDK.h>

class dbCSound
{
private:
	int _soundNum;
public:
	dbCSound() { _soundNum = 0; }
	dbCSound(int iSound) { _soundNum = iSound; }
	dbCSound(const char* szFilename, int iSound) { _soundNum = iSound; Load(szFilename); }

	int& SoundNumber() { return _soundNum; }
	const int& SoundNumber() const { return _soundNum; }

	void Load(const char* szFilename) { dbLoadSound((LPSTR)szFilename, _soundNum); }
	void Load(const char* szFilename, int iFlag) { dbLoadSound((LPSTR)szFilename, _soundNum, iFlag); };
	void Delete() { dbDeleteSound(_soundNum); }

	void Play() { dbPlaySound(_soundNum); }
	void Play(int iOffset) { dbPlaySound(_soundNum, iOffset); }
	void Loop() { dbLoopSound(_soundNum); }
	void Loop(int iStart) { dbLoopSound(_soundNum, iStart); }
	void Loop(int iStart, int iEnd) { dbLoopSound(_soundNum, iStart, iEnd); }
	void Loop(int iStart, int iEnd, int iInitialPosition) { dbLoopSound(_soundNum, iStart, iEnd, iInitialPosition); }

	void Stop() { dbStopSound(_soundNum); }
	void Resume() { dbResumeSound(_soundNum); }
	void Pause() { dbPauseSound(_soundNum); }

	void SetSpeed(int iFrequency) { dbSetSoundSpeed(_soundNum, iFrequency); }
	void SetVolume(int iVolume) { dbSetSoundVolume(_soundNum, iVolume); }

	int Exist() { return dbSoundExist(_soundNum); }
	int Type() { return dbSoundType(_soundNum); }
	int Playing() { return dbSoundPlaying(_soundNum); }
	int Looping() { return dbSoundLooping(_soundNum); }
	int Paused() { return dbSoundPaused(_soundNum); }
	int Speed() { return dbSoundSpeed(_soundNum); }
	int Volume() { return dbSoundVolume(_soundNum); }
};

#endif