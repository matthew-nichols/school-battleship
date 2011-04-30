#include <id/idDarkGDK.h>
#include <id/HighResTimer.h>
#include <sstream>
#include <ctime>

// We should really find a better place for this
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Image::h;
DarkGDKExt::HandleAllocator<1, 32> DarkGDKExt::Bitmap::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Sound::h;
DarkGDKExt::HandleAllocator<1, 65535> DarkGDKExt::Music::h;

using namespace Idknoti;
using namespace DarkGDKExt;
using namespace std;

class Button
{
private:
	int _x, _y;
	Image _i;
public:
	Button(Image i, int x, int y)
		: _i(i)
	{
		_x = x;
		_y = y;
	}

	Vec2i getPosition() { return Vec2i(_x, _y); }
	void setPosition(int x, int y) { _x = x; _y = y; }
	int getWidth() { return _i.Width(); }
	int getHeight() { return _i.Height(); }

	void Render() { _i.Paste(_x, _y); }
	bool withinBounds(Vec2i m)
	{
		return m.x() >= _x && m.y() >= _y && m.x() <= _x + _i.Width() && m.y() <= _y + _i.Height();
	}
};

class Ship
{
private:
	Image _i;
	int _x, _y; // Location on grid
	int _h, _w;
public:
	Ship()
		: _i(Bitmap(1, 1))
	{
	}

	Ship(const Ship& other)
		:_i(other._i)
	{
		_x = other._x;
		_y = other._y;
		_h = other._h;
		_w = other._w;
	}
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
		return gridPos.x() >= _x && gridPos.x() < _x + _w && gridPos.y() >= _y && gridPos.y() < _y + _h;
	}

	int getWidth() { return _w; }
	int getHeight() { return _h; }
};

vector<Ship> possibleShips; // 0,1;2,3;etc. same ship, different rotations

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
		_showShips = true;
		_x = Vec2i(50, 0);
		_y = Vec2i(0, 50);
		_pos = Vec2i(5, 5);
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
				board[x][y] = CELL_UNFIRED;
		for (int s = 0; s < 5; s++)
		{
			Ship temp(possibleShips[2 * s + dbRND(1)]);
			temp.setPosition(dbRND(10-temp.getWidth()), dbRND(10-temp.getHeight()));
			for (vector<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
			{
				if (temp.IntersectsWith(*i))
				{
					--s;
					goto OuterLoop;
				}
			}
			ships.push_back(temp);
OuterLoop:;
		}
	}

	bool allIsLost()
	{
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (board[x][y] == CELL_UNFIRED && thereIsShip(x, y))
					return false;
			}
		}
		return true;
	}

	void setPosition(Vec2i pos) { _pos = pos; }

	void setPosition(int x, int y) { _pos = Vec2i(x, y); }

	CellState& state(int x, int y) { return board[x][y]; }
	CellState& state(Vec2i v) { return board[v.x()][v.y()]; }

	Vec2i MouseToCell(Vec2i m)
	{
		Vec2f temp = (Vec2f)m - (Vec2f)_pos;
		temp = temp / 50.0f;
		return Vec2i(floor(temp.x()), floor(temp.y()));
	}

	bool& shipsVisible() { return _showShips; }

	bool thereIsShip(int x, int y)
	{
		for (vector<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
		{
			if (i->HitBy( Vec2i( x, y ) ) )
				return true;
		}
		
		return false;
	}

	void display()
	{
		// display background
		dbInk(dbRGB(0, 0, 128), 0);
		dbBox(_pos, _pos + 10 * _x + 10 * _y);

		// display ships
		if (_showShips)
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

Menu* becauseCppWontLookFoward();

class Battleship : public Menu
{
	Image f_title;
	Button returnToMain;
	BattleshipGrid ai;
	BattleshipGrid player;
public:
	Battleship()
		: f_title(DarkGDKFont("Times", 32).Render("BATTLESHIP!")),
		returnToMain(DarkGDKFont("Times", 32).Render("Return to Main Menu"), 0, 0)
	{
		returnToMain.setPosition(dbScreenWidth() / 2 - returnToMain.getWidth() / 2, dbScreenHeight() - returnToMain.getHeight() - 75); 
		ai.setPosition(0, 134);
		ai.shipsVisible() = false;
		player.setPosition(524, 134);
	}
	virtual Menu* Update(float elapsed)
	{
		if (dbMouseClick() & 1)
		{
			Vec2i temp = ai.MouseToCell(dbMouse());
			if (temp.x() >= 0 && temp.x() < 10 && temp.y() >= 0 && temp.y() < 10)
			{
				CellState s = ai.state(temp.x(), temp.y());
				if (s == CELL_UNFIRED && !ai.allIsLost() && !player.allIsLost())
				{
					if ( ai.thereIsShip( temp.x(), temp.y() ) )
						ai.state( temp.x(), temp.y() ) = CELL_HIT;
					else
						ai.state( temp.x(), temp.y() ) = CELL_MISSED;

					// ai shoots
					while ( player.state( temp = Vec2i( dbRND(9), dbRND(9) ) ) != CELL_UNFIRED )
						;
					if ( player.thereIsShip( temp.x(), temp.y() ) )
						player.state( temp.x(), temp.y() ) = CELL_HIT;
					else
						player.state( temp.x(), temp.y() ) = CELL_MISSED;
				}				
			}

			// back to main menu button
			if (ai.allIsLost() || player.allIsLost())
			{
				if ( returnToMain.withinBounds( dbMouse() ) )
				{
					return becauseCppWontLookFoward();
				}
			}
			
		}
		return this;
	}
	virtual void Display()
	{
		f_title.Paste(dbScreenWidth() / 2 - f_title.Width() / 2, 0);

		DarkGDKFont f;
		/*stringstream ss;
		Vec2i g = player.MouseToCell(dbMouse());
		ss << "(" << g.x() << ", " << g.y() << ")";
		
		f.Render(ss.str().c_str()).Paste(0, 10);*/

		Image i = f.Render("Computer");
		i.Paste(250 - i.Width() / 2, 117);
		i = f.Render("Player");
		i.Paste(774 - i.Width() / 2, 117);

		if (ai.allIsLost())
		{
			i = f.Render("YOU WIN!");
			i.Paste(dbScreenWidth() / 2 - i.Width() / 2, 100);
			returnToMain.Render();
		}
		else if (player.allIsLost())
		{
			i = f.Render("YOU LOSE!");
			i.Paste(dbScreenWidth() / 2 - i.Width() / 2, 100);
			returnToMain.Render();
		}

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

Menu* becauseCppWontLookFoward() { return new MainMenu; }

void DarkGDK()
{
	dbSetDisplayMode(1024, 768, 32);

	// fails on dual screen
	//dbSetWindowOff();

	dbSyncOn();

	dbRandomize(time(NULL));

	possibleShips.push_back(Ship(Image("battlestarGalactica2x4.png"), 0, 0, 4, 2));
	possibleShips.push_back(Ship(Image("battlestarGalactica4x2.png"), 0, 0, 2, 4));
	possibleShips.push_back(Ship(Image("mFalcon.png"), 0, 0, 2, 2));
	possibleShips.push_back(Ship(Image("mFalcon.png"), 0, 0, 2, 2));
	possibleShips.push_back(Ship(Image("starDestroyer1x5.png"), 0, 0, 5, 1));
	possibleShips.push_back(Ship(Image("starDestroyer5x1.png"), 0, 0, 1, 5));
	possibleShips.push_back(Ship(Image("ussEnterprise2x3.png"), 0, 0, 3, 2));
	possibleShips.push_back(Ship(Image("ussEnterprise3x2.png"), 0, 0, 2, 3));
	possibleShips.push_back(Ship(Image("xWing1x2.png"), 0, 0, 2, 1));
	possibleShips.push_back(Ship(Image("xWing2x1.png"), 0, 0, 1, 2));

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

	possibleShips.clear();
	
	return;
}
