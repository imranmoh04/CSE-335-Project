/**
 * @file Component.h
 * @author mohac
 *
 *
 */
 
#ifndef COMPONENT_H
#define COMPONENT_H


/**
* class for components
*/
class Component {
private:

/// position of object
 wxPoint mPos;
 /// size of object
 wxPoint mSize;
public:
/**
 * draws the machine
 * @param graphics used to draw
 */
virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Set the position for the root of the machine
     * @param location X,Y location in pixels
     */
  virtual void SetLocation(wxPoint location) { mPos.x = location.x; mPos.y = location.y; }
 /**
      * Set the size for the root of the machine
      * @param size X,Y size in pixels
      */
 virtual void SetSize(wxPoint size) {mSize.x = size.x; mSize.y = size.y; }
 /// Update the state of the component
 /// @param time the time
 virtual void Update(double time) {}

 /// Reset the component to its initial state
 virtual void Reset() {}

};



#endif //COMPONENT_H
