#include "base.h"
#include <cmath>
#include <QDebug>

Base::Base(int cell_count, int x)
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
                cell[i][j].green = 0;
                cell[i][j].blue = 51;
            }
        }
    }
    is_base = true;
    hero_max = cell_count/4;
    if(x == 0){
        base_id = 1;
        move_flag = true;
    }else{
        base_id = 2;
        move_flag = false;
    }
    int r = cell_size/2;
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

void Base::make_dark(){
    for(int i = 0; i < cell_size; i++){
        for(int j = 0; j < cell_size; j++){
            if((i>=1 && i<=2) || (i>=cell_size-3 && i<=cell_size-2) ||(j>=1 && j<=2) || (j>=cell_size-3 && j<=cell_size-2)){
                cell[i][j].red = 153;
                cell[i][j].green = 0;
                cell[i][j].blue = 51;
            }
            if(i == 0 || j == 0 || i == cell_size-1 || j == cell_size-1){
                cell[i][j].red = 102;
                cell[i][j].green = 102;
                cell[i][j].blue = 102;
            }
        }
    }
    is_selected = false;
}

bool Base::get_move_flag(){
    return  move_flag;
}

void Base::change_move_flag(){
    move_flag = !move_flag;
}

int Base::get_base_id(){
    return base_id;
}

int Base::get_hero_max(){
    return hero_max;
}

int Base::get_hero_count(){
    return hero_count;
}

void Base::add_hero(){
    hero_count++;
}

void Base::delet_hero(){
    hero_count--;
}
