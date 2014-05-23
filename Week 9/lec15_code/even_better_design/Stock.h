#ifndef _LEC15_STOCK_H_
#define _LEC15_STOCK_H_

#include <string>

using namespace std;

// A Stock object represents purchases of shares of a stock.
class Stock {
 public:
  Stock(string symbol, double share_price = 0.0);

  // Stock's mutator/accessor methods.
  virtual void   Purchase(int shares, double share_price);
  virtual string get_symbol() const;
  virtual int    get_shares() const;
  virtual double get_share_price() const;
  virtual void   set_share_price(double share_price);

  // Stock's "investment" interface.
  virtual double GetCost() const;
  virtual double GetMarketValue() const;
  virtual double GetProfit() const;

  // Print out the Stock information.
  virtual void Print() const;

 private:
  string symbol_;
  int    shares_;
  double cost_;
  double share_price_;
};

#endif  // LEC15_STOCK_H_
