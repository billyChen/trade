//
// Trade.cpp for Trade in /home/chen_c/rendu/trade
// 
// Made by Billy CHEN
// Login   <chen_c@epitech.net>
// 
// Started on  Fri May 16 17:43:38 2014 Billy CHEN
// Last update Fri Jun  6 15:11:24 2014 Billy CHEN
//

#include "Trade.hh"
#include <iostream>

Trade::Trade()
{
  this->capital = 0;
  this->days = 0;
}

Trade::~Trade()
{

}

int		Trade::getDays() const
{
  return (this->days);
}

void		Trade::setDays(int val)
{
  this->days = val;
}

int		Trade::getTotalDays() const
{
  return (this->totalDays);
}

void		Trade::setTotalDays(int val)
{
  this->totalDays = val;
}

double		Trade::getCapital() const
{
  return (this->capital);
}

void		Trade::setCapital(double val)
{
  this->capital = val;
}

void		Trade::Buy(double val)
{
  double	buy;
  double	commission;
  int		nbr;

  nbr = (this->capital / val);
  if (nbr <= 0)
    this->Wait();
  else
    {
      this->buyPrice = val;
      buy = nbr * val;
      commission = 0.0015 * buy;
      this->capital = this->capital - (buy + commission);
      this->action = this->action + nbr;
      std::cout << "buy " << nbr << std::endl;
    }
}

void		Trade::Wait() const
{
  std::cout << "wait" << std::endl;
}

void		Trade::Sell(double val)
{
  double	sell;
  double	commission;

  if (this->action > 0)
    {
      std::cout << "sell " << this->action << std::endl;
      sell = val * this->action;
      commission = 0.0015 * sell;
      this->capital = this->capital + (sell - commission);
      this->action = 0;
    }
  else
    this->Wait();
}

void		Trade::doAction(double val, Trade *t)
{
  static double	prevMacd = 0;
  static double	prevSig = 0;
  static double	prevRsi = 0;
  static int	i = 0;

  if (i == 0)
    {
      prevMacd = this->macd;
      prevSig = this->ema9;
      prevRsi = this->rsi;
      i = i + 1;
      this->Wait();
    }
  else
    {
      if (prevMacd >= prevSig && this->macd <= this->ema9
	  && this->buyPrice < val)
	{
	  this->Sell(val);
	  prevMacd = this->macd;
	  prevSig = this->ema9;
	  prevRsi = this->rsi;
	}
      else if (prevMacd <= prevSig && this->macd >= this->ema9 && this->days >= 34
	       && this->macd - this->ema9 >= 3 && this->macd <= 30)
	{	
	  this->Buy(val);
	  prevMacd = this->macd;
	  prevSig = this->ema9;
	  prevRsi = this->rsi;
	}
      else
	{
	  this->Wait();
	  prevMacd = this->macd;
	  prevSig = this->ema9;
	  prevRsi = this->rsi;
	}
    }
}

int		Trade::getAction() const
{
  return (this->action);
}

void		Trade::setAction(int val)
{
  this->action = val;
}

void		Trade::setExp12()
{
  this->exp12 = 2.00 / 13.00;
}

void		Trade::setExp26()
{
  this->exp26 = 2.00 / 27.00;
}

void		Trade::setMacd()
{
  this->macd = this->ema12 - this->ema26;
}

double		Trade::getMacd() const
{
  return (this->macd);
}

void		Trade::setema12(double arg)
{
  static int	i = 0;
  static double	prev = 0;

  if (i == 0)
    {
      this->ema12 = this->mm;
      prev = this->ema12;
      i = i + 1;
    }
  else
    {
      this->ema12 = prev * (1 - this->exp12) + arg * this->exp12;
      prev = this->ema12;
    }
}

void		Trade::setema26(double arg)
{
  static int	i = 0;
  static double	prev = 0;

  if (i == 0)
    {
      this->ema26 = this->mm;
      prev = this->ema26;
      i = i + 1;
    }
  else
    {
      this->ema26 = prev * (1 - this->exp26) + arg * this->exp26;  
      prev = this->ema26;
    }
}

void		Trade::setMm(double val)
{
  this->mm = val;
}

double		Trade::getMm() const
{
  return (this->mm);
}

void		Trade::setEma9(double arg, std::vector<double>somme)
{
  static int	i = 0;
  static double	prev = 0;
  std::vector<double>::const_iterator	it;
  double	avg;
  int		day;

  if (i == 0)
    {
      day = 0;
      avg = 0;
      for (it = somme.begin(); it != somme.end(); it++)
	{
	  avg += *it;
	  day = day + 1;
	}
      avg = avg / day;
      this->ema9 = avg;
      prev = this->ema9;
      i = i + 1;
    }
  else
    {
      this->ema9 = prev * (1 - this->exp9) + this->macd * this->exp9;    
      prev = this->ema9;
    }
}

double		Trade::getEma9() const
{
  return (this->ema9);
}

void		Trade::setExp9()
{
  this->exp9 = 2.00 / 10.00;  
}

double		Trade::getEma12() const
{
  return (this->ema12);
}

double		Trade::getEma26() const
{
  return (this->ema26);
}

double		Trade::getExp12() const
{
  return (this->exp12);
}

double		Trade::getExp26() const
{
  return (this->exp26);
}

double		Trade::getRsi() const
{
  return (this->rsi);
}

void		Trade::setRsi(std::vector<double> baisse, std::vector<double>hausse)
{
  double	rsi;
  double	rs;

  this->setAvg_gain(hausse);
  this->setAvg_perte(baisse);
  rs = this->avg_gain / this->avg_perte;
  rsi = 100 - (100 / (1 + rs));
  this->rsi = rsi;
}

void		Trade::setAvg_gain(std::vector<double> hausse)
{
  std::vector<double>::const_iterator it;
  double	avg;
  double	day;

  day = 0;
  avg = 0;
  for (it = hausse.begin(); it != hausse.end(); it++)
    {
      avg += *it;
      day = day + 1;
    }
  avg = avg / day;
  this->avg_gain = avg;
}

void		Trade::setAvg_perte(std::vector<double> baisse)
{
  std::vector<double>::const_iterator it;
  double	avg;
  double	day;

  day = 0;
  avg = 0;
  for (it = baisse.begin(); it != baisse.end(); it++)
    {
      avg += *it;
      day = day + 1;
    }
  avg = avg / day;
  this->avg_perte = avg;
}

double		Trade::getAvg_gain() const
{
  return (this->avg_gain);
}

double		Trade::getAvg_perte() const
{
  return (this->avg_perte);
}
