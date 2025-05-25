/**
 * @file Machine.h
 * @author mohac
 *
 *
 */
 
#ifndef MACHINE_H
#define MACHINE_H
#include "Component.h"

/**
* class for machine
*/
class Machine {
private:
///Time elapsed
double mTime;
 ///Machine number
 int mMachineNum;
 ///list of compnents
 std::vector<std::shared_ptr<Component>> mComponents;
 int mX = 0;         ///< Machine x location
 int mY = 0;         ///< Machine y location
 int mFrame = 0;     ///< Current frame
 int mMachine = 1;   ///< Machine number
public:
 Machine();

 /**
     * Set the position for the root of the machine
     * @param location X,Y location in pixels
     */
 void SetLocation(wxPoint location) { mX = location.x; mY = location.y; }

 /**
  * Get the root position of the machine
  * @return location x,y in pixels as a point
  */
 wxPoint GetLocation() {return wxPoint(mX, mY);}

 void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);

 /**
 * Set the current machine animation frame
 * @param frame Frame number
 */
 void SetMachineFrame(int frame) { mFrame = frame; }

 /**
 * Set the machine number
 * @param machine An integer number. Each integer makes a different machine
 */
 void SetMachine(int machine) { mMachine = machine; }

 /**
 * Get the current machine number
 * @return Machine number
 */
 int GetMachine() { return mMachine; }

 void Update(double time);


 void AddComponent(std::shared_ptr<Component> component);
/**
 * sets time
 * @param time the time
 *
 */
void SetTime(double time) { mTime = time; }

};



#endif //MACHINE_H
