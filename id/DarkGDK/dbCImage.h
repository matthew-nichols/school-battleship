#ifndef IDKNOTI_DARKGDK_DB_CIMAGE_CLASS
#define IDKNOTI_DARKGDK_DB_CIMAGE_CLASS

#include <id/idDarkGDK.h>

class dbCImage
{
private:
	int _imageNum;
public:
	dbCImage() { _imageNum = 0; }
	dbCImage(int iImage) { _imageNum = iImage; }
	dbCImage(const char* szFilename, int iImage) { _imageNum = iImage; Load(szFilename); }
	dbCImage(const char* szFilename, int iImage, int TextureFlag)
	{ _imageNum = iImage; Load(szFilename, TextureFlag); }
	dbCImage(const char* szFilename, int iImage, int TextureFlag, int iDivideTextureSize)
	{ _imageNum = iImage; Load(szFilename, TextureFlag, iDivideTextureSize); }

	dbCImage& operator =(const dbCImage other)
	{ 
		if (this != &other)
			_imageNum = other._imageNum;
		return *this;
	}

	int& ImageNumber() { return _imageNum; }
	const int& ImageNumber() const { return _imageNum; }

	void Load(const char* szFilename) { dbLoadImage(const_cast<char*>(szFilename), _imageNum); }
	void Load(const char* szFilename, int TextureFlag) { dbLoadImage(const_cast<char*>(szFilename), _imageNum, TextureFlag); }
	void Load(const char* szFilename, int TextureFlag, int iDivideTextureSize) { dbLoadImage(const_cast<char*>(szFilename), _imageNum, TextureFlag, iDivideTextureSize); }

	void Save(const char* szFilename) { dbSaveImage(const_cast<char*>(szFilename), _imageNum); }
	void Save(const char* szFilename, int iCompressionMode) { dbSaveImage(const_cast<char*>(szFilename), _imageNum, iCompressionMode); }

	void Get(int iX1, int iY1, int iX2, int iY2) { dbGetImage(_imageNum, iX1, iY1, iX2, iY2); }
	void Get(int iX1, int iY1, int iX2, int iY2, int iTextureFlag) { dbGetImage(_imageNum, iX1, iY1, iX2, iY2, iTextureFlag); }
	void Get(Idknoti::Vec2i v1, Idknoti::Vec2i v2) { dbGetImage(_imageNum, v1, v2); }
	void Get(Idknoti::Vec2i v1, Idknoti::Vec2i v2, int iTextureFlag) { dbGetImage(_imageNum, v1, v2, iTextureFlag); }

	void Paste(int iX, int iY) { dbPasteImage(_imageNum, iX, iY); }
	void Paste(int iX, int iY, int iFlag) { dbPasteImage(_imageNum, iX, iY, iFlag); }
	void Paste(Idknoti::Vec2i v) { dbPasteImage(_imageNum, v); }
	void Paste(Idknoti::Vec2i v, int iFlag) { dbPasteImage(_imageNum, v, iFlag); }

	void Delete() { dbDeleteImage(_imageNum); }

	void Rotate(int iAngle) { dbRotateImage(_imageNum, iAngle); }

	int Exist() { return dbImageExist(_imageNum); }

	void GetData(DWORD* dwWidth, DWORD* dwHeight, DWORD* dwDepth, LPSTR* pData, DWORD* dwDataSize, bool bLockData)
		{ dbGetImageData(_imageNum, dwWidth, dwHeight, dwDepth, pData, dwDataSize, bLockData); }

	void SetData(DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, LPSTR pData, DWORD dwDataSize)
		{ dbSetImageData(_imageNum, dwWidth, dwHeight, dwDepth, pData, dwDataSize); }

	int GetWidth() { return dbGetImageWidth(_imageNum); }
	int GetHeight() { return dbGetImageHeight(_imageNum); }

	bool GetExist() { return dbGetImageExist(_imageNum); }
	LPSTR GetName() { return dbGetImageName(_imageNum); }

	void Lock() { dbLockImage(_imageNum); }
	void Unlock() { dbUnlockImage(_imageNum); }
	void Write(int iX, int iY, int iA, int iR, int iG, int iB) { dbWriteImage(_imageNum, iX, iY, iA, iR, iG, iB); }
	void Get(int iX, int iY, int* piR, int* piG, int* piB) { dbGetImage(_imageNum, iX, iY, piR, piG, piB); }

	void SetTranslucency(int iPercent) { dbSetImageTranslucency(_imageNum, iPercent); }

	bool LoadEx(const char* szFilename) { return dbLoadImageEx(const_cast<char*>(szFilename), _imageNum); }

	float GetUMax() { return dbGetImageUMax(_imageNum); }
	float GetVMax() { return dbGetImageVMax(_imageNum); }

	void Stretch(int iSizeX, int iSizeY) { dbStretchImage(_imageNum, iSizeX, iSizeY); }
};

#endif