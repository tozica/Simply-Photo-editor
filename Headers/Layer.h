#pragma once
#include"Pixel.h"
#include"Formater.h"
#include"Bmp.h"
#include"PAM.h"
#include<string>
#include<regex>
#include"Image.h"
#include"Errors.h"



class Layer{
public:
    friend Formater;
    friend BMP;
    friend PAM;
    friend Image;
    Layer(std::string s);
    Layer(int h, int w);
    Layer();
    void setActive(bool b) { active = b; }
    void setVisible(bool b) { visible = b; }
    void setOpacity(double i) { opacity = i; }
    bool getVisible()const { return visible; }
    bool getActive()const { return active; }
    double getOpacity()const { return opacity; }
    std::vector<Pixel*> getData() { return pixelData; }
    int getH()const { return hight; }
    int getW()const { return width; }
    static int getHS() { return hightS; }
    static int getWS() { return widthS; }
    void extendLayer(int h, int w, int oldW, int oldH);
private:
    std::string path;
    int hight, width;
    static int hightS, widthS;
    double opacity = 0.5;
    std::vector<Pixel*> pixelData;
    bool active = true;
    bool visible = true;
    
    

};
