#ifndef _LEC15_STOCK_H_
#define _LEC15_STOCK_H_

#include <string>

using namespace std;

// A Stock object represents purchases of shares of a stock.
class Stock {
 public:
  Stock(string symbol, double share_price = 0.0);

  // Stock's mutator/accessor methods.
  string get_symbol() const;
  int    get_shares() const;
  double get_share_price() const;
  void   set_share_price(double share_price);

  // Stock's "investment" interface.
  void   Purchase(int shares, double share_price);
  double GetCost() const;
  double GetMarketValue() const;
  double GetProfit() const;

  // Print out the Stock information.
  void Print() const;

 private:
  string symbol_;
  int    shares_;
  double cost_;
  double share_price_;
};

#endif  // LEC15_STOCK_H_
