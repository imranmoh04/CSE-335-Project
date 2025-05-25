/**
* @file RotationSource.cpp
 * @author mohac
 */
#include "pch.h"
#include "RotationSource.h"

#include "IRotationSink.h"

RotationSource::RotationSource()
{
}

/**
* sets rotation for other components
*@param rotation
*/
void RotationSource::SetRotation(double rotation)
{

 for (auto sink : mSinks) {
  sink->SetRotation(rotation);
 }
}

/**
* adds roation sinks
*@param sink roation sinks
*/
void RotationSource::AddSink(IRotationSink* sink)
{
 mSinks.push_back(sink);
}
