#include <iostream>
#include <iomanip>

#include "./Stock.h"

// Constructs a new Stock with the given symbol and current price per share.
Stock::Stock(string symbol, double share_price) {
  symbol_ = symbol;
  share_price_ = share_price;
  cost_ = 0.0;
  shares_ = 0;
}

// Gets the stock symbol.
string Stock::get_symbol() const {
  return symbol_;
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

// Returns this asset's total cost spent on all shares.
double Stock::GetCost() const {
  return cost_;
}

// Returns the market value of this stock, which is the total number
// of shares times the share price.
double Stock::GetMarketValue() const {
  return get_shares() * get_share_price();
}

// Returns the profit earned on this stock.
double Stock::GetProfit() const {
  return GetMarketValue() - GetCost();
}

// Records a purchase of the given number of shares of stock at the
// given price per share.
void Stock::Purchase(int shares, double share_price) {
  shares_ += shares;
  cost_ += shares * share_price;
}

// Print out the stock information.
void Stock::Print() const {
  cout << "Stock (" << get_symbol() << "):" << endl;
  cout << "  value: $" << setw(7) << GetMarketValue() << endl;
  cout << "   cost: $" << setw(7) << GetCost() << endl;
  cout << " profit: $" << setw(7) << GetProfit() << endl;
}
