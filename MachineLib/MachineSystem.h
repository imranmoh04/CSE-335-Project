/**
 * @file MachineSystem.h
 * @author Charles Owen
 *
 * A Machine System class that displays a standin machine only.
 *
 * DO NOT CHANGE THIS FILE!
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H

#include "IMachineSystem.h"
#include "MachineAFactory.h"

class MachineStandin;
class MachineCFactory;
class Machine;

/**
 * A Machine System class that displays a standin machine only.
 */
class MachineSystem : public IMachineSystem
{
private:
    /**
     * A stand-in machine class.
     *
     * This draws simple stand-in graphics
     * so you can see where the machine will be and what its state
     * is. This makes it easy to develop code that uses the
     * machine before you have the machine working.
     *
     * And no, you may not change this to point to your
     * machine implementation!
     */
    std::shared_ptr<MachineStandin> mStandin;
    ///current machine
    std::shared_ptr<Machine> mMachine;
    /// Path to the resources directory
    std::wstring mResourcesDir;
    /// Pointer to factory1
    std::shared_ptr<MachineCFactory> mFactory1;
 /// Point to factory2
 std::shared_ptr<MachineAFactory> mFactory2;
    /// Time elapsed
    double mTime = 0;
    /// location of machine
    wxPoint mLocation;
    /// framerate for animation
    double mFrameRate = 30;
    /// current frame
    int mFrame = 0;

public:
    /// Constructor
    MachineSystem(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;


    virtual void SetLocation(wxPoint location);
    virtual wxPoint GetLocation();


    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void SetMachineFrame(int frame);
    virtual void SetFrameRate(double rate);
    virtual void ChooseMachine(int machine);
    virtual int GetMachineNumber();
    virtual double GetMachineTime();
///Sets machine time
 void SetMachineTime() {mTime = (mFrame/mFrameRate);}

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) {}
///resets time
    void Reset() {mTime = 0;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H
