/**
 * @file MachineDrawable.cpp
 * @author mohac
 */
#include "pch.h"
#include "MachineDrawable.h"
#include <machine-api.h>


/**
 * constuctor
 * @param name name of machine
 * @param resourceDir resource directory
 */
MachineDrawable::MachineDrawable(std::wstring name, std::wstring resourceDir) : Drawable(name), mResourceDir(resourceDir)
{
 MachineSystemFactory factory(mResourceDir);
 mMachineSystem = factory.CreateMachineSystem();
}

/**
 * draws machine
 * @param graphics used to draw
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 if (!mMachineSystem) return;

 // Save the current graphics state
 graphics->PushState();

 // Translate and scale the drawing context
 graphics->Translate(mPos.x, mPos.y);
 graphics->Scale(mScale, mScale);

 // Set the machine system's position to the origin


 // Draw the machine system
 mMachineSystem->DrawMachine(graphics);
 SetFrameRate();
 mMachineSystem->SetFrameRate(mFrameRate);
 SetFrame();
 mMachineSystem->SetMachineFrame(mFrame);

 // Restore the graphics state
 graphics->PopState();
}

/**
 * to test if mahcine is hit
 * @param pos position
 * @return if machine is hit
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
 // Make x and y relative to the top-left corner of the bitmap image
 // Subtracting the center makes x, y relative to the image center
 // Adding half the size makes x, y relative to theimage top corner
 double size = 250;
 double testX = pos.x - mPos.x + size/2;
 double testY = pos.y - mPos.y + size;

 // Test to see if x, y are in the image
 if (testX < 0 || testY < 0 || testX >= size || testY >= size)
 {
  // We are outside the image
  return false;
 }
 else
 {
  std::cout << "lol it wokrs" << std::endl;
  return true;
 }
}

/**
 * displays dialog
 * @param parent the frame parent
 */
void MachineDrawable::ShowMachineDialog(wxFrame* parent) {
 if (!mMachineSystem) return;

 MachineDialog dialog(parent, mMachineSystem);
 if (dialog.ShowModal() == wxID_OK) {

 }
}

/**
 * updates machine drawable
 */
void MachineDrawable::Update()
{
  mMachineSystem->ChooseMachine(mMachineNumber);
}


/**
 * used to save the machine
 * @param node the node being saved to
 * @return the node
 */
wxXmlNode *MachineDrawable::SaveToXml(wxXmlNode *node) {
 auto machineNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"MachineDrawable");
 node->AddChild(machineNode);
 // Save attributes
 machineNode->AddAttribute(L"name", GetName());
 machineNode->AddAttribute(L"position-x", std::to_wstring(mPos.x));
 machineNode->AddAttribute(L"position-y", std::to_wstring(mPos.y));
 machineNode->AddAttribute(L"scale", std::to_wstring(mScale));
 machineNode->AddAttribute(L"start-time", std::to_wstring(mStartTime));
 machineNode->AddAttribute(L"time", std::to_wstring(mTime));
 machineNode->AddAttribute(L"frame", std::to_wstring(mFrame));
 machineNode->AddAttribute(L"frame-rate", std::to_wstring(mFrameRate));
 machineNode->AddAttribute(L"machine-number", std::to_wstring(mMachineNumber));

 return machineNode;
}

/**
 * loads from an xml
 * @param machineNode the node being loaded from
 */
void MachineDrawable::LoadFromXml(wxXmlNode *machineNode) {
 machineNode->GetAttribute(L"position-x",L"0").ToInt(&mPos.x);
 machineNode->GetAttribute(L"position-y",L"0").ToInt(&mPos.y);
 machineNode->GetAttribute(L"scale").ToDouble(&mScale);
 machineNode->GetAttribute(L"start-time",L"0").ToDouble(&mStartTime);
 machineNode->GetAttribute(L"time", L"0").ToDouble(&mTime);
 machineNode->GetAttribute(L"frame", L"0").ToDouble(&mFrame);
 machineNode->GetAttribute(L"frame-rate", L"0").ToDouble(&mFrameRate);
 machineNode->GetAttribute(L"machine-number",L"1").ToInt(&mMachineNumber);
}

/**
 * handle double click
 * @param parent the frame
 */
void MachineDrawable::HandleDoubleClick(wxFrame* parent)
{
 ShowMachineDialog(parent);
}

