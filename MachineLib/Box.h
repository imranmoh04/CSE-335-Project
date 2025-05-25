/**
 * @file Box.h
 * @author mohac
 *
 *
 */

#ifndef BOX_H
#define BOX_H


#include "Component.h"
#include "ICamConnection.h"
#include "Polygon.h"

/**
 * class for box component
 */
class Box : public Component, public ICamConnection {
private:
 ///x postion of lid
 double mLidX;
 ///y position of lid
 double mLidY;
 ///whether box is open
 bool mIsOpen;
 ///time since the box was opened
 double mOpenTime;
 /// Polygon representing the box
 cse335::Polygon mBox;
 ///  polygon for foreground
 cse335::Polygon mForeground;
 /// polygone for lid
 cse335::Polygon mLid;
 /// Resource directory for images
 std::wstring mImageDir;
 ///x position of box
 double mX;
 ///y position of box
 double mY;
 /// Current angle of the lid
 double mLidAngle;
 /// Current scale of the lid
 double mLidScale;
public:
 /// Constructor
 Box(std::wstring imageDir, double boxSize, double lidSize);

 /// Draw the box graphics
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 /// Draw the foreground graphics
 void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics);

 /// Update the state of the box over time
 void Update(double time) override;

 /// Activate or deactivate the box on a key press
 void ActivateOnKey();
 ///get lid position
 void CalculateLidPosition();
/**
* check is box is open
*@return if box is open
*/
 bool IsOpen() const { return mIsOpen;}

 ///getter for x position
 ///@return the x pos
 double GetX() const { return mX; }
 ///getter for y position
 ///@return the y pos
 double GetY() const { return mY; }
};



#endif //BOX_H
