#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QPixmap>
#include <string>

#include "config.h"
#include "cell.h"
#include "base.h"
#include "RGB.h"
#include "mgraphicsview.h"

class Gamefield
{
public:
    Gamefield(Config *count);
    ~Gamefield();

    QPixmap getMap();
    void hero_event(int start_x, int start_y, int finish_x, int finish_y);
    void del_light();
    void start_light(int x, int y);
    void add_hero(int type, int x, int y);
    bool has_cell_unit(int x, int y);
    void move_hero(int from_x, int from_y, int to_x, int to_y);
    void change_move_base();
    int count_hero_base1();
    int count_hero_base2();
    bool better_type(int from_x, int from_y, int to_x, int to_y);
    bool hero_level_up(int start_x, int start_y, int finish_x, int finish_y);
    std::string* show_info();
    int lose();
    void add_lands();

private:
    Config *count = nullptr;
    Cell*** field = nullptr;
    Base* base_1 = nullptr;
    Base* base_2 = nullptr;
};

#endif // GAMEFIELD_H
