/**
 * @file Machine.cpp
 * @author mohac
 */

#include "pch.h"
#include "Machine.h"

Machine::Machine()
{
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void Machine::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
 for (auto component : mComponents)
 {
  component->Draw(graphics);
 }
}
/**
* updates the machine for animation
*@param time the time
*/
void Machine::Update(double time)
{
 for (auto component : mComponents)
 {
  component->Update(time);
 }
}


/**
 * adds components to machine
 * @param component components
 */
void Machine::AddComponent(std::shared_ptr<Component> component) {
 mComponents.push_back(component);
}
