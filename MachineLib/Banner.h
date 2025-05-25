/**
 * @file Banner.h
 * @author mohac
 *
 *
 */
 
#ifndef BANNER_H
#define BANNER_H

#include "Component.h"
#include "Polygon.h"

/**
* class for banner component
*/
class Banner : public Component{
private:
 double mCurrentWidth;       ///< Current width of the unfurled part of the banner
 double mXPosition;          ///< X position of the banner
 ///polygon for bannerroll
 cse335::Polygon mBannerRoll;
 ///polygon for banner
 cse335::Polygon mBanner;
 /// check is banner rolled
 bool mIsUnfurled;
 /// Resource directory for images
 std::wstring mImageDir;

public:
 // Constructor to initialize the Banner
 Banner(std::wstring imageDir);

 // Method to draw the banner with cropping
 void Draw(std::shared_ptr<wxGraphicsContext> graphics);

 // Method to update the banner (unfurling over time)
 void Update(double time);
};


#endif //BANNER_H
