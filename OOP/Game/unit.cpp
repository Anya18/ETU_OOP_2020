#include "unit.h"

Unit::Unit()
{

}

void Unit::set_Base(Base* b){
    if(base == nullptr){
        base = b;
    }
}

Base* Unit::get_Base(){
    return base;
}

int Unit::get_type(){
    return type;
}

int Unit::get_step(){
    return step;
}

int Unit::get_level(){
    return level;
}

int Unit::get_height(){
    return height;
}

void Unit::level_up(){
    level++;
}
