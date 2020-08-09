#include "cell.h"
#include "unit.h"

#include <QDebug>
#include <cmath>

Cell::Cell()
{
    cell = new RGB*[cell_size];
    for(int i = 0; i < cell_size; i++){
        cell[i] = new RGB[cell_size];
        for(int j = 0; j < cell_size; j++){
            if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                cell[i][j].red = 102;
                cell[i][j].green = 102;
                cell[i][j].blue = 102;
            }else{
                cell[i][j].red = 153;
                cell[i][j].green = 153;
                cell[i][j].blue = 204;
            }
        }
    }
}


int Cell::get_cellSize(){
    return cell_size;
}

RGB Cell::get_RGB(int y, int x){
    return cell[y][x];
}

void Cell::make_lighted(){
    for(int i = 0; i < cell_size; i++){
        for(int j = 0; j < cell_size; j++){
            if((i>=0 && i<=2) || (i>=cell_size-3 && i<=cell_size-1) ||(j>=0 && j<=2) || (j>=cell_size-3 && j<=cell_size-1)){
                cell[i][j].red = 0;
                cell[i][j].green = 255;
                cell[i][j].blue = 0;
            }
        }
    }
    is_selected = true;
}

void Cell::make_dark(){
    if(get_land() == nullptr){
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if((i>=1 && i<=2) || (i>=cell_size-3 && i<=cell_size-2) ||(j>=1 && j<=2) || (j>=cell_size-3 && j<=cell_size-2)){
                    cell[i][j].red = 153;
                    cell[i][j].green = 153;
                    cell[i][j].blue = 204;
                }
                if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 102;
                }
            }
        }
    }else{
        switch (get_land()->impact()) {
        case 1:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if((i>=1 && i<=2) || (i>=cell_size-3 && i<=cell_size-2) ||(j>=1 && j<=2) || (j>=cell_size-3 && j<=cell_size-2)){
                        cell[i][j].red = 102;
                        cell[i][j].green = 204;
                        cell[i][j].blue = 255;
                    }
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }
                }
            }
            break;
        case 2:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if((i>=1 && i<=2) || (i>=cell_size-3 && i<=cell_size-2) ||(j>=1 && j<=2) || (j>=cell_size-3 && j<=cell_size-2)){
                        cell[i][j].red = 153;
                        cell[i][j].green = 204;
                        cell[i][j].blue = 153;
                    }
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }
                }
            }
            break;
        case 3:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if((i>=1 && i<=2) || (i>=cell_size-3 && i<=cell_size-2) ||(j>=1 && j<=2) || (j>=cell_size-3 && j<=cell_size-2)){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 153;
                    }
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }
                }
            }
            break;
        }
    }
    is_selected = false;
}


void Cell::clicked(){
    if(is_selected){
        make_dark();
    }else{
        make_lighted();
    }
}

bool Cell::is_lighted(){
    return is_selected;
}

bool Cell::isBase(){
    return is_base;
}

void Cell::cell_painter(int type, int base_id){
    int r = cell_size/2;
    switch (type) {
    case 1:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 51;
                    cell[i][j].green = 204;
                    cell[i][j].blue = 0;
                }
            }
        }
        break;
    case 2:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 153;
                    cell[i][j].green = 255;
                    cell[i][j].blue = 0;
                }
            }
        }
        break;
    case 3:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 255;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 51;
                }
            }
        }
        break;
    case 4:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 255;
                    cell[i][j].green = 153;
                    cell[i][j].blue = 51;
                }
            }
        }
        break;
    case 5:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 0;
                    cell[i][j].green = 0;
                    cell[i][j].blue = 255;
                }
            }
        }
        break;
    case 6:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-10, 2)){
                    cell[i][j].red = 102;
                    cell[i][j].green = 0;
                    cell[i][j].blue = 204;
                }
            }
        }
        break;
    default:
        return;
    }
    switch (base_id) {
    case 1:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-20, 2)){
                    cell[i][j].red = 255;
                    cell[i][j].green = 255;
                    cell[i][j].blue = 255;
                }
            }
        }
        break;
    case 2:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(pow(i-r, 2) + pow(j-r, 2) < pow(r-20, 2)){
                    cell[i][j].red = 0;
                    cell[i][j].green = 0;
                    cell[i][j].blue = 0;
                }
            }
        }
        break;
    default:
        break;
    }
}

void Cell::cell_repaint(){
    if(get_land() == nullptr){
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 102;
                }else{
                    cell[i][j].red = 153;
                    cell[i][j].green = 153;
                    cell[i][j].blue = 204;
                }
            }
        }
    }else {
        switch (get_land()->impact()) {
        case 1:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }else{
                        cell[i][j].red = 102;
                        cell[i][j].green = 204;
                        cell[i][j].blue = 255;
                    }
                }
            }
            break;
        case 2:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }else{
                        cell[i][j].red = 153;
                        cell[i][j].green = 204;
                        cell[i][j].blue = 153;
                    }
                }
            }
            break;
        case 3:
            for(int i = 0; i < cell_size; i++){
                for(int j = 0; j < cell_size; j++){
                    if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 102;
                    }else{
                        cell[i][j].red = 102;
                        cell[i][j].green = 102;
                        cell[i][j].blue = 153;
                    }
                }
            }
            break;
        }
    }
}

void Cell::create_unit(int type, Base* base){
    if(unit != nullptr){
        return;
    }
    UnitFactory* fact;
    switch (type) {
    case 1:
        fact = new Unit_shooter_Factory;
        break;
    case 2:
        fact = new Unit_volatile_Factory;
        break;
    case 3:
        fact = new Unit_cavalry_Factory;
        break;
    default:
        return;
    }
    unit = fact->create_Unit();
    unit->set_Base(base);
    cell_painter(unit->get_type(), base->get_base_id());
}

bool Cell::has_unit(){
    if(unit != nullptr)
        return true;
    else
        return false;
}

Unit* Cell::get_unit(){
    return unit;
}

void Cell::set_unit(Unit *other){
    delete unit;
    if(other == nullptr){
        unit = nullptr;
        cell_repaint();
    }
    else{
        unit = new Unit(*other);
        cell_painter(unit->get_type(), unit->get_Base()->get_base_id());
    }
}

void Cell::add_land(Lands *land){
    this->land = land;
    switch (get_land()->impact()) {
    case 1:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 102;
                }else{
                    cell[i][j].red = 102;
                    cell[i][j].green = 204;
                    cell[i][j].blue = 255;
                }
            }
        }
        break;
    case 2:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 102;
                }else{
                    cell[i][j].red = 153;
                    cell[i][j].green = 204;
                    cell[i][j].blue = 153;
                }
            }
        }
        break;
    case 3:
        for(int i = 0; i < cell_size; i++){
            for(int j = 0; j < cell_size; j++){
                if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 102;
                }else{
                    cell[i][j].red = 102;
                    cell[i][j].green = 102;
                    cell[i][j].blue = 153;
                }
            }
        }
        break;
    }
}

Lands* Cell::get_land(){
    return land;
}

Cell::~Cell(){
    for(int i = 0; i < cell_size; i++){
        delete cell[i];
    }
    delete cell;
}
