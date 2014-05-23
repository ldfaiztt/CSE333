#include <iomanip>

#include "./Stock.h"

using std::endl;
using std::setw;

// Constructs a new Stock with the given symbol and current price per share.
Stock::Stock(string symbol, double share_price) {
  symbol_ = symbol;
  share_price_ = share_price;
  cost_ = 0.0;
  shares_ = 0;
}

// Returns this asset's total cost spent on all shares.
double Stock::GetCost() const {
  return cost_;
}

// Returns the market value of this stock, which is the total number
// of shares times the share price.
double Stock::GetMarketValue() const {
  return shares_ * share_price_;
}

// Returns the profit earned on shares of this asset.
double Stock::GetProfit() const {
  return GetMarketValue() - GetCost();
}

// Records a purchase of the given number of shares of stock at the
// given price per share.
void Stock::Purchase(int shares, double share_price) {
  shares_ += shares;
  cost_ += shares * share_price;
}

// Returns the total number of shares purchased.
int Stock::get_shares() const {
  return shares_;
}

// Returns the price per share of this asset.
double Stock::get_share_price() const {
  return share_price_;
}

// Sets the current share price of this asset.
void Stock::set_share_price(double share_price) {
  share_price_ = share_price;
}

// Gets the stock symbol.
string Stock::get_symbol() const {
  return symbol_;
}

// Print the stock to the ostream; note this is a non-member function.
ostream &operator<<(ostream &out, const Stock &rhs) {
  out << "Stock (" << rhs.get_symbol() << "):" << endl;
  out << "  value: $" << setw(7) << rhs.GetMarketValue() << endl;
  out << "   cost: $" << setw(7) << rhs.GetCost() << endl;
  out << " profit: $" << setw(7) << rhs.GetProfit() << endl;
  return out;
}
