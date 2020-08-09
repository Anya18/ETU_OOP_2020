#ifndef BASE_H
#define BASE_H

#include "cell.h"


class Base : public Cell
{
public:
    Base(int cell_count, int x);
    void make_dark();
    bool get_move_flag();
    void change_move_flag();
    int get_base_id();
    int get_hero_max();
    int get_hero_count();
    void add_hero();
    void delet_hero();

private:
    int base_id = 0;
    bool move_flag = false;
    int hero_count = 0;
    unsigned int hero_max = 0;
};

#endif // BASE_H
