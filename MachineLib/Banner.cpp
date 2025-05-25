/**
 * @file Banner.cpp
 * @author mohac
 */

#include "pch.h"
#include "Banner.h"

/// Scale to draw relative to the image sizes
const double BannerScale = 0.42;

/// Height of the banner in pixels
double const BannerHeight = 150 * BannerScale;

/// Width fo the banner in pixels
const double BannerWidth = 1024 * BannerScale;

/// Height of the banner roll image in pixels
const double BannerRollHeight = 300 * BannerScale;

/// Width of the banner roll image in pixels
double const BannerRollWidth = 16 * BannerScale;

/// How fast ot unfurl the banner in pixels per second
double const BannerSpeed = 41.65;

/// Minimum number of pixels to start with as unfurled
const double BannerMinimum = 15;

///banner image
const std::wstring BannerImage = L"/banner.png";

///banner roll image
const std::wstring BannerRollImage = L"/banner.png";

/**
 * constuctor
 * @param imageDir image directory
 *
 */
Banner::Banner(std::wstring imageDir) :  mImageDir(imageDir),mCurrentWidth(0), mXPosition(-200), mIsUnfurled(false) {
 // Load images
 mBannerRoll.SetImage(mImageDir + BannerRollImage);  // Apply banner roll image
 mBannerRoll.Rectangle(0, 0, BannerWidth, BannerHeight);

 mBanner.SetImage(mImageDir + BannerImage);
}

/**
 * draws banner
 * @param graphics used to drwa
 */
void Banner::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
 mBannerRoll.DrawPolygon(graphics, mXPosition, 300, 0);
}

/**
 * updates banner
 * @param time time
 *
 */
void Banner::Update(double time) {
 if (!mIsUnfurled)
 {
  mCurrentWidth += BannerSpeed * time;  // Adjust speed as necessary

  // Make sure the banner does not exceed its full width
  if (mCurrentWidth >= BannerWidth)
  {
   mCurrentWidth = BannerWidth;
   mIsUnfurled = true;  // Mark banner as fully unfurled
  }
 }
}
