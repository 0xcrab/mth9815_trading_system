
/**
 * BasicListener.hpp
 * This file provides a Listener class that basically does nothing,
 * but implement the pure virtual functions given by soa.hpp Service
 * 
 * With this BasicListener.hpp, a lot of work can be avoided when
 * define a new service
 * 
 * @ Zilun shen <shenzilun@gmail.com>
 */

#ifndef BASICLISTENER_HPP
#define BASICLISTENER_HPP

#include "framework/soa.hpp"

template<typename V>
class BasicListener : public virtual ServiceListener<V>
{

public:
  virtual ~BasicListener() = default;

  // Listener callback to process an add event to the Service
  virtual void ProcessAdd(V &data) {}

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(V &data) {}

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(V &data) {}

};

#endif
