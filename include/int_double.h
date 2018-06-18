// a simple version of double interval arithmetic that avoids messing
// with rounding modes by doing nextbefore/nextafter after every operation
// may increase interval unnecessarily when results are exact
#ifndef INT_DOUBLE
#define INT_DOUBLE
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "crlibm.h"

using namespace std;

inline long double min(const long double a, const long double b, const long double c, const long double d)
{
  return std::min(std::min(a,b),std::min(c,d));
}

inline long double max(const long double a, const long double b, const long double c, const long double d)
{
  return std::max(std::max(a,b),std::max(c,d));
}

long double nextbefore(const long double);

inline long double nextafter (const long double x)
{
  if(!isfinite(x)) return nan("");
  if(x==0.0) return DBL_MIN;
  long double xx=x;
  __uint128_t *i;
  i=(__uint128_t *) &xx;
  i[0]+=(x>0.0 ? 1 : -1);
  return xx;
}

inline long double nextbefore (const long double x)
{
  if(!isfinite(x)) return nan("");
  if(x==0.0) return -DBL_MIN;
  long double xx=x;
  __uint128_t *i;
  i=(__uint128_t *) &xx;
  i[0]+=(x>0.0 ? -1 : 1);
  return xx;
}

// most of the operators aren't defined yet
class int_double{
public:
  long double left;
  long double right;

inline  int_double ()                      // constructors
  {
  };
// does no rounding, see below
inline int_double(long double l)
{
  left=l;
  right=l;
};

// N.B. this default contructor does no rounding.
// Note that the compiler probably rounds to nearest
// e.g. third=1.0/3.0; int_third=int_double(third,third);
//      results in a point interval at nearest to 1/3.
//
// you probably want int_third=int_double(1.0)/3.0;
inline int_double(long double l,long double r)
{

    if(l>r)
    {

      cout<<"Error constructing int_double, rightError constructing int_double, right "<<r<<" < "<<l<<". Exiting";
      exit(1);
    };

    left=l;
    right=r;
}

   friend int_double operator + (const int_double &lhs, const int_double &rhs);
   friend int_double operator + (const int_double &lhs, const long double &rhs);
   friend int_double operator - (const int_double &lhs, const int_double &rhs);
   friend int_double operator - (const int_double &lhs, const long double &rhs);
   friend int_double operator - (const int_double &lhs);
   friend int_double operator * (const int_double &lhs, const int_double &rhs);
   friend int_double operator * (const int_double &lhs, const long double &rhs);
  friend int_double operator / (const int_double &lhs, const int_double &rhs);
  friend int_double operator / (const int_double &lhs, const long double &rhs);
  friend int_double operator += (int_double &lhs, const int_double &rhs);
  friend int_double operator += (int_double &lhs, const long double &rhs);
  friend int_double operator -= (int_double &lhs, const int_double &rhs);
  friend int_double operator -= (int_double &lhs, const long double &rhs);
  friend int_double operator *= (int_double &lhs, const int_double &rhs);
  friend int_double operator *= (int_double &lhs, const long double &rhs);
  friend int_double operator /= (int_double &lhs, const int_double &rhs);
  friend int_double operator /= (int_double &lhs, const long double &rhs);
  friend int operator >= (const int_double &lhs, const int_double &rhs);
  friend int operator > (const int_double &lhs, const int_double &rhs);
  friend int operator < (const int_double &lhs, const int_double &rhs);
  friend ostream& operator<<(ostream &os, const int_double &x);
}; // end class

inline void print_int_double(const int_double &x)
{
  std::cout<<setprecision(50)<<scientific<<"["<<x.left<<","<<x.right<<"]";
  // printf("[%20.18e,%20.18e]",x.left,x.right);
};

inline int_double operator + (const int_double &lhs, const int_double &rhs)
{
  int_double temp;
  temp.left=nextbefore(lhs.left+rhs.left);
  temp.right=nextafter(lhs.right+rhs.right);
  return(temp);
}

inline int_double operator += (int_double &lhs, const int_double &rhs)
{
  lhs=rhs+lhs;
  return lhs;
}

inline int_double operator += (int_double &lhs, const long double &rhs) {
  int_double temp;
  temp.left = lhs.left + rhs;
  temp.right = lhs.right + rhs;
  return (temp);
}

// unary minus
inline int_double operator - (const int_double &x)
{
  return int_double(-x.right,-x.left);
}

inline int_double operator - (const int_double &lhs, const int_double &rhs)
{
  int_double temp;
  temp.left=nextbefore(lhs.left-rhs.left);
  temp.right=nextafter(lhs.right-rhs.right);
  return(temp);
}

inline int_double operator * (const int_double &lhs, const int_double &rhs)
{
  long double a=lhs.left*rhs.left;
  long double b=lhs.left*rhs.right;
  long double c=lhs.right*rhs.left;
  long double d=lhs.right*rhs.right;
  long double mx=max(a,b,c,d);
  long double mn=min(a,b,c,d);
  return int_double(nextbefore(mn),nextafter(mx));
}

inline ostream& operator<<(ostream &os, const int_double &x) {
  os<<setprecision(36)<<scientific<<"["<<x.left<<","<<x.right<<"]";
  return os;
}

inline bool contains_zero(const int_double &x)
{
  return (x.left<=0.0) && (x.right>=0.0);
}

inline int_double inv(const int_double &x)
{
  if(x.left<=0.0)
    {
      if(x.right>=0)
	return int_double(-nan(""),nan(""));
      else
	return int_double(nextbefore(1.0/x.right),nextafter(1.0/x.left));
    }
  return int_double(nextbefore(1.0/x.left),nextafter(1.0/x.right));
}

inline int_double operator / (const int_double &lhs, const int_double &rhs)
{
  if(contains_zero(rhs))
    return int_double(-nan(""),nan(""));
  long double a=lhs.left/rhs.left;
  long double b=lhs.left/rhs.right;
  long double c=lhs.right/rhs.left;
  long double d=lhs.right/rhs.right;
  long double mx=max(a,b,c,d);
  long double mn=min(a,b,c,d);
  return int_double(nextbefore(mn),nextafter(mx));
}

inline int_double log_two_sided(const int_double &x)
{
  return int_double(log_rd(x.left),log_ru(x.right));
}

inline int_double log(const int_double &x)
{
  if(x.left==x.right) // faster?
    {
      long double rd=log_rd(x.left);
      return int_double(rd,nextafter(rd));
    }
  return log_two_sided(x);
}


#endif
