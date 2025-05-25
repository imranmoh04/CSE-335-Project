/**
 * @file MachineDrawable.h
 * @author mohac
 *
 *
 */
 
#ifndef MACHINEDRAWABLE_H
#define MACHINEDRAWABLE_H

#include "Drawable.h"
#include "Timeline.h"

class IMachineSystem;

/**
 * class to draw machine in Candian experience
 */
class MachineDrawable : public Drawable
{
private:
 ///machine number
 int mMachineNumber = 1;
 /// scale of machine
 double mScale = 1.0;
 /// keep track of time
 double mStartTime = 0;
 /// the resource directory
 std::wstring mResourceDir;
 ///position of machine
 wxPoint mPos;
 /// Time for animation
 double mTime = 0;
 /// frame for animation
 double mFrame = 0;
 ///framerate for animation
 double mFrameRate = 0;
 /// timeline for time
 Timeline *mTimeline = nullptr;
 /// composiiton for machine
 std::shared_ptr<IMachineSystem> mMachineSystem;
public:
 MachineDrawable(std::wstring name, std::wstring resourceDir);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 bool HitTest(wxPoint pos) override;
 /**
 * Add the channels for this drawable to a timeline
 * @param timeline The timeline class.
 */
 void SetTimeLine(Timeline *timeline) { mTimeline = timeline; }
 /**
  * set postion of machine
  * @param pos postion
  */
 void SetPosition(wxPoint pos) {mPos.x = pos.x, mPos.y = pos.y;}
 /**
  * setter for machine number
  * @param num number to set
  */
 void SetMachineNumber(int num) {mMachineNumber = num;}
/**
* set sclae
*@param scale the scale
*/
 void SetScale(double scale) { mScale = scale; }
 /**
 * set frame using timeline
*/
 void SetFrame() {mFrame = mTimeline->GetCurrentFrame();}
 /**
 * get frame
 *@return the frame
*/
 double GetFrame() {return mFrame;}
 /**
 * sets framerate
*/
 void SetFrameRate() {mFrameRate = mTimeline->GetFrameRate();}
 /**
 * get framerate
 * @return the framerate
*/
 double GetFrameRate() {return mFrameRate;}
 /// Sets the animation start time
 /// @param time start time
 void SetStartTime(double time) { mStartTime = time; }
 /// Gets the animation start time
 /// @return the start tiem
 double GetStartTime() const { return mTimeline->GetTime(); }
 void HandleDoubleClick(wxFrame* parent);
 void Update();
 void ShowMachineDialog(wxFrame* parent);
 wxXmlNode *SaveToXml(wxXmlNode *node);
 void LoadFromXml(wxXmlNode *machineNode);
};


#endif //MACHINEDRAWABLE_H
