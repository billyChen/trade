//
// main.cpp for main in /home/chen_c/rendu/trade
// 
// Made by Billy CHEN
// Login   <chen_c@epitech.net>
// 
// Started on  Fri May 16 17:42:46 2014 Billy CHEN
// Last update Fri Jun  6 15:09:45 2014 Billy CHEN
//

#include <iostream>
#include <sstream>
#include "Trade.hh"
#include <vector>
#include <cmath>
#include <iomanip>
  
double			stringToDouble(std::string arg)
{
  double		val;

  std::istringstream	i(arg);
  i >> val;
  return (val);
}

int			stringToInt(std::string arg)
{
  int			val;
  std::istringstream	i(arg);

  i >> val;
  return (val);
}

double			CalculateMm(std::vector<double>somme, int days)
{
  std::vector<double>::const_iterator it;
  double		add;

  add = 0;
  for (it = somme.begin(); it != somme.end(); it++)
    {
      add += *it;
    }
  add = add / days;
  return (add);
}

void			addSum(std::vector<double>*somme, std::string arg)
{
  double		val;
  std::istringstream	i(arg);

  i >> val;
  somme->push_back(val);
}

int			main(int argc, char **argv)
{
  std::string		arg;
  Trade			*t;
  std::vector<double>	somme;
  std::vector<double>	macdSomme;
  std::vector<double>	hausse;
  std::vector<double>	baisse;
  double		var;
  double		current_val;
  double		last_val;

  t = new Trade();
  std::cin >> arg;
  t->setCapital(stringToDouble(arg));
  std::cin >> arg;
  t->setTotalDays(stringToInt(arg));
  t->setDays(1);
  std::cin >> arg;
  t->setExp12();
  t->setExp26();
  t->setExp9();
  while (arg != "--end--")
    {
      addSum(&somme, arg);
      current_val = stringToDouble(arg);
      t->setMm(CalculateMm(somme, t->getDays()));
      if (t->getDays() >= 2)
	{
	  var = current_val - last_val;
	  if (var < 0)
	    {
	      var = var * -1;
	      baisse.push_back(var);
	    }
	  else if (var > 0)
	    hausse.push_back(var);
	}
      if (t->getDays() >= 12)
	{
	  t->setema12(current_val);
	  if (t->getDays() >= 14)
	    {
	      t->setRsi(baisse, hausse);
	      if (t->getDays() >= 26)	
		{
		  t->setema26(current_val);
		  t->setMacd();
		  macdSomme.push_back(t->getMacd());
		  if (t->getDays() >= 34)
		    {
		      t->setEma9(current_val, macdSomme);
		    }
		}
	    }
	}
      t->doAction(current_val, t);
      if (t->getDays() + 1 == t->getTotalDays() && t->getAction() > 0)
	t->Sell(current_val);
      std::cin >> arg;
      t->setDays(t->getDays() + 1);
      last_val = current_val;
    }
}
