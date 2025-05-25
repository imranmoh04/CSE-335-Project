/**
* @file MachineCFactory.cpp
 *
 * @author Charles Owen
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "Machine.h"
#include "Box.h"
#include "Cam.h"
#include "Sparty.h"
#include "Crank.h"
#include "Pulley.h"
#include "Shaft.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineCFactory::MachineCFactory(std::wstring resourcesDir) :
        mResourcesDir(resourcesDir)
{
 mImagesDir = mResourcesDir + ImagesDirectory;
}



/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> MachineCFactory::Create()
{
 // The machine itself
 auto machine = std::make_shared<Machine>();

 // Locations of some things in the machine
 const int Shaft1Y = -180;
 const int Shaft2Y = -70;
 const int Shaft3Y = -180;

 /*
  * The Box class constructor parameters are:
  * @param imagesDir Directory containing the images
  * @param boxSize Size of the box in pixels (just the box, not the lid)
  * @param lidSize Size of the lid in pixels
  */
 auto box = std::make_shared<Box>(mImagesDir, 250, 240);

 // This simulates the cam key drop so the box will immediately open
 //box->KeyDrop();
 machine->AddComponent(box);

 /*
  * The Sparty class constructor parameters are:
  * @param image Image file to load
  * @param size Size to draw Sparty (width and height)
  * @param springLength How long the spring is when fully extended in pixels
  * @param springWidth How wide the spring is in pixels
  * @param numLinks How many links (loops) there are in the spring
  */
 auto sparty =
     std::make_shared<Sparty>(mImagesDir, 212, 80, 80, 15);

 // This simulates the cam key drop so Sparty will immediately pop up
 //sparty->KeyDrop();
 machine->AddComponent(sparty);

 auto crank = std::make_shared<Crank>();
 crank->SetLocation({150, Shaft1Y});

 auto shaft1 = std::make_shared<Shaft>();
 shaft1->SetLocation({90, Shaft1Y});
 shaft1->SetSize({10,70});
 machine->AddComponent(shaft1);

 crank->GetSource()->AddSink(shaft1.get());

 machine->AddComponent(crank);

 auto pulley1 = std::make_shared<Pulley>(30, 15);
 pulley1->SetLocation({103, Shaft1Y});
 shaft1->GetSource()->AddSink(pulley1.get());

 // The second pulley
 auto pulley2 = std::make_shared<Pulley>(80, 15);
 pulley2->SetLocation({pulley1->GetLocation().x, Shaft2Y});
 pulley1->ConnectPulley(pulley2.get());

 auto shaft2 = std::make_shared<Shaft>();
 shaft2->SetLocation({-115, Shaft2Y});
 shaft2->SetSize({10,230});
 machine->AddComponent(shaft2);

 pulley2->GetSource()->AddSink(shaft2.get());

 // We add the driven pulley first, then the driving pulley
 // so the belt draws on top of both
 machine->AddComponent(pulley2);
 machine->AddComponent(pulley1);

 auto pulley3 = std::make_shared<Pulley>(15, 15);
 pulley3->SetLocation({-103, Shaft2Y});
 shaft2->GetSource()->AddSink(pulley3.get());

 auto pulley4 = std::make_shared<Pulley>(90, 15);
 pulley4->SetLocation({pulley3->GetLocation().x, Shaft3Y});
 pulley3->ConnectPulley(pulley4.get());

 auto shaft3 = std::make_shared<Shaft>();
 shaft3->SetLocation({-115, Shaft3Y});       // Left end of the shaft
 shaft3->SetSize({10, 50});                // Diameter and length
 machine->AddComponent(shaft3);

 pulley4->GetSource()->AddSink(shaft3.get());

 machine->AddComponent(pulley4);
 machine->AddComponent(pulley3);

 auto cam = std::make_shared<Cam>(mImagesDir);
 cam->SetLocation({-80,Shaft3Y});
 machine->AddComponent(cam);

 cam->AddKeyDrop(box.get());
 cam->AddKeyDrop(sparty.get());

 shaft3->GetSource()->AddSink(cam.get());

 return machine;
}

