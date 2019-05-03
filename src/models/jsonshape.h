#ifndef JSONSHAPE_H
#define JSONSHAPE_H

#include "ishape.h"
#include "shaperect.h"

#include <QJsonObject>
#include <QString>
#include <QDebug>

struct JSONShape
{
    static const QString keyShapeID;
    static const QString keyShapeType;
    static const QString keyDimens;
    static const QString keyPenClr;
    static const QString keyPenWidth;
    static const QString keyPenStyle;

    static const QString keyPenCapStyle;
    static const QString keyPenJoinStyle;
    static const QString keyBrushClr;
    static const QString keyBrushStyle;

    static QJsonObject toJSON(const IShape* shapeToSerialize);

    template<typename X>
    static IShape* fromJSON(const QJsonObject &json)
    {
        //Defaults
        int id = -1;
        IShape::ShapeType shType = IShape::ShapeType::NoShape;
        QVector<int> dimens = QVector<int>();
        QColor penClr = Qt::GlobalColor::white;
        int penWidth = 1;
        Qt::PenStyle penStyle = Qt::PenStyle::SolidLine;
        Qt::PenCapStyle capStyle = Qt::PenCapStyle::SquareCap;
        Qt::PenJoinStyle joinStyle = Qt::PenJoinStyle::BevelJoin;
        QColor brushClr = Qt::GlobalColor::white;
        Qt::BrushStyle brushStyle = Qt::BrushStyle::SolidPattern;

        //Shape type has to exist to init the shape, otherwise die
        if (!json.contains(keyShapeType) || !json[keyShapeType].isString()) {return nullptr;}

        //Grab the shape type
        shType = parseShapeTypeFrom(json[keyShapeType].toString());

        //Die if no shape
        if (shType == IShape::ShapeType::NoShape) {return nullptr;}

        //Init the object
        switch (shType)
        {
//        case IShape::ShapeType::Line:
//            return new Line?
//        case IShape::ShapeType::Text:
//            return new Text?
//        case IShape::ShapeType::Ellipse:
//            return new ShapeElipse?
//        case IShape::ShapeType::Polygon:
//            return
//        case IShape::ShapeType::Polyline:
//            return
//        case IShape::ShapeType::Rectangle:
//            return new ShapeRect()
        case IShape::ShapeType::NoShape:
            return nullptr;
        default:
                qDebug() << "";
                return nullptr;
        }
    }
private:
    static IShape::ShapeType parseShapeTypeFrom(QString rawJSON)
    {
        if (rawJSON == "Polyline") {return IShape::ShapeType::Polyline;}
        else if (rawJSON == "Line") {return IShape::ShapeType::Line;}
        else if (rawJSON == "Polygon") {return IShape::ShapeType::Polygon;}
//        else if (rawJSON == "Triangle") {return IShape::ShapeType::Triangle;}
        else if (rawJSON == "Rectangle") {return IShape::ShapeType::Rectangle;}
//        else if (rawJSON == "Square") {return IShape::ShapeType::Square;}
        else if (rawJSON == "Ellipse") {return IShape::ShapeType::Ellipse;}
//        else if (rawJSON == "Circle") {return IShape::ShapeType::Circle;}
        else if (rawJSON == "Text") {return IShape::ShapeType::Text;}
        else
        {
            qDebug() << "Unsupported shape type: " << rawJSON;
            return IShape::ShapeType::NoShape;
        }
    }
};
const QString JSONShape::keyShapeID = "ShapeId";
const QString JSONShape::keyShapeType = "ShapeType";
const QString JSONShape::keyDimens = "ShapeDimensions";
const QString JSONShape::keyPenClr = "PenColor";
const QString JSONShape::keyPenWidth = "PenWidth";
const QString JSONShape::keyPenStyle = "PenStyle";
const QString JSONShape::keyPenCapStyle = "PenCapStyle";
const QString JSONShape::keyPenJoinStyle = "PenJoinStyle";
const QString JSONShape::keyBrushClr = "BrushColor";
const QString JSONShape::keyBrushStyle = "BrushStyle";

#endif // JSONSHAPE_H
