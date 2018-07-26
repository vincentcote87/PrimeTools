#include "gtest/gtest.h"
#include "../include/Primetools.h"
#include "../include/PsiTools.h"
#include "../include/s2.h"

#include <iostream>

TEST (B2Test, bernoulliSize) {
  EXPECT_EQ(B2.size(), 12);
}

TEST (B2Test, bernoulliValue_of_2) {
  mpfr::mpreal::set_default_prec(192);
  EXPECT_TRUE(B2[1] - 1.0/6.0 <= 0.000000000001);
}

TEST (B2Test, bernoulliValue_of_10) {
  EXPECT_TRUE(B2[4] - 5.0/66.0 <= 0.000000000001);
}
