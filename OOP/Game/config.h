#ifndef CONFIG_H
#define CONFIG_H

class Config{
private:
    int x = 5;
    int y = 5;

public:
    Config(){

    }

    Config(int x, int y) : x(x), y(y){

    }

    int get_x(){
        return x;
    }

    int get_y(){
        return y;
    }

    void set_x(int x){
        this->x = x;
    }

    void set_y(int y){
        this->y = y;
    }
};



#endif // CONFIG_H
