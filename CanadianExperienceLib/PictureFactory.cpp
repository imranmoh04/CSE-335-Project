/**
 * @file PictureFactory.cpp
 *
 * @author Charles Owen
 * @author Anik Momtaz
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(750, 620));
    picture->AddActor(sparty);

    auto machine1Actor = std::make_shared<Actor>(L"Machine1");
    auto machine1 = std::make_shared<MachineDrawable>(L"Machine1", resourcesDir);
    machine1->SetPosition(wxPoint(400, 550));
    machine1->SetScale(0.75);
    auto *timeline = picture->GetTimeline();
    machine1->SetTimeLine(timeline);
    machine1Actor->AddDrawable(machine1);
    machine1Actor->SetRoot(machine1);
    picture->AddActor(machine1Actor);

    auto machine2Actor = std::make_shared<Actor>(L"Machine2");
    auto machine2 = std::make_shared<MachineDrawable>(L"Machine2", resourcesDir);
    machine2->SetPosition(wxPoint(1000, 550));
    machine2->SetScale(0.75);
    machine2->SetMachineNumber(2);
    machine2->Update();
    machine2->SetTimeLine(timeline);
    machine2Actor->AddDrawable(machine2);
    machine2Actor->SetRoot(machine2);
    picture->AddActor(machine2Actor);

    return picture;
}

