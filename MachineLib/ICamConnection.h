/**
 * @file ICamConnection.h
 * @author mohac
 *
 *
 */
 
#ifndef ICAMCONNECTION_H
#define ICAMCONNECTION_H
/**
* Interface that represents a cam connection for keydrop.
*
*/
class ICamConnection
{
public:
/**
* activates  when key is dropped
*/
 virtual void ActivateOnKey() = 0;
};


#endif //ICAMCONNECTION_H
