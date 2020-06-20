#pragma once
#include<utility>




class Rectangle {
public:
    Rectangle(int i, int j, int l, int w): lenght(l), width(w){
        position.first = i;
        position.second = j;
    }
    std::pair<int, int> getPos() { return position; }
    int getLenght() { return lenght; }
    int getWidth() { return width; }
private:
    std::pair<int, int> position;
    int lenght;
    int width;
};