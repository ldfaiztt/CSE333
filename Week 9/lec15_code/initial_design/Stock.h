#ifndef _LEC15_STOCK_H_
#define _LEC15_STOCK_H_

#include <string>
#include <iostream>

using std::string;
using std::ostream;

// A Stock object represents purchases of shares of a stock.
class Stock {
 public:
  Stock(string symbol, double share_price = 0.0);

  // Stock's mutator/accessor methods.
  void   Purchase(int shares, double share_price);
  int    get_shares() const;
  double get_share_price() const;
  void   set_share_price(double share_price);
  string get_symbol() const;

  // Stock's "investment" interface.
  double GetCost() const;
  double GetMarketValue() const;
  double GetProfit() const;

  // Overload (ostream& <<) so we can print Stock.
  friend ostream &operator<<(ostream &out, const Stock &rhs);

 private:
  string symbol_;
  int    shares_;
  double cost_;
  double share_price_;
};

#endif  // LEC15_STOCK_H_
