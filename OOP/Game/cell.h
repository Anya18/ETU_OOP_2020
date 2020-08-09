#ifndef CELL_H
#define CELL_H

#include "RGB.h"
#include "lands.h"

class Unit;
class Base;

class Cell
{
public:
    Cell();
    virtual ~Cell();
    int get_cellSize();
    RGB get_RGB(int y, int x);
    void make_lighted();
    virtual void make_dark();
    void clicked();
    bool is_lighted();
    bool isBase();
    void create_unit(int type, Base* base);
    bool has_unit();
    Unit* get_unit();
    void set_unit(Unit* other);
    void cell_painter(int type, int base_id);
    void cell_repaint();
    void add_land(Lands* land);
    Lands* get_land();

private:
    Lands* land = nullptr;
    Unit *unit = nullptr;

protected:
    bool is_base = false;
    bool is_selected = false;
    int cell_size = 50;
    RGB **cell = nullptr;
};

#endif // CELL_H
