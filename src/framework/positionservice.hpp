/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"
#include "tradebookingservice.hpp"

using std::string;
using std::map;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:

  // ctor for a position
  Position();
  Position(const T &_product);

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(const string &book);

  // Get the aggregate position
  long GetAggregatePosition();

  // Add position to a book
  void AddPosition(Trade<T> trade);

private:
  T product;
  map<string,long> positions;

};

/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public virtual Service<string,Position <T> >
{

public:

  // Add a trade to the service
  virtual void AddTrade(const Trade<T> &trade) = 0;

};

template<typename T>
Position<T>::Position() {
	positions["TRSY1"] = 0;
	positions["TRSY2"] = 0;
	positions["TRSY3"] = 0;
}

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
	positions["TRSY1"] = 0;
	positions["TRSY2"] = 0;
	positions["TRSY3"] = 0;
}

template<typename T>
const T& Position<T>::GetProduct() const
{
	return product;
}

template<typename T>
long Position<T>::GetPosition(const string &book)
{
  return positions[book];
}

template<typename T>
void Position<T>::AddPosition(Trade<T> trade)
{
	long volume = trade.GetQuantity();
	if(trade.GetSide() == SELL) volume = -volume;
	positions[trade.GetBook()] += volume;
}

template<typename T>
long Position<T>::GetAggregatePosition()
{
  // No-op implementation - should be filled out for implementations
  return 
	positions["TRSY1"] + 
	positions["TRSY2"] + 
	positions["TRSY3"];
  return 0;
}

#endif
