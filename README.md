# The Golden Cone's CS1C Project

![alt text](https://github.com/xavierliancw/CS1C-Class-Project/blob/master/artifacts/doxygen%20documentation/html/unknown.png)

## Requirement Locations in Source Code: 

GOLDEN CONE GRAPHICS PROGRAM
__________________________________________________________________________________________________________
EXTRA-CREDIT SORTING DONE IN:
*CustomSorts.h
- Sorting implementation: line 38
*dlgshapereport.cpp 
- Fuction that uses sorting implmenetation: line 40
__________________________________________________________________________________________________________
Class project requirements are met in these files:
__________________________________________________________________________________________________________
1) Provide satisfied customer testimonials (solicit for additional
testimonials). Guest users may enter testimonials. The testimonials
should be persistent between executions.

*dlgtestimonialcreate.h

- Entire dialog creates a new testimonial

*dlgtestimonialcreate.cpp
- Entire dialog creates a new testimonial

*dlgtestimonialcreate.ui
- Entire dialog creates a new testimonial

*dtotestimonial.h
- Struct that represents the attributes of a testimonial

*jsontestimonial.h
- JSON transformational layer that converts DTOTestimonial objects into JSON

*svcjson.h
- Service that persists JSON in the local filesystem.

*svcjson.cpp
- Persists JSON in the local filesystem: line 54
- Reads JSON: line 90

__________________________________________________________________________________________________________
2)Provide "contact us" method with team name and logo

*dlgcontactform.h, *dlgcontactform.cpp, *dlgcontactform.ui
- Entire dialog takes input for creating an inquiry

*final_icon.png
- Our logo

*dtocustomerinquiry.h
- Struct that represents an inquiry

*jsoncustomerinquiry.h
- JSON transformational layer

*svcjson.h
- Persists and loads inquiry JSON to and from the local filesystem

*svcjson.cpp
- Persists JSON: line 54
- Reads JSON: line 90

__________________________________________________________________________________________________________
3)Display all graphic objects (i.e. shapes including text) in rendering
window. The shape id will be displayed above each shape identifying
it. The rendering area to display shapes must have minimum
dimensions of 1000 pixels (horizontal) by 500 pixels (vertical). The
coordinate system is defined such that the top left corner of the
rendering area is located at point (0,0), the bottom right corner at
point (1000,500).

*vmcanvas.h
*vmcanvas.cpp
*goldenconevector.h
*ishape.h
*ishape.cpp
*shapecircle.h
*shapecircle.cpp
*shapeellipse.h
*shapeellipse.cpp
*shapeline.h
*shapeline.cpp
*shapepolygon.h
*shapepolygon.cpp
*shapepolyline.h
*shapepolyline.cpp
*shaperect.h
*shaperect.cpp
*shapesquare.h
*shapesquare.cpp
*shapetext.h
*shapetext.cpp
*vmcanvas.h
*vmcanvas.cpp
*winmainl.h
*winmain.cpp
__________________________________________________________________________________________________________
4)Your program should read from a shape file that keeps track of all
shapes currently being rendered by the 2D modeler. Shapes are
identified by their type: line, polyline, polygon, rectangle, ellipse,
text. Shapes have properties: shape dimensions, pen color, pen
width, pen style, pen cap style, pen join style, brush color, brush
shape. Text has properties: shape dimensions, text string, text 
color, text alignment, text point size, text font family, text font
style, text font weight. All shapes must also have a unique ID.

*IShape.h
*IShape.cpp
*jsonshape.h
*jsonshape.cpp
*svcjson.h
*svcjson.cpp
__________________________________________________________________________________________________________
5)Your program should be able to move shapes, including text, being
rendered. This is accomplished via a move shape form. All changes
are visible in the rendering area. ñ administrator only

*/movement on canvas is done by move functions on the shapes derived from IShape
	abstract class, see (3)
__________________________________________________________________________________________________________
6)Your program should be able to add and remove shapes, including
text, being rendered. This is accomplished via an add/remove shape
form. All changes are visible in the rendering area. ñ administrator
only

*goldenconevector.h
*vmcanvas.h
*vmcanvas.cpp
*winmain.cpp
- Adding shapes: line 648 and 604
- Removing shapes: line 346

*/all images rendered on canvas use specific IShape-derived-classes coordinates see (3)

__________________________________________________________________________________________________________
7)Produce a shape listing report sorted by shape id (at any time). All
shape properties should be included in the report.

*dlgshapereport.h
*dlgshapereport.cpp
*dlgshapreport.ui
__________________________________________________________________________________________________________
8)Produce a shape listing report of ONLY shapes with an area sorted
by area (at any time). The shape type, id and area should be
included in the report.

*/see (7)
*customsorts.h
__________________________________________________________________________________________________________
9)Produce a shape listing report of ONLY shapes with a perimeter
sorted by perimeter (at any time). The shape type, id and perimeter
should be included in the report.

*/ see(8)
__________________________________________________________________________________________________________
10)Save all changes between executions

*winmain.h
*winmain.cpp
*winmain.ui
*jsonshape.h
*jsonshape.cpp
*svcjson.h
*svcjson.cpp
- Persists JSON: line 54
- Reads JSON: line 90

__________________________________________________________________________________________________________
