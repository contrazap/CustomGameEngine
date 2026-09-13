#include <iostream>
#include <string>

struct TankState
{
    std::string name;
    int x;
    int y;
};

void moveTank(TankState& tank, int deltaX, int deltaY)
{
    tank.x += deltaX;
    tank.y += deltaY;
}

void printTankState(const TankState& tank)
{
    std::cout << tank.name << " is at (" << tank.x << ", " << tank.y << ")\n";
}

int main()
{
    TankState tank{"Player", 2, 3};

    printTankState(tank);
    moveTank(tank, 1, 0);
    printTankState(tank);
    moveTank(tank, -2, -1);
    printTankState(tank);

    return 0;
}
