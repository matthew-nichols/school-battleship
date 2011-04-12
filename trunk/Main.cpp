#include <id/idDarkGDK.h>
#include <id/HighResTimer.h>

using namespace Idknoti;

enum EventType
{
	MOUSE_CLICK,
	KEY_DOWN,
	KEY_UP,
};

class Event
{
public:
	EventType type;
	int arg;
	Event() {}
	Event(EventType type) { this->type = type; }
	Event(EventType type, int arg) { this->type = type; this->arg = arg; }
};

bool GetMessage(Event& e, float elapsed)
{
	static bool spaceDown = false;

	bool returnValue = false;

	if (spaceDown && !dbSpaceKey())
	{
		e.type = KEY_UP;
		e.arg = ' ';
		returnValue = true;
	}
	if (!spaceDown && dbSpaceKey())
	{
		e.type = KEY_DOWN;
		e.arg = ' ';
		returnValue = true;
	}

	spaceDown = dbSpaceKey();

	return returnValue;
}

class Menu
{
public:
	virtual void ProcessMessage(const Event& e) = 0;
	virtual Menu* Update(float elapsed) = 0;
	virtual void Display() = 0;
};


class Battleship : public Menu
{
public:
	virtual void ProcessMessage(const Event& e) {}
	virtual Menu* Update(float elapsed) { return this; }
	virtual void Display() { dbCenterText(150, 150, "BATTLESHIP!"); }
};

class MainMenu : public Menu
{
	bool change;
public:
	MainMenu() {change = false;}
	virtual void ProcessMessage(const Event& e) {change = e.type == KEY_DOWN && e.arg == ' ';}
	virtual Menu* Update(float elapsed) { return change ? (Menu*)(new Battleship) : this; }
	virtual void Display() { dbCenterText(150, 150, "Hello, world!"); }
};

void DarkGDK()
{
	dbSetDisplayMode(1024, 768, 32);
	dbSetWindowOff();

	dbSyncOn();

	auto_ptr<Menu> menu(new MainMenu);

	HighResTimer timer;
	timer.Start();

	while (LoopGDK())
	{
		const float elapsed = timer.Elapsed();
		timer.Start();

		Event e;
		while (GetMessage(e, elapsed))
			menu->ProcessMessage(e);

		dbCLS(dbRGB(255, 0, 255));

		Menu* temp;
		temp = menu->Update(elapsed);
		menu->Display();

		if (temp != menu.get())
			menu = auto_ptr<Menu>(temp);

		//dbBox(0, 134, 500, 654);

		//dbBox(524, 134, 1024, 654);

		dbSync();
	}
	
	return;
}
