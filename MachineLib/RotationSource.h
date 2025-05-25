/**
* @file RotationSource.h
 * @author mohac
 *
 *
 */

#ifndef ROTATIONSOURCE_H
#define ROTATIONSOURCE_H

class IRotationSink;
/**
* class for roations sources
*/
class RotationSource {
private:
 /// List of sinks connected to this source
 std::vector<IRotationSink*> mSinks;

public:
 /// Constructor
 RotationSource();

 /// Copy constructor (disabled)
 RotationSource(const RotationSource &) = delete;

 /// Assignment operator (disabled)
 void operator=(const RotationSource &) = delete;

 void SetRotation(double rotation);

 void AddSink(IRotationSink* sink);
};



#endif //ROTATIONSOURCE_H
