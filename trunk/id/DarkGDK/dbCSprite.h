#ifndef IDKNOTI_DARKGDK_DB_CSPRITE_CLASS
#define IDKNOTI_DARKGDK_DB_CSPRITE_CLASS

#include <id/idDarkGDK.h>

class dbCSprite
{
private:
	int _spriteNum;
public:
	dbCSprite() { _spriteNum = 0; }
	dbCSprite(int iID) { _spriteNum = iID; }
	dbCSprite(int iID, int iX, int iY, int iImage) { _spriteNum = iID; Create(iX, iY, iImage); }
	dbCSprite(int iID, Idknoti::Vec2i pos, int iImage) { _spriteNum = iID; Create(pos, iImage); }
	dbCSprite(int iID, int iX, int iY, dbCImage& image) { _spriteNum = iID; Create(iX, iY, image); }
	dbCSprite(int iID, Idknoti::Vec2i pos, dbCImage& image) { _spriteNum = iID; Create(pos, image); }

	int& SpriteNumber() { return _spriteNum; }
	const int& SpriteNumber() const { return _spriteNum; }

	void Create(int iX, int iY, int iImage) { dbSprite(_spriteNum, iX, iY, iImage); }
	void Create(const Idknoti::Vec2i pos, int iImage) { dbSprite(_spriteNum, pos, iImage); }
	void Create(int iX, int iY, dbCImage& image) { dbSprite(_spriteNum, iX, iY, image.ImageNumber()); }
	void Create(const Idknoti::Vec2i pos, dbCImage& image) { dbSprite(_spriteNum, pos, image.ImageNumber()); }

	void SetPosition(int iX, int iY) { dbSetSpritePosition(_spriteNum, iX, iY); }
	void SetPosition(Idknoti::Vec2i pos) { dbSetSpritePosition(_spriteNum, pos); }
	const Idknoti::Vec2i Size() { return dbSpriteSize(_spriteNum); }

	void Set(int iBackSave, int iTransparency) { dbSetSprite(_spriteNum, iBackSave, iTransparency); }
	void Paste(int iX, int iY) { dbPasteSprite(_spriteNum, iX, iY); }
	void Paste(Idknoti::Vec2f pos) { dbPasteSprite(_spriteNum, pos); }
	void Size(int iXSize, int iYSize) { dbSizeSprite(_spriteNum, iXSize, iYSize); }
	void Scale(float fScale) { dbScaleSprite(_spriteNum, fScale); }
	void Stretch(int iXStretch, int iYStretch) { dbStretchSprite(_spriteNum, iXStretch, iYStretch); }
	void Mirror() { dbMirrorSprite(_spriteNum); }
	void Flip() { dbFlipSprite(_spriteNum); }
	void Offset(int iXOffset, int iYOffset) { dbOffsetSprite(_spriteNum, iXOffset, iYOffset); }
	void Offset(Idknoti::Vec2i offset) { dbOffsetSprite(_spriteNum, offset); }
	void Hide() { dbHideSprite(_spriteNum); }
	void Show() { dbShowSprite(_spriteNum); }
	void Delete() { dbDeleteSprite(_spriteNum); }

	void Move(float velocity) { dbMoveSprite(_spriteNum, velocity); }
	void Rotate(float fRotate) { dbRotateSprite(_spriteNum, fRotate); }
	void SetImage(int iImage) { dbSetSpriteImage(_spriteNum, iImage); }
	void SetImage(dbCImage& image) { dbSetSpriteImage(_spriteNum, image.ImageNumber()); }
	void SetAlpha(int iValue) { dbSetSpriteAlpha(_spriteNum, iValue); }
	void SetDiffuse(int iR, int iG, int iB) { dbSetSpriteDiffuse(_spriteNum, iR, iG, iB); }
	void Play(int iStart, int iEnd, int iDelay) { dbPlaySprite(_spriteNum, iStart, iEnd, iDelay); }
	void SetFrame(int iFrame) { dbSetSpriteFrame(_spriteNum, iFrame); }
	void SetTextureCoordinates(int iVertex, float tu, float tv) { dbSetSpriteTextureCoordinates(_spriteNum, iVertex, tu, tv); }
	void CreateAnimated(const char* szImage, int iWidth, int iHeight, int iImageID) { dbCreateAnimatedSprite(_spriteNum, const_cast<char*>(szImage), iWidth, iHeight, iImageID); }
	void SetPriority(int iPriority) { dbSetSpritePriority(_spriteNum, iPriority); }

	int Exist() { return dbSpriteExist(_spriteNum); }
	int X() { return dbSpriteX(_spriteNum); }
	int Y() { return dbSpriteY(_spriteNum); }
	const Idknoti::Vec2i Position() { return dbSpritePosition(_spriteNum); }
	int Image() { return dbSpriteImage(_spriteNum); }
	int Width() { return dbSpriteWidth(_spriteNum); }
	int Height() { return dbSpriteHeight(_spriteNum); }
	int ScaleX() { return dbSpriteScaleX(_spriteNum); }
	int ScaleY() { return dbSpriteScaleY(_spriteNum); }
	int Mirrored() { return dbSpriteMirrored(_spriteNum); }
	int Flipped() { return dbSpriteFlipped(_spriteNum); }
	int OffsetX() { return dbSpriteOffsetX(_spriteNum); }
	int OffsetY() { return dbSpriteOffsetY(_spriteNum); }
	const Idknoti::Vec2i Offset() { return dbSpriteOffset(_spriteNum); }
	int Hit(int iTarget) { return dbSpriteHit(_spriteNum, iTarget); }
	int Collision(int iTarget) { return dbSpriteCollision(_spriteNum, iTarget); }

	float Angle() { return dbSpriteAngle(_spriteNum); }
	int Alpha() { return dbSpriteAlpha(_spriteNum); }
	int Red() { return dbSpriteRed(_spriteNum); }
	int Green() { return dbSpriteGreen(_spriteNum); }
	int Blue() { return dbSpriteBlue(_spriteNum); }
	int Frame() { return dbSpriteFrame(_spriteNum); }
	int Visible() { return dbSpriteVisible(_spriteNum); }
};

#endif