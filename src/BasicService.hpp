/**
 * BasicService.hpp
 * This file provides a Service class that basically does nothing,
 * but implement the pure virtual functions given by soa.hpp Service
 * 
 * With this BasicService.hpp, a lot of work can be avoided when
 * define a new service
 * 
 * @ Zilun shen <shenzilun@gmail.com>
 */

#ifndef BASICSERVICE_HPP
#define BASICSERVICE_HPP

#include "framework/soa.hpp"
#include <vector>
#include <string>
#include <map>
#include <functional>
using std::vector;
using std::map;
using std::string;
using std::function;

template<typename K, typename V>
class BasicService : public virtual Service<K, V>{
public:

	// Default ctor, use ProductId as key
	BasicService() : 
		GetID([](const V& v){return v.GetProduct().GetProductId();}){}
	// Use given func to get key
	BasicService(function<string(const V&)> _GetID) : GetID(_GetID) {}

	// Get data on our service given a key
	virtual V& GetData(K key){ return data_pool[key]; }
	//virtual const V& GetData(K key) const { 
		//std::cout << "Get Data" << key << std::endl;	
		//return data_pool.at(key); 
	//}

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(V &data){
		//data_pool[data.GetProduct().GetProductId()] = data;
		data_pool[GetID(data)] = data;
		for(auto&& lsnr : listeners){
			lsnr->ProcessAdd(data);
		}
	}

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<V> *listener){ listeners.push_back(listener); }

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<V>* >& GetListeners() const{ return listeners; }

protected:
	function<string(const V&)> GetID;
	vector<ServiceListener<V>*> listeners;
	map<K, V> data_pool;
};

#endif
