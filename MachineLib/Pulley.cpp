/**
 * @file Pulley.cpp
 * @author mohac
 */
#include "pch.h"
#include "Pulley.h"

/// How wide the hub is on each side of the pulley
const double PulleyHubWidth = 3;

/// How deep the belt is into the pulley
const double PulleyBeltDepth = 3;

/// The color to use for pulleys
const wxColour PulleyColor = wxColour(205, 250, 5);

/// The line color to use for the hub
/// First parameter to Cylinder::SetLines
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width to draw the lines on the hub
/// Second parameter to Cylinder::SetLines
const int PulleyHubLineWidth = 4;

/// The number of lines to draw on a pulley is the int(diameter / 6.0)
/// Third parameter to Cylinder::SetLines
const double PulleyHubLineCountDiviser = 6.0;

/**
* constuctor
* @param diameter for pulley hub
* @param width width for pulley
**/
Pulley::Pulley(double diameter, double width) : mWidth(width),mRotation(0), mDiameter(diameter)
{
 mBodyCylinder.SetSize(mDiameter, mWidth);
 mBodyCylinder.SetColour(PulleyColor);
 mBodyCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth,PulleyHubLineCountDiviser);

 // Set the size for the left and right hub cylinders
 mLeftHubCylinder.SetSize(mDiameter + PulleyBeltDepth, PulleyHubWidth);
 mLeftHubCylinder.SetColour(PulleyColor);
 mLeftHubCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth, PulleyHubLineCountDiviser);

 mRightHubCylinder.SetSize(mDiameter + PulleyBeltDepth, PulleyHubWidth);
 mRightHubCylinder.SetColour(PulleyColor);
 mRightHubCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth, PulleyHubLineCountDiviser);
}

/**
* fucntion to draw pulley
* @param graphics used to draw
**/
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 // Draw the body of the pulley
 mBodyCylinder.Draw(graphics, GetLocation().x, GetLocation().y, mRotation);

 // Draw the left hub
 mLeftHubCylinder.Draw(graphics, GetLocation().x-3, GetLocation().y, mRotation);

 // Draw the right hub
 mRightHubCylinder.Draw(graphics, GetLocation().x+mWidth , GetLocation().y, mRotation);
 DrawBelt(graphics);
}

/**
* draws belt over pulley
*
** @param graphics used to draw
*/
void Pulley::DrawBelt(std::shared_ptr<wxGraphicsContext> graphics)
{
 if (mBeltConnectedPulley == nullptr)
 {
  return;
 }
 double thisRadius = mDiameter/2;
 double connectedRadius = mBeltConnectedPulley->GetDiameter()/2;
 wxPoint thisCenter = GetLocation();
 wxPoint connectedCenter = mBeltConnectedPulley->GetLocation();

 double thisHubY = thisCenter.y+thisRadius;

 double connectedHubY = connectedCenter.y;

 double beltHeight; // Vertical height difference

 graphics->SetPen(wxPen(wxColour(50, 50, 50)));
 graphics->SetBrush(wxBrush(wxColour(50, 50, 50)));
 if (thisCenter.y > connectedCenter.y)
 {
   beltHeight = fabs(connectedHubY - thisHubY)+(connectedRadius);
  graphics->DrawRectangle(connectedCenter.x, connectedCenter.y-connectedRadius, mWidth, beltHeight);
 }
 else
 {
  beltHeight = fabs(connectedHubY - thisHubY)+(connectedRadius+mDiameter);
  graphics->DrawRectangle(GetLocation().x, GetLocation().y-thisRadius, mWidth, beltHeight);
 }
  }


/**
 * Set the rotation for this component
 * @param rotation Relative number of turns to set.
 */
void Pulley::SetRotation(double rotation)
{
 // Set the rotation for an source
  mRotation = rotation;

 if (mBeltConnectedPulley != nullptr)
 {
  // Set the rotation for any pulley we
  // are connected to by a belt.
  mBeltConnectedPulley->SetRotation(rotation);
 }

}

/**
 * connects two pulleys
 * @param pulley ptr to pulley
 */
void Pulley::ConnectPulley(Pulley* pulley)
{
 mBeltConnectedPulley = pulley;
}

/**
 * updates rotions for components
 * @param time time
 */
void Pulley::Update(double time)
{
 mSource.SetRotation(mRotation);
}
