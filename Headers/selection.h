#pragma once
#include<vector>
#include"rectangle.h"
#include<string>


class Seletcion{
public:

    Seletcion(std::string n, bool a = false):name(n), active(a){}
    void add(Rectangle r){
        rectangles.push_back(r);
    }
    std::string getName() { return name; }
    std::vector<Rectangle> getRectangles() {
        return rectangles;
    }
    bool getActive()const { return active; }
    void setActive(bool b) { active = b; }

private:

    std::vector<Rectangle> rectangles;
    std::string name;
    bool active;

};