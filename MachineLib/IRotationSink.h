/**
 * @file IRotationSink.h
 * @author mohac
 *
 *
 */


#ifndef IROTATIONSINK_H
#define IROTATIONSINK_H

/**
* Interface that represents a rotationsink.
*
*/

class IRotationSink
{
 private:
 public:
 /**
  * sets rotation for sinks
  * @param rotation roation
  */
 virtual void SetRotation(double rotation) = 0;
};
#endif //IROTATIONSINK_H
