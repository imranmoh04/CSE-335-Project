/**
 * @file Box.cpp
 * @author mohac
 */

#include "pch.h"
#include "Box.h"

/// The background image to use
const std::wstring BoxBackgroundImage = L"/box-background.png";

/// The foreground image to use
const std::wstring BoxForegroundImage = L"/box-foreground.png";

/// The lid image to use
const std::wstring BoxLidImage = L"/box-lid.png";

/// The horizontal scale for the lid when the angle is zero
const double LidZeroAngleScale = 0.02;

/// How long it takes to up the lid in seconds
const double LidOpeningTime = 0.25;

/**
 * constructor
 * @param imageDir image director
 * @param boxSize box size
 * @param lidSize lid size
 */
Box::Box(std::wstring imageDir, double boxSize, double lidSize)
: mX(0), mY(0), mLidAngle(0), mLidScale(LidZeroAngleScale), mIsOpen(false), mOpenTime(0.0), mImageDir(imageDir)
{
 mBox.Rectangle(-boxSize/2, 0,boxSize , boxSize);
 mBox.SetImage(mImageDir + BoxBackgroundImage);

 mForeground.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
 mForeground.SetImage(mImageDir + BoxForegroundImage);

 mLid.Rectangle(-lidSize / 2, 0, lidSize, lidSize);
 mLid.SetImage(mImageDir + BoxLidImage);
}

/**
* used to draw box
* @param graphics used to draw
*/
void Box::Draw(std::shared_ptr<wxGraphicsContext>  graphics) {
 // Draw the main box
 mBox.DrawPolygon(graphics, GetX(), GetY());  // Draw the box at position (0, 0) with no rotation

 CalculateLidPosition();

 graphics->PushState();
 graphics->Translate(mLidX, mLidY);
 graphics->Scale(1, mLidScale);

 mLid.DrawPolygon(graphics, 0, 0);

 graphics->PopState();
 DrawForeground(graphics);
}
/**
 * used to draw foregroound of box
* @param graphics used to draw
*/
void Box::DrawForeground(std::shared_ptr<wxGraphicsContext>  graphics) {
 // Draw the foreground polygon
 mForeground.DrawPolygon(graphics, GetX(), GetY());  // Draw the foreground at the same position
}

/**
 * Advance the animation in time
 * @param time Amount of time to advance in seconds
 */
void Box::Update(double time) {
 Component::Update(time);	// Upcall

 double openAngle = M_PI / 2;

 if(mIsOpen && mLidAngle < openAngle)
 {
  mLidAngle += openAngle * time / LidOpeningTime;

  if(mLidAngle > openAngle)
  {
   mLidAngle = openAngle;
  }
 }
 mLidScale = LidZeroAngleScale + (1 - LidZeroAngleScale) * sin(mLidAngle);
}
/**
* toggles the box to open
*/
void Box::ActivateOnKey() {
 mIsOpen = true;   // Toggle open/closed state
 mOpenTime = 0.0;     // Reset the open time when toggled
}
/**
* calculate lid position
*/
void Box::CalculateLidPosition()
{
 // Horizontal center
 mLidX = mX;

 // Vertical position is at the top of the box, considering lid height
 mLidY = mY - 250 ;
}


