/**
 * @file Shaft.h
 * @author mohac
 *
 *
 */
 
#ifndef SHAFT_H
#define SHAFT_H

#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/**
* class for shaft component
*/
class Shaft : public Component, public IRotationSink{
private:
 /// to keep track of rotation
 double mRotation;
 ///cylinder for shaft
 cse335::Cylinder mCylinder;
 ///postion
 wxPoint mPos;
 ///size
 wxPoint mSize;
 /// Rotation source for this component
 RotationSource mSource;

public:
 Shaft();
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 /**
  * setter for location
  * @param location loaction
  */
 void SetLocation(wxPoint location) { mPos.x = location.x; mPos.y = location.y; }
 void SetSize(wxPoint size);
 /// getter for size
 /// @return size
 wxPoint GetSize() {return mSize; }
 ///getter for position
 ///@return location
 wxPoint GetLocation() {return mPos;}
 /// sets rotation from crank
 /// @param rotation the new rotation
 void SetRotation(double rotation) {mRotation = rotation;}
 ///getter for rotation
 ///@return the rotation
 double GetRotation() const { return mRotation; }
 void Update(double time) override;
 /// Get a pointer to the source object
 /// @return Pointer to RotationSource object
 RotationSource *GetSource() { return &mSource; }
};



#endif //SHAFT_H
