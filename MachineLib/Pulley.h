/**
 * @file Pulley.h
 * @author mohac
 *
 *
 */
 
#ifndef PULLEY_H
#define PULLEY_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/**
* Class for pulley component
*/
class Pulley : public Component, public IRotationSink{
private:
 ///position
 wxPoint mPos;
///diamtere of pulley
double mDiameter;

///keep track of rotation
double mRotation;
 ///width of pulley
 double mWidth;
 /// Rotation source for this component
 RotationSource mSource;
 ///other pulleys
 Pulley* mBeltConnectedPulley = nullptr;
 /// Cylinder used to draw pulley body
 cse335::Cylinder mBodyCylinder;
 /// Cylinders for the lefy pulley hub
 cse335::Cylinder mLeftHubCylinder;
 /// Cylinders for the right pulley hub
 cse335::Cylinder mRightHubCylinder;
 ///check for if updating
 bool mIsUpdating = false;
public:
 Pulley(double diameter,double width);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 void SetRotation(double rotation);
 /**
 * getter for rotation
* @return the rotation
**/
 double GetRotation() const { return mRotation; }
 void Update(double time) override;
 ///setter for diameter
 ///@param diameter the diameter
 void SetDiameter(double diameter) {mDiameter = diameter;}
 ///getter for diameter
 ///@return the diameter
 double GetDiameter() {return mDiameter;}
 void ConnectPulley(Pulley* pulley);
 void DrawBelt(std::shared_ptr<wxGraphicsContext> graphics);
 ///setter for location
 ///@param location locoation point
 void SetLocation(wxPoint location) { mPos.x = location.x; mPos.y = location.y; }
 ///getter for position
 ///@return the location
 wxPoint GetLocation() {return mPos;}
 /// Get a pointer to the source object
 /// @return Pointer to RotationSource object
 RotationSource *GetSource() { return &mSource; }
};



#endif //PULLEY_H
