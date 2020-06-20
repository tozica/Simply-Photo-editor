#pragma once
class Layer;

class Formater{

public:
    Formater() = default;
    virtual void read(const char* file, Layer *l) = 0;
    virtual void write(const char* file, Layer *l) = 0;

};