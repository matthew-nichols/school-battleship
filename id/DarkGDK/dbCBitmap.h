#ifndef IDKNOTI_DARKGDK_DB_CBITMAP_CLASS
#define IDKNOTI_DARKGDK_DB_CBITMAP_CLASS

#include <id/idDarkGDK.h>

class dbCBitmap
{
private:
	int _bitmapNum;
public:
	dbCBitmap() { _bitmapNum = 0; }
	dbCBitmap(int BitmapNumber) { _bitmapNum = BitmapNumber; }
	dbCBitmap(const char* szFilename, int BitmapNumber) { _bitmapNum = BitmapNumber; Load(szFilename); }

	int& BitmapNumber() { return _bitmapNum; }
	const int& BitmapNumber() const { return _bitmapNum; }

	void Create(int iWidth, int iHeight) { dbCreateBitmap(_bitmapNum, iWidth, iHeight); }
	void Load(const char* szFilename) { dbLoadBitmap(const_cast<char*>(szFilename), _bitmapNum); }
	void Save(const char* szFilename) { dbSaveBitmap(const_cast<char*>(szFilename), _bitmapNum); }

	void Copy(int iToID) { dbCopyBitmap(_bitmapNum, iToID); }
	void Copy(dbCBitmap& b) { dbCopyBitmap(_bitmapNum, b._bitmapNum); }
	void Copy(int iX1, int iY1, int iX2, int iY2, int iToID, int iToX1, int iToY1, int iToX2, int iToY2)
	{ dbCopyBitmap(_bitmapNum, iX1, iY1, iX2, iY2, iToID, iToX1, iToY1, iToX2, iToY2); }
	void Copy(int iX1, int iY1, int iX2, int iY2, dbCBitmap& b, int iToX1, int iToY1, int iToX2, int iToY2)
	{ dbCopyBitmap(_bitmapNum, iX1, iY1, iX2, iY2, b._bitmapNum, iToX1, iToY1, iToX2, iToY2); }
	void Copy(Idknoti::Vec2i v1, Idknoti::Vec2i v2, int iToID, Idknoti::Vec2i vTo1, Idknoti::Vec2i vTo2)
	{ dbCopyBitmap(_bitmapNum, v1, v2, iToID, vTo1, vTo2); }
	void Copy(Idknoti::Vec2i v1, Idknoti::Vec2i v2, dbCBitmap& b, Idknoti::Vec2i vTo1, Idknoti::Vec2i vTo2)
	{ dbCopyBitmap(_bitmapNum, v1, v2, b._bitmapNum, vTo1, vTo2); }

	void Delete() { dbDeleteBitmap(_bitmapNum); }
	void Flip() { dbFlipBitmap(_bitmapNum); }
	void Mirror() { dbMirrorBitmap(_bitmapNum); }
	void Fade(int iFade) { dbFadeBitmap(_bitmapNum, iFade); }
	void Blur(int iBlurLevel) { dbBlurBitmap(_bitmapNum, iBlurLevel); }
	void SetCurrent() { dbSetCurrentBitmap(_bitmapNum); }

	int Exist() { return dbBitmapExist(_bitmapNum); }
	int Width() { return dbBitmapWidth(_bitmapNum); }
	int Height() { return dbBitmapHeight(_bitmapNum); }
	int Depth() { return dbBitmapDepth(_bitmapNum); }
	int Mirrored() { return dbBitmapMirrored(_bitmapNum); }
	int Flipped() { return dbBitmapFlipped(_bitmapNum); }

	void GetData(DWORD* dwWidth, DWORD* dwHeight, DWORD* dwDepth, LPSTR* pData, DWORD* dwDataSize, bool bLockData)
	{ dbGetBitmapData(_bitmapNum, dwWidth, dwHeight, dwDepth, pData, dwDataSize, bLockData); }
	void SetData(DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, LPSTR pData, DWORD dwDataSize)
	{ dbSetBitmapData(_bitmapNum, dwWidth, dwHeight, dwDepth, pData, dwDataSize); }

};

#endif