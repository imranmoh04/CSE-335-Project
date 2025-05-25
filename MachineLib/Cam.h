/**
 * @file Cam.h
 * @author mohac
 *
 *
 */
 
#ifndef CAM_H
#define CAM_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "ICamConnection.h"
#include "Polygon.h"


/**
* class for cam component
*/
class Cam : public Component, public IRotationSink {
private:
///polygon for key
cse335::Polygon mKey;
///keep track of rotation
double mRotation;
///check if key is dropped
bool mIsKeyIn;
///cylinder for cam
cse335::Cylinder mCylinder;
 /// Resource directory for images
 std::wstring mImageDir;
 ///postion of cam
 wxPoint mPos;
 ///list of connections
 std::vector<ICamConnection*> mCamConnection;
public:
 Cam(std::wstring imageDir);
 /**
 * setter for rotation
 *@param rotation the rotation
*/
 void SetRotation(double rotation) {mRotation = rotation;}
 ///getter for rotation
 ///@return the rotation
 double GetRotation() const { return mRotation; }
 void AddKeyDrop(ICamConnection* connection);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
/**
 * setter for location
 * @param location location
 */
void SetLocation(wxPoint location) { mPos.x = location.x; mPos.y = location.y; }
 ///getter for position
 ///@return the location
 wxPoint GetLocation() {return mPos;}
 void ActivateOnKey();
};



#endif //CAM_H
