#pragma once
#include"Formater.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<regex>
#include"Pixel.h"

class Layer;

class PAMHeader {
public:
    friend class PAM;
    PAMHeader(int w, int h, int d, int m, std::string t, std::string tt) :width(w),
        height(h), depth(d), type(t), tuplType(tt), maxval(m) {}
    PAMHeader() = default;

    friend std::ostream& operator<<(std::ostream& os, const PAMHeader& p) {
        os << p.type << std::endl;
        os << "WIDTH " << p.width << std::endl;
        os << "HEIGHT " << p.height << std::endl;
        os << "DEPTH " << p.depth << std::endl;
        os << "MAXVAL " << p.maxval << std::endl;
        os << "TUPLTYPE " << p.tuplType << std::endl;
        return os << "ENDHDR" << std::endl;
    }
private:
    int width;
    int height;
    int depth;
    int maxval;
    std::string tuplType;
    std::string type;
};

class PAM : public Formater{
public:
    PAM(int w, int h): header(w,h, 4, 255, "P7", "RGB_ALPHA"){}
    PAM() = default;
    void write(const char* file, Layer*)override;
    void read(const char*, Layer*)override;

private:
    PAMHeader header;
    std::vector<uint8_t> data;
};

