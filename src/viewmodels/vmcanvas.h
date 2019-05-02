#ifndef VMCANVAS_H
#define VMCANVAS_H

#include <util/goldenconevector.h>
#include <models/ishape.h>
#include <functional>

class VMCanvas
{
public:
    VMCanvas();

    void addShape(IShape shape);
    void removeShapeAtLayer(int layerID);
    void getShapeAtLayer(int layerID) const;
    void redrawCanvas();

private:
    GoldenConeVector<IShape*> shapesInMemory;
};

#endif // VMCANVAS_H
