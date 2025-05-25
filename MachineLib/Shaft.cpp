/**
 * @file Shaft.cpp
 * @author mohac
 */
#include "pch.h"
#include "Shaft.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
/// First parameter to Cylinder::SetLines
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
/// Second parameter to Cylinder::SetLines
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
/// Third parameter to Cylinder::SetLines
const int ShaftNumLines = 4;
///constuctor
Shaft::Shaft() : mRotation(0)
{
 mCylinder.SetColour(ShaftColor);
 mCylinder.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);
}

/**
* draws shaft
* @param graphics used to draw
*/
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 mCylinder.Draw(graphics,GetLocation().x,GetLocation().y,mRotation);
}

/**
 * updates roation for other components
 * * @param time the time
 */
void Shaft::Update(double time)
{
 mSource.SetRotation(mRotation);
}

/**
 * sets size
 * @param size the size
 */
void Shaft::SetSize(wxPoint size)
{
 mSize = size; // Update the shaft's size property
 mCylinder.SetSize(size.x, size.y); // Update the cylinder's size
}