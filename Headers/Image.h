#pragma once
#include"Pixel.h"
#include"selection.h"
#include"Operation.h"

class Layer;

class Image {
public:
    friend Layer;

    void addLayer(Layer* l);
    void addSelection(Seletcion* s);
    void addRectangleInSelection(Rectangle r);
    Layer* setToFirstALayer();
    void combinateImage();
    void writeImage(std::string s);
    std::vector<Layer*> getLayers() { return layers; }
    Seletcion* getSelecetion() { return selection; }
    void extendAllLayers(int, int);
    void findMaxLayer();
    void setOperation(Operation* o) {
        if (operation) delete operation;
        operation = o;
        o->operate();
    }
    Operation* getOperation()const { return operation; }
    void LoadFromTFile(std::string s);
    void writeComposite(std::string s);
    void deleteSelection() { delete selection; selection = nullptr; }
    void deleteLayer(int i) { layers.erase(layers.begin() + i); }
    ~Image();

private:
    std::vector<Layer*> layers;
    Seletcion* selection = nullptr;
    static Layer* mergeLayers;
    Operation* operation = nullptr;
};