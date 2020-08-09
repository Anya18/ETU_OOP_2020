#include "gamefield.h"
#include "unit.h"
#include "logging.h"
#include <string>
#include <fstream>
#include <ios>

Gamefield::Gamefield(Config *count) : count(count)
{
    std::string s = "создал новое поле размером ";
    s.append(std::to_string(count->get_x()));
    s.append("x");
    s.append(std::to_string(count->get_y()));
    s.append(" клеток");
    Logging::user_log(s);

    field = new Cell**[count->get_y()];
    for(int i = 0; i < count->get_y(); i++){
        field[i] = new Cell*[count->get_x()];
        for(int j = 0; j < count->get_x(); j++){
            if((i == 0 && j == 0) || (i ==  count->get_y()-1 && j == count->get_x()-1)){
                if(i == 0){
                    base_1 = new Base(count->get_x()*count->get_y(), i);
                    field[i][j] = base_1;
                }else {
                    base_2 = new Base(count->get_x()*count->get_y(), i);
                    field[i][j] = base_2;
                }
            }else{
                field[i][j] = new Cell;
            }
        }
    }
    field[0][1]->create_unit(1, base_1);
    base_1->add_hero();
    field[count->get_y()-1][count->get_x()-2]->create_unit(1, base_2);
    base_2->add_hero();
    add_lands();

    std::ofstream fout;
    fout.open("../log.txt", std::ios_base::trunc);
    if(!fout.is_open()){
        qDebug() << "Файл для записи лога не может быть открыт!";
        return;
    }
    fout.close();
}

Gamefield::~Gamefield(){
    for(int i = 0; i < count->get_y(); i++){
        for(int j = 0; j < count->get_x(); j++){
            delete field[i][j];
        }
        delete field[i];
    }
    delete field;
}

void Gamefield::add_lands(){
    coordinate river;
    river.y = 0;
    river.x = 3*count->get_x()/4;
    for(river.y; river.y<count->get_y() && river.x >= 0; river.y++){
        field[river.y][river.x]->add_land(new River);
        int i = river.x + 1 - rand()%3;
        if(i >= 0 && i!=river.x){
            field[river.y][i]->add_land(new River);
        }
        river.x = river.x - 1;
    }
    for(int i = 0; i < count->get_y(); i++){
        for(int j = 0; j < count->get_x(); j++){
            if(field[i][j]->get_land()==nullptr && field[i][j]->isBase()==false && i!=0 && i!=count->get_y()-1 && j!=1 && j!=count->get_x()-2){
                if(rand()%6 == 0){
                    field[i][j]->add_land(new Forest);
                }else{
                    if(rand()%6 == 0){
                        field[i][j]->add_land(new Mountain);
                    }
                }
            }
        }
    }
}

QPixmap Gamefield::getMap(){
    QImage *image = new QImage(count->get_x()*field[0][0]->get_cellSize(), count->get_y()*field[0][0]->get_cellSize(), QImage::Format_RGB666);
    QColor pixel;
    for(int i = 0; i < count->get_y(); i++){
        for(int j = 0; j < count->get_x(); j++){
            for(int y = 0; y < field[i][j]->get_cellSize(); y++){
                for(int x = 0; x < field[i][j]->get_cellSize(); x++){
                    pixel.setRed(field[i][j]->get_RGB(y, x).red);
                    pixel.setGreen(field[i][j]->get_RGB(y, x).green);
                    pixel.setBlue(field[i][j]->get_RGB(y, x).blue);
                    image->setPixel(x+j*field[i][j]->get_cellSize(), y+i*field[i][j]->get_cellSize(), pixel.rgb());
                }
            }
        }
    }
    QPixmap rezult = QPixmap::fromImage(*image);
    return rezult;
}

void Gamefield::del_light(){
    for(int i = 0; i < count->get_y(); i++){
        for(int j = 0; j < count->get_x(); j++){
            field[i][j]->make_dark();
        }
    }
}

void Gamefield::start_light(int x, int y){
    if(!field[y / field[0][0]->get_cellSize()][x / field[0][0]->get_cellSize()]->is_lighted()){
        del_light();
    }
}

void Gamefield::hero_event(int start_x, int start_y, int finish_x, int finish_y){
    coordinate start;
    start.x = start_x / field[0][0]->get_cellSize();
    start.y = start_y / field[0][0]->get_cellSize();
    coordinate finish;
    finish.x = finish_x / field[0][0]->get_cellSize();
    finish.y = finish_y / field[0][0]->get_cellSize();

    if(start.x == finish.x && start.y == finish.y){
        field[start.y][start.x]->clicked();
    }else{
        del_light();
        move_hero(start.x, start.y, finish.x, finish.y);
    }

}

void Gamefield::change_move_base(){
    base_1->change_move_flag();
    base_2->change_move_flag();
}

void Gamefield::add_hero(int type, int x, int y){
    if(type == 0){
        return;
    }
    coordinate cord;
    cord.x = x / field[0][0]->get_cellSize();
    cord.y = y / field[0][0]->get_cellSize();
    if(field[cord.y][cord.x]->isBase() || field[cord.y][cord.x]->get_land()!=nullptr){
        return;
    }
    if(base_1->get_move_flag() == true){
        if(base_1->get_hero_count() >= base_1->get_hero_max()){
            return;
        }
        field[cord.y][cord.x]->create_unit(type, base_1);
        base_1->add_hero();
    }else{
        if(base_2->get_hero_count() >= base_2->get_hero_max()){
            return;
        }
        field[cord.y][cord.x]->create_unit(type, base_2);
        base_2->add_hero();
    }
    change_move_base();
}

bool Gamefield::has_cell_unit(int x, int y){
    coordinate cord;
    cord.x = x / field[0][0]->get_cellSize();
    cord.y = y / field[0][0]->get_cellSize();
    return field[cord.y][cord.x]->has_unit();
}

bool Gamefield::better_type(int from_x, int from_y, int to_x, int to_y){
    if(field[from_y][from_x]->get_unit()->get_type() == BOW && field[to_y][to_x]->get_unit()->get_type() == AIRSHIP){
        return true;
    }
    if(field[from_y][from_x]->get_unit()->get_type() == CROSSBOW && field[to_y][to_x]->get_unit()->get_type() == PARAFOIL){
        return true;
    }
    if(field[from_y][from_x]->get_unit()->get_type() == AIRSHIP && field[to_y][to_x]->get_unit()->get_type() == CHIVALRY){
        return true;
    }
    if(field[from_y][from_x]->get_unit()->get_type() == PARAFOIL && field[to_y][to_x]->get_unit()->get_type() == LIGHTHORSE){
        return true;
    }
    if(field[from_y][from_x]->get_unit()->get_type() == CHIVALRY && field[to_y][to_x]->get_unit()->get_type() == BOW){
        return true;
    }
    if(field[from_y][from_x]->get_unit()->get_type() == LIGHTHORSE && field[to_y][to_x]->get_unit()->get_type() == CROSSBOW){
        return true;
    }
    return false;
}

void Gamefield::move_hero(int from_x, int from_y, int to_x, int to_y){
    if(field[to_y][to_x]->isBase()){
        return;
    }
    if(!field[from_y][from_x]->has_unit() ||
            (field[to_y][to_x]->get_land()!=nullptr && field[to_y][to_x]->get_land()->impact() >= field[from_y][from_x]->get_unit()->get_height()) ||
            abs(from_x-to_x)>field[from_y][from_x]->get_unit()->get_step() ||
            abs(from_y-to_y)>field[from_y][from_x]->get_unit()->get_step() ||
            field[from_y][from_x]->get_unit()->get_Base()->get_move_flag() == false){
        return;
    }
    if(field[to_y][to_x]->has_unit()){
        if(field[from_y][from_x]->get_unit()->get_level() == field[to_y][to_x]->get_unit()->get_level()){
            if(field[from_y][from_x]->get_unit()->get_type() == field[to_y][to_x]->get_unit()->get_type()){
                return;
            }
            if(better_type(from_x, from_y, to_x, to_y)){
                field[to_y][to_x]->get_unit()->get_Base()->delet_hero();
                field[to_y][to_x]->set_unit(field[from_y][from_x]->get_unit());
                field[from_y][from_x]->set_unit(nullptr);
                change_move_base();
                Logging::user_log("походил героем");
                Logging::hero_log("убил другого героя");
                return;
            }
        }
        if(field[from_y][from_x]->get_unit()->get_level() > field[to_y][to_x]->get_unit()->get_level()){
            field[to_y][to_x]->get_unit()->get_Base()->delet_hero();
            field[to_y][to_x]->set_unit(field[from_y][from_x]->get_unit());
            field[from_y][from_x]->set_unit(nullptr);
            change_move_base();
            Logging::user_log("походил героем");
            Logging::hero_log("убил другого героя");
        }
        return;
    }else{
        field[to_y][to_x]->set_unit(field[from_y][from_x]->get_unit());
        field[from_y][from_x]->set_unit(nullptr);
        change_move_base();
        Logging::user_log("походил героем");
        Logging::hero_log("сделал шаг");
    }
}

int Gamefield::count_hero_base1(){
    return base_1->get_hero_count();
}

int Gamefield::count_hero_base2(){
    return base_2->get_hero_count();
}

bool Gamefield::hero_level_up(int start_x, int start_y, int finish_x, int finish_y){
    coordinate start;
    start.x = start_x / field[0][0]->get_cellSize();
    start.y = start_y / field[0][0]->get_cellSize();
    coordinate finish;
    finish.x = finish_x / field[0][0]->get_cellSize();
    finish.y = finish_y / field[0][0]->get_cellSize();

    if(start.x != finish.x || start.y != finish.y){
        return false;
    }
    if(field[start.y][start.x]->has_unit() == false){
        return false;
    }
    if(field[start.y][start.x]->get_unit()->get_Base()->get_move_flag() == false){
        return false;
    }
    if(field[start.y][start.x]->get_unit()->get_level() != 4){
        field[start.y][start.x]->get_unit()->level_up();
    }else{
        Base* b = field[start.y][start.x]->get_unit()->get_Base();
        Unit *un;
        switch (field[start.y][start.x]->get_unit()->get_type()) {
        case BOW:
            un = new Unit_crossbow;
            break;
        case AIRSHIP:
            un = new  Unit_parafoil;
            break;
        case CHIVALRY:
            un = new Unit_lighthorse;
            break;
        }
        un->set_Base(b);
        field[start.y][start.x]->set_unit(un);
    }
    change_move_base();
    Logging::user_log("поднял уровень героя");
    return true;
}

std::string* Gamefield::show_info(){
    if(base_1->is_lighted()){
        std::string* s = new std::string;
        s->append("База №");
        s->append(std::to_string(base_1->get_base_id()));
        s->append(",    количество героев у базы - ");
        s->append(std::to_string(base_1->get_hero_count()));
        s->append(",    максимальное количество героев - ");
        s->append(std::to_string(base_2->get_hero_max()));
        return s;
    }
    if(base_2->is_lighted()){
        std::string* s = new std::string;
        s->append("База №");
        s->append(std::to_string(base_2->get_base_id()));
        s->append(",    количество героев у базы - ");
        s->append(std::to_string(base_2->get_hero_count()));
        s->append(",    максимальное количество героев - ");
        s->append(std::to_string(base_2->get_hero_max()));
        return s;
    }
    for(int i = 0; i < count->get_y(); i++){
        for(int j = 0; j < count->get_x(); j++){
            if(field[i][j]->has_unit() && field[i][j]->is_lighted()){
                std::string* s = new std::string;
                s->append("Информация о герое: тип - ");
                switch (field[i][j]->get_unit()->get_type()) {
                case BOW:
                    s->append("стрелок из лука,");
                    break;
                case CROSSBOW:
                    s->append("стрелок из арбалета,");
                    break;
                case AIRSHIP:
                    s->append("маленький дракон,");
                    break;
                case PARAFOIL:
                    s->append("большой дракон,");
                    break;
                case CHIVALRY:
                    s->append("всадник с мечом,");
                    break;
                case LIGHTHORSE:
                    s->append("всадник с копьем,");
                    break;
                }
                s->append("   уровень - ");
                s->append(std::to_string(field[i][j]->get_unit()->get_level()));
                s->append(",   максимальный шаг - ");
                s->append(std::to_string(field[i][j]->get_unit()->get_step()));
                s->append(",   принадлежит базе №");
                s->append(std::to_string(field[i][j]->get_unit()->get_Base()->get_base_id()));
                return s;
            }
            if(!field[i][j]->has_unit() && field[i][j]->get_land()!=nullptr && field[i][j]->is_lighted()){
                std::string* s = new std::string;
                switch (field[i][j]->get_land()->impact()) {
                case 1:
                    s->append("Река,  войти  в  которою  могут:  стрелок  из  арбалета,  маленький  дракон,  большой  дракон,  всадник  с  мечом,  всадник  с  копьем");
                    break;
                case 2:
                    s->append("Лес,  войти  в  который  могут:  маленький  дракон,  большой  дракон,  всадник  с  копьем");
                    break;
                case 3:
                    s->append("Гора,  подняться  на  которую  может  толькой  большой  дракон");
                    break;
                }
                return s;
            }
        }
    }
    return nullptr;
}

int Gamefield::lose(){
    if(base_1->get_hero_count() == 0){
        return 1;
    }
    if(base_2->get_hero_count() == 0){
        return 2;
    }
    return  0;
}
