#include <id/idDarkGDK.h>
#include <id/HighResTimer.h>

// We should really find a better place for this
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Image::h;
DarkGDKExt::HandleAllocator<1, 32> DarkGDKExt::Bitmap::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Sound::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Music::h;

using namespace Idknoti;
using namespace DarkGDKExt;

class Menu
{
public:
	virtual Menu* Update(float elapsed) = 0;
	virtual void Display() = 0;
};


class Battleship : public Menu
{
	Image f_title;
public:
	Battleship()
		: f_title(DarkGDKFont("Times", 32).Render("BATTLESHIP!"))
	{}
	virtual Menu* Update(float elapsed) { return this; }
	virtual void Display()
	{
		f_title.Paste(dbScreenWidth() / 2 - f_title.Width() / 2, 0);

		dbInk(dbRGB(255, 0, 255), 0);
		dbBox(0, 134, 500, 654);
		dbBox(524, 134, 1024, 654);
	}
};

class MainMenu : public Menu
{
	Image f_welcome;
	Image f_play;
	bool mouse_down;
public:
	MainMenu()
		: f_welcome(DarkGDKFont("Arial", 48, Font_BoldItalic, dbRGB(255, 255, 255)).Render("Welcome to Battleship!")),
		  f_play(DarkGDKFont("Times", 24).Render("Click Anywhere to Play!"))
	{
		mouse_down = false;
	}

	virtual Menu* Update(float elapsed)
	{
		bool change = false;
		
		change = mouse_down && !(dbMouseClick() & 1);
		mouse_down = dbMouseClick() & 1;

		return change ? (Menu*)(new Battleship) : this;
	}

	virtual void Display()
	{
		f_welcome.Paste(dbScreenWidth() / 2 - f_welcome.Width() / 2, 0);
		f_play.Paste(dbScreenWidth() / 2 - f_play.Width() / 2, dbScreenHeight() / 2 - f_play.Height());
	}
};

void DarkGDK()
{
	dbSetDisplayMode(1024, 768, 32);

	// fails on dual screen
	//dbSetWindowOff();

	dbSyncOn();

	auto_ptr<Menu> menu(new MainMenu);

	HighResTimer timer;
	timer.Start();

	while (LoopGDK())
	{
		const float elapsed = timer.Elapsed();
		timer.Start();

		dbCLS(0);

		Menu* temp;
		temp = menu->Update(elapsed);
		menu->Display();

		if (temp != menu.get())
			menu = auto_ptr<Menu>(temp);

		dbSync();
	}
	
	return;
}
