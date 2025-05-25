/**
 * @file Smile.h
 * @author mohac
 *
 *
 */
 
#ifndef SMILE_H
#define SMILE_H

#include "Component.h"
#include "ICamConnection.h"
#include "Polygon.h"

/**
* cclass for smile component
*/
class Smile :public Component, public ICamConnection{
private:
 ///length of compressed
 double mCompressedLength;
 ///Number of links for spring
 int mNumLinks;
 ///spring width
 double mSpringWidth;
 ///spring length
 double mSpringLength;
 /// the current length of the spring
 double mCurrentSpringLength;
 /// check if spring is popped or not
 bool mSpringPopped;
 /// Resource directory for images
 std::wstring mImageDir;
 /// polygon for sparty
 cse335::Polygon mSparty;
 ///position for x
 double mX;
 ///postion for y for sparty
 double mSmileY;
 ///positon for y for spring
 double mSpringY;
public:
 Smile(std::wstring imageDir,double size, double springWidth, double springLength, int numLinks);

 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double compressedLength, double springWidth, int numLinks);

 void Update(double time) override;
 /// Activate or deactivate the box on a key press
 void ActivateOnKey() { mSpringPopped =true;}
///getter for x position
 ///@return the x pos
 double GetX() const { return mX; }
 ///getter for y position
 ///@return the y pos
 double GetY() const { return mSmileY; }

};


#endif //SMILE_H
