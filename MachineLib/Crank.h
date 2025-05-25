/**
 * @file Crank.h
 * @author mohac
 *
 *
 */
 
#ifndef CRANK_H
#define CRANK_H

#include "Component.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
* class for crank component
*/
class Crank : public Component {
private:
/// to keep track of rotation
double mRotation;
 /// speed of rotation
double mRotationSpeed;
///cylinder for handle
cse335::Cylinder mHandle;
///postion
wxPoint mPos;
 /// Rotation source for this component
 RotationSource mSource;
public:
 Crank();
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void Update(double time) override;
/**
 * setter for location
 * @param location location
 */
void SetLocation(wxPoint location) { mPos.x = location.x; mPos.y = location.y; }
 ///getter for position
 ///@return the postion
 wxPoint GetLocation() {return mPos;}
 /// Get a pointer to the source object
 /// @return Pointer to RotationSource object
 RotationSource *GetSource() { return &mSource; }
};



#endif //CRANK_H
