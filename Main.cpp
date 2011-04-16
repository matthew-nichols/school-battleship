#include <id/idDarkGDK.h>
#include <id/HighResTimer.h>
#include <sstream>

// We should really find a better place for this
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Image::h;
DarkGDKExt::HandleAllocator<1, 32> DarkGDKExt::Bitmap::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Sound::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Music::h;

using namespace Idknoti;
using namespace DarkGDKExt;

class Ship
{
private:
	Image _i;
	int _x, _y; // Location on grid
	int _h, _w;
public:
	Ship(Image i, int x, int y, int h, int w)
		: _i(i)
	{
		_x = x; _y = y; _h = h; _w = w;
	}

	void setPosition(int x, int y)
	{
		_x = x; _y = y;
	}

	void setPosition(Vec2i v)
	{
		_x = v.x(); _y = v.y();
	}

	Vec2i getPosition() { return Vec2i(_x, _y); }

	Image getImage() { return _i; }

	bool IntersectsWith(Ship s)
	{
		return _x < s._x + s._w && _x + _w > s._x && _y < s._y + s._h && _y + _h > s._y;
	}

	bool HitBy(Vec2i gridPos)
	{
		return gridPos.x() >= _x && gridPos.x() <= _x + _w && gridPos.y() >= _y && gridPos.y() <= _y + _h;
	}
};

enum CellState
{
	CELL_UNFIRED = 0,
	CELL_HIT = 1,
	CELL_MISSED = 2,
};

const int CELL_WIDTH = 50;
const int CELL_HEIGHT = 50;

class BattleshipGrid
{
private:
	bool _showShips;
	Vec2i _pos;
	Vec2i _x, _y;
	vector<Ship> ships;
	CellState board[10][10];
public:
	BattleshipGrid()
	{
		_x = Vec2i(50, 0);
		_y = Vec2i(0, 50);
		_pos = Vec2i(5, 5);
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
				board[x][y] = CELL_UNFIRED;
	}

	void setPosition(Vec2i pos) { _pos = pos; }

	void setPosition(int x, int y) { _pos = Vec2i(x, y); }

	CellState& state(int x, int y) { return board[x][y]; }

	Vec2i MouseToCell(Vec2i m)
	{
		Vec2f temp = (Vec2f)m - (Vec2f)_pos;
		temp = temp / 50.0f;
		return Vec2i(floor(temp.x()), floor(temp.y()));
	}

	void display()
	{
		// display background
		dbInk(dbRGB(0, 0, 128), 0);
		dbBox(_pos, _pos + 10 * _x + 10 * _y);

		// display ships
		for (vector<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
			i->getImage().Paste(_pos + 50 * i->getPosition());

		// display grid
		dbInk(0, 0);
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				dbLine(_pos + _x * x + _y * y, _pos + _x * (x + 1) + _y * y);
				dbLine(_pos + _x * x + _y * y, _pos + _x * x + _y * (y + 1));
			}
		}
		
		dbLine(_pos + _x * 10, _pos + _x * 10 + _y * 10);
		dbLine(_pos + _y * 10, _pos + _x * 10 + _y * 10);

		// display hit-or-miss
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				switch(board[x][y])
				{
				case CELL_UNFIRED:
					break;
				case CELL_HIT:
					dbInk(dbRGB(255, 0, 0), 0);
					dbLine(_pos + x * _x + y * _y, _pos + (x + 1) * _x + (y + 1) * _y);
					dbLine(_pos + (x + 1) * _x + y * _y, _pos + x * _x + (y + 1) * _y);
					break;
				case CELL_MISSED:
					dbInk(dbRGB(255, 255, 255), 0);
					dbCircle(static_cast<Vec2i>((Vec2f)_pos + (x + 0.5f) * (Vec2f)_x + (y + 0.5f) * (Vec2f)_y), 20);
					break;
				}

			}
		}
	}

};

class Menu
{
public:
	virtual Menu* Update(float elapsed) = 0;
	virtual void Display() = 0;
};


class Battleship : public Menu
{
	Image f_title;
	BattleshipGrid ai;
	BattleshipGrid player;
public:
	Battleship()
		: f_title(DarkGDKFont("Times", 32).Render("BATTLESHIP!"))
	{
		ai.setPosition(0, 134);
		player.setPosition(524, 134);
	}
	virtual Menu* Update(float elapsed)
	{
		if (dbMouseClick() & 1)
		{
			Vec2i temp = player.MouseToCell(dbMouse());
			if (temp.x() >= 0 && temp.x() < 10 && temp.y() >= 0 && temp.y() < 10)
				player.state(temp.x(), temp.y()) = (CellState)dbRND(2);

		}
		return this;
	}
	virtual void Display()
	{
		f_title.Paste(dbScreenWidth() / 2 - f_title.Width() / 2, 0);

		stringstream ss;
		Vec2i g = player.MouseToCell(dbMouse());
		ss << "(" << g.x() << ", " << g.y() << ")";
		DarkGDKFont f;
		f.Render(ss.str().c_str()).Paste(0, 10);

		ai.display();
		player.display();
	}
};

class MainMenu : public Menu
{
	Image f_welcome;
	Image f_play;
	bool mouse_down;
public:
	MainMenu()
		: f_welcome(DarkGDKFont("Arial", 48, Font_Italic, dbRGB(255, 255, 255)).Render("Welcome to Battleship!")),
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