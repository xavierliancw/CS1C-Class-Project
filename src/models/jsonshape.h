#ifndef JSONSHAPE_H
#define JSONSHAPE_H

#include "ishape.h"
#include "shaperect.h"
#include "shapesquare.h"
#include "shapepolygon.h"
#include "shapepolyline.h"
#include "shapeline.h"
#include "shapeellipse.h"
#include "shapecircle.h"

#include <QJsonObject>
#include <QString>
#include <QDebug>
#include <QJsonArray>

struct JSONShape
{
    static QJsonObject toJSON(const IShape* shapeToSerialize)
    {
        QJsonObject newJson;

        newJson[keyShapeID] = shapeToSerialize->id;
        newJson[keyShapeType] = serializedShapeTypeFrom(shapeToSerialize->getShape());
        newJson[keyDimens] = serializedDimensionsFrom(shapeToSerialize);
        newJson[keyPenClr] = shapeToSerialize->pen.color().name();
        newJson[keyPenWidth] = shapeToSerialize->pen.width();
        newJson[keyPenStyle] = serializedQtPenStyleFrom(shapeToSerialize->pen.style());
        newJson[keyPenCapStyle] = serializedQtCapStyleFrom(shapeToSerialize->pen.capStyle());
        newJson[keyPenJoinStyle] = serializedQtJoinStyleFrom(shapeToSerialize->pen.joinStyle());
        newJson[keyBrushClr] = shapeToSerialize->brush.color().name();
        newJson[keyBrushStyle] = serializedQtBrushStyleFrom(shapeToSerialize->brush.style());

        return newJson;
    }

    static IShape* fromJSON(const QJsonObject &json)
    {
        //Defaults
        int id = -1;
        IShape::ShapeType shType = IShape::ShapeType::NoShape;
        QJsonArray rawJSONDimens;
        QVector<int> dimens;
        QColor penClr = Qt::GlobalColor::white;
        int penWidth = 1;
        Qt::PenStyle penStyle = Qt::PenStyle::SolidLine;
        Qt::PenCapStyle capStyle = Qt::PenCapStyle::SquareCap;
        Qt::PenJoinStyle joinStyle = Qt::PenJoinStyle::BevelJoin;
        QColor brushClr = Qt::GlobalColor::white;
        Qt::BrushStyle brushStyle = Qt::BrushStyle::SolidPattern;
        IShape* retShape = nullptr;
        QString rawShapeTypeJSON;

        //Shape type has to exist to init the shape, otherwise die
        if (!json.contains(keyShapeType) || !json[keyShapeType].isString()) {return retShape;}

        //Grab the shape type
        rawShapeTypeJSON = json[keyShapeType].toString();
        shType = deserializeShapeTypeFrom(rawShapeTypeJSON);

        //Grab dimens, or die
        if (!json.contains(keyDimens) || !json[keyDimens].isArray())
        {
            qDebug() << "JSON parse error. Dimensions are not stored in an array";
            return nullptr;
        }
        rawJSONDimens = json[keyDimens].toArray();

        //Map to ints
        foreach (const QJsonValue& value, rawJSONDimens) {dimens.append(value.toInt());}

        //Init the specific shape
        retShape = dynmaicallyIinitializedShapeGiven(shType, rawShapeTypeJSON, dimens);

        if (retShape == nullptr) {return retShape;}

        //Parse other properties if they're there
        if (json.contains(keyShapeID))
        {
            id = json[keyShapeID].toInt();
        }
        if (json.contains(keyPenClr) && json[keyPenClr].isString())
        {
            penClr = deserializeQtColorFrom(json[keyPenClr].toString(), penClr);
        }
        if (json.contains(keyPenWidth))
        {
            penWidth = json[keyPenWidth].toInt();
        }
        if (json.contains(keyPenStyle) && json[keyPenStyle].isString())
        {
            penStyle = deserializeQtPenStyleFrom(json[keyPenStyle].toString(), penStyle);
        }
        if (json.contains(keyPenCapStyle) && json[keyPenCapStyle].isString())
        {
            capStyle = deserializeQtCapStyleFrom(json[keyPenCapStyle].toString(), capStyle);
        }
        if (json.contains(keyPenJoinStyle) && json[keyPenJoinStyle].isString())
        {
            joinStyle = deserializeQtJoinStyleFrom(json[keyPenJoinStyle].toString(), joinStyle);
        }
        if (json.contains(keyBrushClr) && json[keyBrushClr].isString())
        {
            brushClr = deserializeQtColorFrom(json[keyBrushClr].toString(), brushClr);
        }
        if (json.contains(keyBrushStyle) && json[keyBrushStyle].isString())
        {
            brushStyle = deserializeBrushStyleFrom(json[keyBrushStyle].toString(), brushStyle);
        }
        //Init the other properties
        retShape->id = id;
        retShape->pen.setColor(penClr);
        retShape->pen.setWidth(penWidth);
        retShape->pen.setStyle(penStyle);
        retShape->pen.setCapStyle(capStyle);
        retShape->pen.setJoinStyle(joinStyle);
        retShape->brush.setColor(brushClr);
        retShape->brush.setStyle(brushStyle);
        return retShape;
    }
private:
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
    static const QString keyText;

    static IShape* dynmaicallyIinitializedShapeGiven(const IShape::ShapeType shType,
                                                     const QString rawShapeTypeJSONStr,
                                                     const QVector<int> dimens)
    {
        IShape* retShape = nullptr;
        bool badDimensEncountered = true;
        bool unsupportedShapeFound = false;
        bool noShapeError = false;

        switch (shType)
        {
        case IShape::ShapeType::Line:
            if (dimens.size() == 4)
            {
                retShape = new ShapeLine(dimens[0], dimens[1], dimens[2], dimens[3]);
                badDimensEncountered = false;
            }
            break;
        //        case IShape::ShapeType::Text:
        //            retShape = new Text?
        case IShape::ShapeType::Ellipse:
            if (dimens.size() == 4)
            {
                retShape = new ShapeEllipse(shType, dimens[0], dimens[1], dimens[2], dimens[3]);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::Circle:
            if (dimens.size() == 3)
            {
                retShape = new ShapeCircle(dimens[0], dimens[1], dimens[2]);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::Polygon:
            if (dimens.size() > 2)
            {
                QVector<QPoint> polyDimens;
                int x = 0;
                while (x < dimens.size())
                {
                    polyDimens.push_back(QPoint(dimens[x], dimens[x + 1]));
                    x = x + 2;
                }
                retShape = new ShapePolygon(polyDimens);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::Polyline:
            if (dimens.size() > 4)
            {
                QVector<QPoint> polyDimens;
                int x = 0;
                while (x < dimens.size())
                {
                    polyDimens.push_back(QPoint(dimens[x], dimens[x + 1]));
                    x = x + 2;
                }
                retShape = new ShapePolyLine(IShape::ShapeType::Polyline, polyDimens);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::Rectangle:
            if (dimens.size() == 4)
            {
                retShape = new ShapeRect(shType, dimens[0], dimens[1], dimens[2], dimens[3]);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::Square:
            if (dimens.size() == 3)
            {
                retShape = new ShapeSquare(dimens[0], dimens[1], dimens[2]);
                badDimensEncountered = false;
            }
            break;
        case IShape::ShapeType::NoShape:
            badDimensEncountered = false;
            break;
        default:
            unsupportedShapeFound = true;
            break;
        }
        if (badDimensEncountered)
        {
            qDebug() << "Bad JSON formatting. Found " << dimens.size() <<
                        " element(s) in json array for shape type: " << rawShapeTypeJSONStr;
        }
        else if (unsupportedShapeFound)
        {
            qDebug() << "Unsupported JSON shape: " << rawShapeTypeJSONStr;
        }
        else if (noShapeError)
        {
            qDebug() << "Tried to instantiate no shape from JSON.";
        }
        return retShape;
    }

    static IShape::ShapeType deserializeShapeTypeFrom(const QString rawJSON)
    {
        if (rawJSON == "Polyline") {return IShape::ShapeType::Polyline;}
        else if (rawJSON == "Line") {return IShape::ShapeType::Line;}
        else if (rawJSON == "Polygon") {return IShape::ShapeType::Polygon;}
        else if (rawJSON == "Triangle") {return IShape::ShapeType::Triangle;}
        else if (rawJSON == "Rectangle") {return IShape::ShapeType::Rectangle;}
        else if (rawJSON == "Square") {return IShape::ShapeType::Square;}
        else if (rawJSON == "Ellipse") {return IShape::ShapeType::Ellipse;}
        else if (rawJSON == "Circle") {return IShape::ShapeType::Circle;}
        else if (rawJSON == "Text") {return IShape::ShapeType::Text;}
        else
        {
            qDebug() << "Unsupported shape type: " << rawJSON;
            return IShape::ShapeType::NoShape;
        }
    }

    static QString serializedShapeTypeFrom(const IShape::ShapeType sType)
    {
        switch (sType)
        {
        case IShape::ShapeType::NoShape: return "NoShape";
        case IShape::ShapeType::Polyline: return "Polyline";
        case IShape::ShapeType::Line: return "Line";
        case IShape::ShapeType::Polygon: return "Polygon";
        case IShape::ShapeType::Triangle: return "Triangle";
        case IShape::ShapeType::Rectangle: return "Rectangle";
        case IShape::ShapeType::Square: return "Square";
        case IShape::ShapeType::Ellipse: return "Ellipse";
        case IShape::ShapeType::Text: return "Text";
        case IShape::ShapeType::Circle: return "Circle";
        }
    }

    static QJsonArray serializedDimensionsFrom(const IShape* shapeToSerialize)
    {
        QJsonArray jsonAr;
        switch (shapeToSerialize->getShape())
        {
        case IShape::ShapeType::Line:
            if (const ShapeLine* line = dynamic_cast<const ShapeLine*>(shapeToSerialize))
            {
                for (QPoint vert: line->polyLine)
                {
                    jsonAr.append(QJsonValue(vert.x()));
                    jsonAr.append(QJsonValue(vert.y()));
                }
            }
            break;
        case IShape::ShapeType::Text:
            break;
        case IShape::ShapeType::Circle:
            if (const ShapeCircle* cir = dynamic_cast<const ShapeCircle*>(shapeToSerialize))
            {
                QJsonValue x(cir->frame.x()); QJsonValue y(cir->frame.y());
                QJsonValue w(cir->frame.width());
                jsonAr.append(x); jsonAr.append(y);
                jsonAr.append(w);
            }
            break;
        case IShape::ShapeType::Square:
            if (const ShapeSquare* sq = dynamic_cast<const ShapeSquare*>(shapeToSerialize))
            {
                QJsonValue x(sq->frame.x()); QJsonValue y(sq->frame.y());
                QJsonValue w(sq->frame.width());
                jsonAr.append(x); jsonAr.append(y);
                jsonAr.append(w);
            }
            break;
        case IShape::ShapeType::Ellipse:
            if (const ShapeEllipse* ell = dynamic_cast<const ShapeEllipse*>(shapeToSerialize))
            {
                QJsonValue x(ell->frame.x()); QJsonValue y(ell->frame.y());
                QJsonValue w(ell->frame.width()); QJsonValue h(ell->frame.height());
                jsonAr.append(x); jsonAr.append(y);
                jsonAr.append(w); jsonAr.append(h);
            }
            break;
        case IShape::ShapeType::NoShape:
            break;
        case IShape::ShapeType::Polygon:
            if (const ShapePolygon* poly = dynamic_cast<const ShapePolygon*>(shapeToSerialize))
            {
                for (QPoint vert: poly->poly)
                {
                    jsonAr.append(QJsonValue(vert.x()));
                    jsonAr.append(QJsonValue(vert.y()));
                }
            }
            break;
        case IShape::ShapeType::Polyline:
            if (const ShapePolyLine* line = dynamic_cast<const ShapePolyLine*>(shapeToSerialize))
            {
                for (QPoint vert: line->polyLine)
                {
                    jsonAr.append(QJsonValue(vert.x()));
                    jsonAr.append(QJsonValue(vert.y()));
                }
            }
            break;
        case IShape::ShapeType::Triangle:
            break;
        case IShape::ShapeType::Rectangle:
            if (const ShapeRect* rect = dynamic_cast<const ShapeRect*>(shapeToSerialize))
            {
                QJsonValue x(rect->frame.x()); QJsonValue y(rect->frame.y());
                QJsonValue w(rect->frame.width()); QJsonValue h(rect->frame.height());
                jsonAr.append(x); jsonAr.append(y);
                jsonAr.append(w); jsonAr.append(h);
            }
            break;
        }
        return jsonAr;
    }

    static QColor deserializeQtColorFrom(const QString rawColorJSON, const QColor defaultColor)
    {
        QColor possColor(rawColorJSON);
        if (possColor.isValid()) {return possColor;}
        else {qDebug() << "Encountered invalid color: " << rawColorJSON;}
        return defaultColor;
    }

    static Qt::PenCapStyle deserializeQtCapStyleFrom(const QString rawJsonStr,
                                                     const Qt::PenCapStyle defaultStyle)
    {
        if (rawJsonStr == "FlatCap") {return Qt::PenCapStyle::FlatCap;}
        else if (rawJsonStr == "RoundCap") {return Qt::PenCapStyle::RoundCap;}
        else if (rawJsonStr == "SquareCap") {return Qt::PenCapStyle::SquareCap;}
        else if (rawJsonStr == "MPenCapStyle") {return Qt::PenCapStyle::MPenCapStyle;}
        else
        {
            qDebug() << "Unsupported pen cap style: " << rawJsonStr;
            return defaultStyle;
        }
    }

    static QString serializedQtCapStyleFrom(const Qt::PenCapStyle style)
    {
        switch (style)
        {
        case Qt::PenCapStyle::FlatCap: return "FlatCap";
        case Qt::PenCapStyle::RoundCap: return "RoundCap";
        case Qt::PenCapStyle::SquareCap: return "SquareCap";
        case Qt::PenCapStyle::MPenCapStyle: return "MPenCapStyle";
        }
    }

    static Qt::PenJoinStyle deserializeQtJoinStyleFrom(const QString rawJsonStr,
                                                       const Qt::PenJoinStyle defaultStyle)
    {
        if (rawJsonStr == "BevelJoin") {return Qt::PenJoinStyle::BevelJoin;}
        else if (rawJsonStr == "MiterJoin") {return Qt::PenJoinStyle::MiterJoin;}
        else if (rawJsonStr == "RoundJoin") {return Qt::PenJoinStyle::RoundJoin;}
        else if (rawJsonStr == "SvgMiterJoin") {return Qt::PenJoinStyle::SvgMiterJoin;}
        else if (rawJsonStr == "MPenJoinStyle") {return Qt::PenJoinStyle::MPenJoinStyle;}
        else
        {
            qDebug() << "Unsupported pen join style: " << rawJsonStr;
            return defaultStyle;
        }
    }

    static QString serializedQtJoinStyleFrom(const Qt::PenJoinStyle style)
    {
        switch (style)
        {
        case Qt::PenJoinStyle::BevelJoin: return "BevelJoin";
        case Qt::PenJoinStyle::MiterJoin: return "MiterJoin";
        case Qt::PenJoinStyle::RoundJoin: return "RoundJoin";
        case Qt::PenJoinStyle::SvgMiterJoin: return "SvgMiterJoin";
        case Qt::PenJoinStyle::MPenJoinStyle: return "MPenJoinStyle";
        }
    }

    static Qt::PenStyle deserializeQtPenStyleFrom(const QString rawJsonStr,
                                                  const Qt::PenStyle defaultStyle)
    {
        if (rawJsonStr == "SolidLine") {return Qt::PenStyle::SolidLine;}
        else if (rawJsonStr == "NoPen") {return Qt::PenStyle::NoPen;}
        else if (rawJsonStr == "DotLine") {return Qt::PenStyle::DotLine;}
        else if (rawJsonStr == "DashLine") {return Qt::PenStyle::DashLine;}
        else if (rawJsonStr == "MPenStyle") {return Qt::PenStyle::MPenStyle;}
        else if (rawJsonStr == "DashDotLine") {return Qt::PenStyle::DashDotLine;}
        else if (rawJsonStr == "CustomDashLine") {return Qt::PenStyle::CustomDashLine;}
        else if (rawJsonStr == "DashDotDotLine") {return Qt::PenStyle::DashDotDotLine;}
        else
        {
            qDebug() << "Unsupported pen style: " << rawJsonStr;
            return defaultStyle;
        }
    }

    static QString serializedQtPenStyleFrom(const Qt::PenStyle style)
    {
        switch (style)
        {
        case Qt::PenStyle::SolidLine: return "SolidLine";
        case Qt::PenStyle::NoPen: return "NoPen";
        case Qt::PenStyle::DotLine: return "DotLine";
        case Qt::PenStyle::DashLine: return "DashLine";
        case Qt::PenStyle::MPenStyle: return "MPenStyle";
        case Qt::PenStyle::DashDotLine: return "DashDotLine";
        case Qt::PenStyle::CustomDashLine: return "CustomDashLine";
        case Qt::PenStyle::DashDotDotLine: return "DashDotDotLine";
        }
    }

    static Qt::BrushStyle deserializeBrushStyleFrom(const QString rawJson,
                                                    const Qt::BrushStyle defaultStyle)
    {
        if (rawJson == "NoBrush") {return Qt::BrushStyle::NoBrush;}
        else if (rawJson == "HorPattern") {return Qt::BrushStyle::HorPattern;}
        else if (rawJson == "VerPattern") {return Qt::BrushStyle::VerPattern;}
        else if (rawJson == "BDiagPattern") {return Qt::BrushStyle::BDiagPattern;}
        else if (rawJson == "CrossPattern") {return Qt::BrushStyle::CrossPattern;}
        else if (rawJson == "FDiagPattern") {return Qt::BrushStyle::FDiagPattern;}
        else if (rawJson == "SolidPattern") {return Qt::BrushStyle::SolidPattern;}
        else if (rawJson == "Dense1Pattern") {return Qt::BrushStyle::Dense1Pattern;}
        else if (rawJson == "Dense2Pattern") {return Qt::BrushStyle::Dense2Pattern;}
        else if (rawJson == "Dense3Pattern") {return Qt::BrushStyle::Dense3Pattern;}
        else if (rawJson == "Dense4Pattern") {return Qt::BrushStyle::Dense4Pattern;}
        else if (rawJson == "Dense5Pattern") {return Qt::BrushStyle::Dense5Pattern;}
        else if (rawJson == "Dense6Pattern") {return Qt::BrushStyle::Dense6Pattern;}
        else if (rawJson == "Dense7Pattern") {return Qt::BrushStyle::Dense7Pattern;}
        else if (rawJson == "TexturePattern") {return Qt::BrushStyle::TexturePattern;}
        else if (rawJson == "DiagCrossPattern") {return Qt::BrushStyle::DiagCrossPattern;}
        else if (rawJson == "LinearGradientPattern")
        {return Qt::BrushStyle::LinearGradientPattern;}
        else if (rawJson == "RadialGradientPattern")
        {return Qt::BrushStyle::RadialGradientPattern;}
        else if (rawJson == "ConicalGradientPattern")
        {return Qt::BrushStyle::ConicalGradientPattern;}
        else
        {
            qDebug() << "Unsupported brush style: " << rawJson;
            return defaultStyle;
        }
    }

    static QString serializedQtBrushStyleFrom(const Qt::BrushStyle brushStyle)
    {
        switch (brushStyle)
        {
        case Qt::BrushStyle::NoBrush: return "NoBrush";
        case Qt::BrushStyle::HorPattern: return "HorPattern";
        case Qt::BrushStyle::VerPattern: return "VerPattern";
        case Qt::BrushStyle::BDiagPattern: return "BDiagPattern";
        case Qt::BrushStyle::CrossPattern: return "CrossPattern";
        case Qt::BrushStyle::FDiagPattern: return "FDiagPattern";
        case Qt::BrushStyle::SolidPattern: return "SolidPattern";
        case Qt::BrushStyle::Dense1Pattern: return "Dense1Pattern";
        case Qt::BrushStyle::Dense2Pattern: return "Dense2Pattern";
        case Qt::BrushStyle::Dense3Pattern: return "Dense3Pattern";
        case Qt::BrushStyle::Dense4Pattern: return "Dense4Pattern";
        case Qt::BrushStyle::Dense5Pattern: return "Dense5Pattern";
        case Qt::BrushStyle::Dense6Pattern: return "Dense6Pattern";
        case Qt::BrushStyle::Dense7Pattern: return "Dense7Pattern";
        case Qt::BrushStyle::TexturePattern: return "TexturePattern";
        case Qt::BrushStyle::DiagCrossPattern: return "DiagCrossPattern";
        case Qt::BrushStyle::LinearGradientPattern: return "LinearGradientPattern";
        case Qt::BrushStyle::RadialGradientPattern: return "RadialGradientPattern";
        case Qt::BrushStyle::ConicalGradientPattern: return "ConicalGradientPattern";
        }
    }
};

#endif // JSONSHAPE_H
