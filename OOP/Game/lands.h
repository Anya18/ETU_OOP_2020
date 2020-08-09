#ifndef LANDS_H
#define LANDS_H


class Lands
{
protected:
    int index;
public:
    Lands();
    virtual int impact() = 0;

};

class River : public Lands
{
public:
    River();
    int impact();
};


class Forest : public Lands
{
public:
    Forest();
    int impact();
};


class Mountain : public Lands
{
public:
    Mountain();
    int impact();
};

#endif // LANDS_H
