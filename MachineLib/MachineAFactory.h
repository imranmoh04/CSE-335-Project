/**
 * @file MachineAFactory.h
 * @author mohac
 *
 *
 */
 
#ifndef MACHINEAFACTORY_H
#define MACHINEAFACTORY_H


#include <memory>
#include <string>

class Machine;
class Shape;

/**
 * Factory for creating Machine #1
 */
class MachineAFactory {
private:
 /// Path to the resources directory
 std::wstring mResourcesDir;

 /// Path to the images directory
 std::wstring mImagesDir;

public:
 MachineAFactory(std::wstring resourcesDir);

 std::shared_ptr<Machine> Create();
};



#endif //MACHINEAFACTORY_H
