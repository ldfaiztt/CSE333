#ifndef _LEC15_DIVIDENDSTOCK_H_
#define _LEC15_DIVIDENDSTOCK_H_

#include <string>

#include "./Stock.h"

using namespace std;

// Represents a stock purchase that also pays dividends.
class DividendStock : public Stock {
 public:
  DividendStock(string symbol, double share_price = 0.0);

  // DividendStock's mutator and accessor methods.
  void PayDividend(double amount_per_share);

  // DividentStock's "investment" interface.
  double GetMarketValue() const;
  double GetDividends() const;

  // Print out the DividendStock information.
  void Print() const;

 private:
  double dividends_;
};

#endif  // LEC15_DIVIDEND_STOCK_
