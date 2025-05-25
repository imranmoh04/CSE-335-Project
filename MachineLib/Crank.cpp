/**
 * @file Crank.cpp
 * @author mohac
 */

#include "pch.h"
#include "Crank.h"

/// The width of the crank on the screen in pixels
const int CrankWidth = 10;

/// The depth of the crank away from the screen in pixels
const int CrankDepth = 20;

/// The length of the crank in pixels
const int CrankLength = 50;

/// The diameter to draw the crank handle
const int HandleDiameter = 7;

/// How long the handle is in pixels
const int HandleLength = 40;

/// How much to the left of the crank X the handle starts in pixels
const int HandleStartX = -10;

///max height for rectangle
const int MaxHeight = CrankLength * 2;


/// Crank color
const wxColour CrankColor = wxColour(220, 220, 220);

/// Line color for the rod
const wxColour CrankHandleLineColor = wxColour(100, 100, 100);
/**
* constructor
*/
Crank::Crank() : mRotation(0),mRotationSpeed(0.1)
{
 mHandle.SetSize(HandleDiameter, HandleLength);
 mHandle.SetColour(CrankColor);
 mHandle.SetLines(CrankHandleLineColor, 1, 4);
}
/**
* draws the crank
*@param graphics used to draw
*/
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 double angle = mRotation * 2 * M_PI;
 double handleY = GetLocation().y - cos(angle) * CrankLength;
 mHandle.Draw(graphics, GetLocation().x +HandleStartX, handleY, mRotation);

 double scaledHeight;
 double rectY;
 if(handleY < GetLocation().y)
 {
 scaledHeight = fabs(cos(angle)) * CrankLength + CrankDepth;
 rectY = GetLocation().y - scaledHeight + CrankDepth/2;

 }
 else
 {
  scaledHeight = cos(angle) * CrankLength - CrankDepth;
 rectY = GetLocation().y - scaledHeight - CrankDepth/2;
 }
 // Draw the rectangle vertically, with the Y position unchanged, but height changing
 graphics->SetPen(wxPen(wxColour(0, 0, 0), 1)); // Black border
 graphics->SetBrush(wxBrush(CrankColor)); // Crank color for the fill
 graphics->DrawRectangle(GetLocation().x - CrankWidth / 2, rectY, CrankWidth, scaledHeight);  // Draw centered and scaled

}

/**
 * Advance the animation in time
 * @param time Amount of time to advance in seconds
 */
void Crank::Update(double time)
{
 mRotation += time * mRotationSpeed;
 if (mRotation >= 1.0)
  mRotation -= 1.0;
 else if (mRotation < 0.0)
  mRotation += 1.0;

 mSource.SetRotation(mRotation);
}
