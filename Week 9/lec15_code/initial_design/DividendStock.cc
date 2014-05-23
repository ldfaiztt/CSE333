#include <iomanip>

#include "./DividendStock.h"

using std::endl;
using std::setw;

// Constructs a new dividend stock with the given symbol and no shares.
DividendStock::DividendStock(string symbol, double share_price) {
  symbol_ = symbol;
  share_price_ = share_price;
  cost_ = 0.0;
  shares_ = 0;
  dividends_ = 0.0;
}

// Returns this asset's total cost spent on all shares.
double DividendStock::GetCost() const {
  return cost_;
}

// Returns the market value of this stock, which is the total number
// of shares times the share price, plus dividends
double DividendStock::GetMarketValue() const {
  return shares_ * share_price_ + dividends_;
}

// Returns the profit earned on shares of this asset.
double DividendStock::GetProfit() const {
  return GetMarketValue() - GetCost();
}

// Returns the total amount of dividends paid on this stock.
double DividendStock::GetDividends() const {
  return dividends_;
}

// Records a purchase of the given number of shares of stock at the
// given price per share.
void DividendStock::Purchase(int shares, double share_price) {
  shares_ += shares;
  cost_ += shares * share_price;
}

// Records a dividend of the given amount per share.
void DividendStock::PayDividend(double amount_per_share) {
  dividends_ += amount_per_share * shares_;
}

// Returns the total number of shares purchased.
int DividendStock::get_shares() const {
  return shares_;
}

// Returns the price per share of this asset.
double DividendStock::get_share_price() const {
  return share_price_;
}

// Sets the current share price of this asset.
void DividendStock::set_share_price(double share_price) {
  share_price_ = share_price;
}

// Gets the stock symbol.
string DividendStock::get_symbol() const {
  return symbol_;
}

// Print the dividendstock to the ostream; note this is a non-member
// function.
ostream &operator<<(ostream &out, const DividendStock &rhs) {
  out << "DividendStock (" << rhs.get_symbol() << "):" << endl;
  out << "  value: $" << setw(7) << rhs.GetMarketValue() << endl;
  out << "   cost: $" << setw(7) << rhs.GetCost() << endl;
  out << " profit: $" << setw(7) << rhs.GetProfit() << endl;
  return out;
}
