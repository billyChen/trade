//
// Trade.hh for Trade in /home/chen_c/rendu/trade
// 
// Made by Billy CHEN
// Login   <chen_c@epitech.net>
// 
// Started on  Fri May 16 17:43:44 2014 Billy CHEN
// Last update Fri Jun  6 00:26:05 2014 Billy CHEN
//

#ifndef TRADE_HH
#define TRADE_HH

#include <vector>

class Trade
{

public:
  Trade();
  ~Trade();
  int		getDays() const;
  void		setDays(int);
  double	getCapital() const;
  void		setCapital(double);
  int		getTotalDays() const;
  void		setTotalDays(int);
  void		Buy(double);
  void		Wait() const;
  void		Sell(double);
  void		doAction(double, Trade*);
  void		setAction(int);
  int		getAction() const;
  void		setExp12();
  void		setExp26();
  void		setExp9();
  void		setMacd();
  double	getMacd() const;
  void		setema12(double);
  void		setema26(double);
  void		setMm(double);
  double	getMm() const;
  void		setEma9(double, std::vector<double>);
  double	getEma9() const;
  double	getEma12() const;
  double	getEma26() const;
  double	getExp12() const;
  double	getExp26() const;
  double	getRsi() const;
  void		setRsi(std::vector<double>, std::vector<double>);
  void		setAvg_gain(std::vector<double>);
  void		setAvg_perte(std::vector<double>);
  double	getAvg_gain() const;
  double	getAvg_perte() const;

  private:
  double	capital;
  int		days;
  int		totalDays;
  int		action;
  double	ema12;
  double	ema26;
  double	exp12;
  double	exp26;
  double	exp9;
  double	ema9;
  double	macd;
  double	mm;
  double	buyPrice;
  double	rsi;
  double	avg_gain;
  double	avg_perte;
};

#endif
