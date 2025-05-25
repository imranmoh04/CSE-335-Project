/**
 * @file Cam.cpp
 * @author mohac
 */

#include "pch.h"
#include "Cam.h"

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam diameter
const double CamDiameter = 60;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;
/// cam color
const wxColour CamColor = wxColour(255, 255, 255);
///cam border color
const wxColour CamBorderColor = wxColour(0, 0, 0);


/**
 * constructor
 * @param imageDir image directoryu
 *
 */
Cam::Cam(std::wstring imageDir) : mImageDir(imageDir), mRotation(0), mIsKeyIn(false)
{
 mKey.SetImage(mImageDir + KeyImage);
 mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);

 mCylinder.SetSize(CamDiameter, CamWidth);
 mCylinder.SetColour(CamColor);
 mCylinder.SetBorderColor(CamBorderColor);
}

/**
* used to draw cam
*@param graphics used to draw
*/
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 // Calculate the position of the hole
 double holeX = GetLocation().x + (CamWidth / 2) - (HoleSize / 2);
 double holeHeight = HoleSize * (1 + 0.5 * sin(mRotation * 2 * M_PI));
 double centerY = GetLocation().y;

 // Update holeY to change with rotation
 // Rotate the hole vertically around the center of the cam
 double holeY = centerY - (holeHeight/2) + ( cos(mRotation * 2 * M_PI));
 double phaseShift = (CamDiameter / 2) * cos(mRotation * 2 * M_PI);
 holeY += phaseShift;


 if (mRotation >= 0.5) // A small range around 0.5
 {
  mIsKeyIn = true;
 }
 if (mIsKeyIn)
 {
  mKey.DrawPolygon(graphics, GetLocation().x+(CamWidth / 2), GetLocation().y-(CamDiameter / 2)+(KeyImageSize/2));
  ActivateOnKey();
  mCylinder.Draw(graphics, GetLocation().x, GetLocation().y, mRotation);
  graphics->SetBrush(*wxBLACK);
 graphics->SetPen(*wxTRANSPARENT_PEN);

  graphics->DrawEllipse(holeX, GetLocation().y-(CamDiameter / 2), HoleSize, 4);
 }
 else
 {
  mKey.DrawPolygon(graphics, GetLocation().x+(CamWidth / 2), GetLocation().y-(CamDiameter / 2));
  mCylinder.Draw(graphics, GetLocation().x, GetLocation().y, mRotation);
graphics->SetBrush(*wxBLACK);
 graphics->SetPen(*wxTRANSPARENT_PEN);

  graphics->DrawEllipse(holeX, holeY, HoleSize, holeHeight);

 }
}

/**
 * adds connections for keydrop
 * @param connection connections
 */
void Cam::AddKeyDrop(ICamConnection* connection)
{
 mCamConnection.push_back(connection);
}

/**
 * activates any connections when key is dropped
 */
void Cam::ActivateOnKey()
{
 for (auto connection : mCamConnection) {
        if (connection)
         {
            connection->ActivateOnKey();
        }
    }
}