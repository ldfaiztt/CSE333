#include <iostream>
#include <iomanip>

#include "./DividendStock.h"

using namespace std;

// Constructs a new dividend stock with the given symbol and no shares.
DividendStock::DividendStock(string symbol, double share_price)
  : Stock(symbol, share_price) {
  dividends_ = 0.0;
}

// Returns the market value of this stock, which is the total number
// of shares times the share price, plus dividends
double DividendStock::GetMarketValue() const {
  return get_shares() * get_share_price() + dividends_;
}

// Returns the total amount of dividends paid on this stock.
double DividendStock::GetDividends() const {
  return dividends_;
}

// Records a dividend of the given amount per share.
void DividendStock::PayDividend(double amount_per_share) {
  dividends_ += amount_per_share * get_shares();
}

// Print out the Dividendstock information.
void DividendStock::Print() const {
  cout << "DividendStock (" << get_symbol() << "):" << endl;
  cout << "  value: $" << setw(7) << GetMarketValue() << endl;
  cout << "   cost: $" << setw(7) << GetCost() << endl;
  cout << " profit: $" << setw(7) << GetProfit() << endl;
}
