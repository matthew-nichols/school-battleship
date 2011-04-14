#ifndef IDKNOTI_DARKGDK_GDK_FONT
#define IDKNOTI_DARKGDK_GDK_FONT

#include <string>

namespace DarkGDKExt
{

class Font
{
private:
public:
	virtual Image Render(const char* str) = 0;
	//virtual Image RenderOpaque(const char* str) = 0;
};

enum DarkGDKFontStyle
{
Font_Normal = 0,
Font_Italic = 1,
Font_Bold = 2,
Font_BoldItalic = 3
};

class DarkGDKFont : public Font
{
private:
	std::string _szFont;
	int _iSize;
	DarkGDKFontStyle _style;
	DWORD _color;
public:
	DarkGDKFont()
	{
		// should be default font; change if it changes in the future
		_szFont = "Fixedsys";
		_iSize = 12;
		_style = Font_Normal;
		_color = dbRGB(255, 255, 255);
	}

	DarkGDKFont(std::string FontName, int FontSize)
	{
		_szFont = FontName;
		_iSize = FontSize;
		_style = Font_Normal;
		_color = dbRGB(255, 255, 255);
	}

	DarkGDKFont(std::string FontName, int FontSize, DarkGDKFontStyle style, DWORD color)
	{
		_szFont = FontName;
		_iSize = FontSize;
		_style = style;
		_color = color;
	}

	virtual Image Render(const char* str)
	{
		int temp = dbCurrentBitmap();

		dbSetTextFont(const_cast<char*>(_szFont.c_str()));
		dbSetTextSize(_iSize);
		if (_style == Font_Normal)
			dbSetTextToNormal();
		else if (_style == Font_Italic)
			dbSetTextToItalic();
		else if (_style == Font_Bold)
			dbSetTextToBold();
		else if (_style == Font_BoldItalic)
			dbSetTextToBoldItalic();
		else
			assert(false);

		Bitmap b(dbTextWidth(const_cast<char*>(str)), dbTextHeight(const_cast<char*>(str)));
		dbInk(_color, 0);
		dbText(0, 0, const_cast<char*>(str));

		Image i(b);		
		dbSetCurrentBitmap(temp);
		return i;
	}
};

}

#endif
