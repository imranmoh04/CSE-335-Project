/**
 * @file Sparty.cpp
 * @author mohac
 */

#include "pch.h"
#include "Sparty.h"

/// The spring pen size to use in pixels
const double SpringWireSize = 2;

/// Minimum spacing between spring wire
const double SpringWireMinSpacing = 1;

/// Color to draw the spring
const wxColour SpringColor = wxColour(220, 220, 220);

/// Sparty popup time in seconds
const double SpartyPopupTime = 0.25;

/// The sparty image to use
const std::wstring SpartyImage = L"/sparty.png";

/**
* constuctor for sparty
*@param imageDir image director
*@param size the size
*@param springWidth width width of spring
*@param springLength spring length
*@param numLinks number of links for spring
*/
Sparty::Sparty(std::wstring imageDir,double size, double springWidth, double springLength, int numLinks):
mImageDir(imageDir), mSpringWidth(springWidth),mSpringLength(springLength),mNumLinks(numLinks)
,mCompressedLength(0), mX(0), mSpartyY(-15), mSpringY(-15), mSpringPopped(false)
{
 mSparty.Rectangle(-size/2, mCompressedLength / 2, size, size);
 mSparty.SetImage(mImageDir + SpartyImage);
}

/**
* used to draw sparty
* @param graphics used to draw
*/
void Sparty::Draw(std::shared_ptr<wxGraphicsContext>  graphics)
{
 DrawSpring(graphics,mX,mSpringY,mSpringLength,mSpringWidth,mNumLinks);
 mSparty.DrawPolygon(graphics, GetX(), GetY());
}

/**
 * Draw a spring.
 * @param graphics Graphics context to render to
 * @param x X location of the bottom center of the spring in pixels
 * @param y Y location of the bottom center of the spring in pixels
 * @param length Length to draw the spring (bottom to top) in pixels
 * @param width Spring width in pixels
 * @param numLinks Number of links (loops) in the spring
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                        int x, int y, double length, double width, int numLinks)
{
 auto path = graphics->CreatePath();
 wxPen pen(SpringColor, SpringWireSize);
 graphics->SetPen(pen);
 // We keep track of three locations, the bottom of which
 // is y1. First half-loop will be y1 to y3, second half-loop
 // will be y3 to y2.
 double y1 = y;
 double linkLength = length / numLinks;

 // Left and right X values
 double xR = x + width / 2;
 double xL = x - width / 2;

 path.MoveToPoint(x, y1);

 for(int i=0; i<numLinks; i++)
 {
  auto y2 = y1 - linkLength;
  auto y3 = y2 - linkLength / 2;

  path.AddCurveToPoint(xR, y1, xR, y3, x, y3);
  path.AddCurveToPoint(xL, y3, xL, y2, x, y2);

  y1 = y2;
 }

 graphics->StrokePath(path);
}

/**
 * Advance the animation in time
 * @param time Amount of time to advance in seconds
 */
void Sparty::Update(double time) {
 Component::Update(time);	// Upcall

 if(mSpringPopped)
 {
  double targetLength = 250;

  // Incrementally increase the spring length
  if (mSpringLength < targetLength) {
   mSpringLength += targetLength * time / SpartyPopupTime;
   if (mSpringLength > targetLength) {
    mSpringLength = targetLength;  // Ensure it doesn't exceed max length
   }
  }
  mSpartyY = -mSpringLength;
 }
}