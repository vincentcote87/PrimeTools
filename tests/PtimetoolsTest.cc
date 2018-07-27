#include "gtest/gtest.h"
#include "Primetools.h"

TEST (PiTest, pi_10) {
  EXPECT_EQ(primetools::getPi(10), 4);
}

TEST (PiTest, pi_100) {
  EXPECT_EQ(primetools::getPi(100), 25);
}

TEST (ThetaTest, theta_10) {
  int_double a = primetools::calculateTheta(10);
  int_double b = log(2*3*5*7);
  long double r = a.right - b.right;
  long double l = a.left - b.left;
  long double tolerance = 0.000000000001;
  EXPECT_TRUE(r <= tolerance && l <= tolerance);
}

TEST (ThetaTest, theta_1) {
  EXPECT_TRUE(primetools::calculateTheta(1).right == 0.0 && primetools::calculateTheta(1).left == 0.0);
}

TEST (PsiTest, psi_10) {
  int_double a = primetools::calculatePsi(10);
  int_double b = log(2*3*2*5*7*2*3);
  long double r = a.right - b.right;
  long double l = a.left - b.left;
  long double tolerance = 0.000000000001;
  EXPECT_TRUE(r <= tolerance && l <= tolerance);
}

TEST (PsiTest, Psi_10) {
  mpfr::mpreal a = primetools::calculatePsiNoTheta(10);
  mpfr::mpreal b = log(2*3*2*5*7*2*3);
  long double variation = 0.0000000001;
  EXPECT_TRUE(a - b <= variation || a - b >= -variation);
}
