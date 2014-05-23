#ifndef _LEC15_DIVIDENDSTOCK_H_
#define _LEC15_DIVIDENDSTOCK_H_

#include <string>
#include <iostream>

using std::string;
using std::ostream;

// Represents a stock purchase that also pays dividends.
class DividendStock {
 public:
  DividendStock(string symbol, double share_price = 0.0);

  // DividendStock's mutator and accessor methods.
  void   PayDividend(double amount_per_share);
  void   Purchase(int shares, double share_price);
  int    get_shares() const;
  double get_share_price() const;
  void   set_share_price(double share_price);
  string get_symbol() const;

  // DividentStock's "investment" interface.
  double GetCost() const;
  double GetMarketValue() const;
  double GetProfit() const;
  double GetDividends() const;

  // Overload (ostream& <<) so we can print DividendStock.
  friend ostream &operator<<(ostream &out, const DividendStock &rhs);

 private:
  string symbol_;
  int    shares_;
  double cost_;
  double share_price_;
  double dividends_;
};

#endif  // LEC15_DIVIDEND_STOCK_
