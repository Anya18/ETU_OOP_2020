#include "lands.h"

Lands::Lands()
{

}

River::River(){
    index = 1;
}

int River::impact(){
    return index;
}


Forest::Forest(){
    index = 2;
}
int Forest::impact(){
    return index;
}


Mountain::Mountain(){
    index = 3;
}

int Mountain::impact(){
    return index;
}
