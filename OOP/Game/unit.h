#ifndef UNIT_H
#define UNIT_H

#include "cell.h"
#include "base.h"
#include "logging.h"

#define BOW 1
#define CROSSBOW 2
#define AIRSHIP 3
#define PARAFOIL 4
#define CHIVALRY 5
#define LIGHTHORSE 6

class Base;
class Cell;

class Unit
{
public:
    Unit();
    Unit(const Unit& original){
        base = original.base;
        level = original.level;
        type = original.type;
        height = original.height;
        step = original.step;
    }
    Unit(Unit&& other){
        base = other.base;
        other.base = nullptr;
        level = other.level;
        other.level = 0;
        type = other.type;
        other.type = 0;
        height = other.height;
        other.height = 0;
        step = other.step;
        other.step = 0;
    }
    void set_Base(Base* b);
    Base* get_Base();
    int get_type();
    int get_step();
    int get_level();
    int get_height();
    void level_up();

protected:
    int level = 1;
    Base* base = nullptr;
    int type;
    int height = 1;
    int step = 1;
};

//____________________________________________________________________________

class Unit_shooter : public Unit //Стрелки
{
public:
    Unit_shooter(){
    }
};

class Unit_bow : public Unit_shooter //Лук(+здоровье)
{
public:
    Unit_bow(){
        type = BOW;
        Logging::user_log("создал героя-стрелка с луком");
    }
};

class Unit_crossbow : public Unit_shooter//Арбалет(+скорость)
{
public:
    Unit_crossbow(){
        level = 5;
        type = CROSSBOW;
        step = 3;
        height = 2;
        Logging::user_log("создал героя-стрелка с арбалетом");
    }
};

//---------------------------------------------------------------------

class Unit_volatile : public Unit //Крылатые
{
public:
    Unit_volatile(){
    }
};

class Unit_airship : public Unit_volatile //воздушный шар(+здоровье)
{
public:
    Unit_airship(){
        type = AIRSHIP;
        height = 3;
        Logging::user_log("создал маленького героя-дракона");
    }
};

class Unit_parafoil : public Unit_volatile //параплан (+скорость)
{
public:
    Unit_parafoil(){
        level = 5;
        type = PARAFOIL;
        height = 5;
        step = 3;
        Logging::user_log("создал большого героя-дракона");
    }
};

//---------------------------------------------------------------------

class Unit_cavalry : public Unit //Конница
{
public:
    Unit_cavalry(){
    }
};

class Unit_chivalry : public Unit_cavalry //тяжелые рыцари(+здоровье)
{
public:
    Unit_chivalry(){
        type = CHIVALRY;
        height = 2;
        step = 2;
        Logging::user_log("создал героя-всадника с мечом");
    }
};

class Unit_lighthorse : public Unit_cavalry //легкая конница(+сорость)
{
public:
    Unit_lighthorse(){
        level = 5;
        type = LIGHTHORSE;
        height = 3;
        step = 5;
        Logging::user_log("создал героя-всадника с копьем");
    }
};

//_________________________________________________________________________


class UnitFactory
{
public:
    virtual Unit* create_Unit() = 0;
    ~UnitFactory(){};
};


class Unit_shooter_Factory : public UnitFactory
{
public:
    Unit* create_Unit(){
        return new Unit_bow;
    }
};

class Unit_volatile_Factory : public UnitFactory
{
public:
    Unit* create_Unit(){
        return new Unit_airship;
    }
};

class Unit_cavalry_Factory : public UnitFactory
{
public:
    Unit* create_Unit(){
        return new Unit_chivalry;
    }
};


#endif // UNIT_H
