/**
 * @file MachineSystem.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "MachineSystem.h"

#include "Machine.h"
#include "MachineStandin.h"
#include "MachineCFactory.h"

/**
 * Constructor
 * *@param resourcesDir resources diresctory
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mFactory1 = std::make_shared<MachineCFactory>(mResourcesDir);
    mFactory2 = std::make_shared<MachineAFactory>(mResourcesDir);

    ChooseMachine(1);
}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystem::SetLocation(wxPoint location)
{
    mMachine->SetLocation(location);
}

/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mMachine->GetLocation();
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    auto point = GetLocation();
    graphics->PushState();
    graphics->Translate(point.x, point.y);
    mMachine->DrawMachine(graphics);
    graphics->PopState();
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        Reset();
        mMachine->Update(1.0/mFrameRate);
        mMachine->SetTime(mTime);
    }

    while (mFrame < frame) {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Update(1.0 / mFrameRate);
        mMachine->SetTime(mTime);
    }

}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::ChooseMachine(int machine)
{
    if(machine == 1)
    {
        mMachine = mFactory1->Create();
        mMachine->SetMachine(1);
    }
    else
    {
        mMachine = mFactory2->Create();
        mMachine->SetMachine(2);

    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetMachine();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    SetMachineTime();
    return mTime;
}

