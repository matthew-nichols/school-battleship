#ifndef IDKNOTI_GDK_FUNCTIONS
#define IDKNOTI_GDK_FUNCTIONS

#include "DarkGDK.h"
#include <id/Vector.h>

// Core functions
void dbSetCursor(Idknoti::Vec2i pos) { dbSetCursor(pos.x(), pos.y()); }
// TODO: dbNewXValue, dbNewYValue, ... if I understand it

// Text functions
void dbText(Idknoti::Vec2i pos, char* szText) { dbText(pos.x(), pos.y(), szText); }
void dbCenterText(Idknoti::Vec2i pos, char* szText) { dbCenterText(pos.x(), pos.y(), szText); }

// Input functions
void dbPositionMouse(Idknoti::Vec2i pos) { dbPositionMouse(pos.x(), pos.y()); }
const Idknoti::Vec2i dbMouse() { return Idknoti::Vec2i(dbMouseX(), dbMouseY()); }

// Basic2D functions
void dbDot(Idknoti::Vec2i pos) { dbDot(pos.x(), pos.y()); }
void dbDot(Idknoti::Vec2i pos, DWORD dwColor) { dbDot(pos.x(), pos.y(), dwColor); }
void dbLine(Idknoti::Vec2i p1, Idknoti::Vec2i p2) { dbLine(p1.x(), p1.y(), p2.x(), p2.y()); }
void dbBox(Idknoti::Vec2i v1, Idknoti::Vec2i v2) { dbBox(v1.x(), v1.y(), v2.x(), v2.y()); }
void dbCircle(Idknoti::Vec2i pos, int iRadius) { dbCircle(pos.x(), pos.y(), iRadius); }
void dbEllipse(Idknoti::Vec2i pos, int iXRadius, int iYRadius) { dbEllipse(pos.x(), pos.y(), iXRadius, iYRadius); }
DWORD dbRGBA(int iRed, int iGreen, int iBlue, int iAlpha) { return dbRGB(iRed, iGreen, iBlue) | (iAlpha << 28); }
int dbRGBAA(DWORD iRGBA) { return iRGBA >> 28; }

// Bitmap functions
void dbCopyBitmap(int iID, Idknoti::Vec2i v1, Idknoti::Vec2i v2, int iToID, Idknoti::Vec2i vTo1, Idknoti::Vec2i vTo2)
{ dbCopyBitmap(iID, v1.x(), v1.y(), v2.x(), v2.y(), iToID, vTo1.x(), vTo1.y(), vTo2.x(), vTo2.y()); }

// Sprite functions
void dbSprite(int iID, const Idknoti::Vec2i pos, int iImage) { dbSprite(iID, pos.x(), pos.y(), iImage); }
void dbOffsetSprite(int iID, const Idknoti::Vec2i offset) { dbOffsetSprite(iID, offset.x(), offset.y()); }
void dbPasteSprite(int iID, const Idknoti::Vec2i pos) { dbPasteSprite(iID, pos.x(), pos.y()); }
const Idknoti::Vec2i dbSpritePosition(int iID) { return Idknoti::Vec2i(dbSpriteX(iID), dbSpriteY(iID)); }
const Idknoti::Vec2i dbSpriteOffset(int iID) { return Idknoti::Vec2i(dbSpriteOffsetX(iID), dbSpriteOffsetY(iID)); }
void dbSetSpritePosition(int iID, int iX, int iY) { dbSprite(iID, iX, iY, dbSpriteImage(iID)); }
void dbSetSpritePosition(int iID, const Idknoti::Vec2i pos) { dbSetSpritePosition(iID, pos.x(), pos.y()); }
const Idknoti::Vec2i dbSpriteSize(int iID) { return Idknoti::Vec2i(dbSpriteWidth(iID), dbSpriteHeight(iID)); }

// Image functions
void dbGetImage(int iID, Idknoti::Vec2i v1, Idknoti::Vec2i v2) { dbGetImage(iID, v1.x(), v1.y(), v2.x(), v2.y()); }
void dbGetImage(int iID, Idknoti::Vec2i v1, Idknoti::Vec2i v2, int iTextureFlag) { dbGetImage(iID, v1.x(), v1.y(), v2.x(), v2.y(), iTextureFlag); }
void dbPasteImage(int iID, Idknoti::Vec2i pos) { dbPasteImage(iID, pos.x(), pos.y()); }
void dbPasteImage(int iID, Idknoti::Vec2i pos, int iFlag) { dbPasteImage(iID, pos.x(), pos.y(), iFlag); }

#endif