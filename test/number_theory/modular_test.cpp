//          Copyright Diego Ramírez November 2014, May 2015
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <djp/number_theory/modular.hpp>
#include <gtest/gtest.h>

#include <djp/number_theory/euclid.hpp> // for djp:gcd
#include <cstdint> // For INT64_MAX, UINT64_MAX

using namespace djp;

TEST(ModSumTest, WorksWell) {
  EXPECT_EQ(20, mod_sum(10, 10, 31));
  EXPECT_EQ(9, mod_sum(20, 20, 31));
  EXPECT_EQ(30, mod_sum(19, 11, 31));
  EXPECT_EQ(0, mod_sum(19, 12, 31));
  EXPECT_EQ(1, mod_sum(19, 13, 31));

  EXPECT_EQ(UINT64_MAX - 3,
            mod_sum(UINT64_MAX / 2 - 2, UINT64_MAX / 2, UINT64_MAX));
  EXPECT_EQ(UINT64_MAX - 2,
            mod_sum(UINT64_MAX / 2 - 1, UINT64_MAX / 2, UINT64_MAX));
  EXPECT_EQ(UINT64_MAX - 1,
            mod_sum(UINT64_MAX / 2 + 0, UINT64_MAX / 2, UINT64_MAX));
  EXPECT_EQ(0, mod_sum(UINT64_MAX / 2 + 1, UINT64_MAX / 2, UINT64_MAX));
  EXPECT_EQ(1, mod_sum(UINT64_MAX / 2 + 2, UINT64_MAX / 2, UINT64_MAX));
  EXPECT_EQ(2, mod_sum(UINT64_MAX / 2 + 3, UINT64_MAX / 2, UINT64_MAX));

  EXPECT_EQ(UINT64_MAX - 7,
            mod_sum(UINT64_MAX - 3, UINT64_MAX - 4, UINT64_MAX));
}

TEST(ModMulTest, WorksWell) {
  EXPECT_EQ(1500, mod_mul(15, 100, 2000));
  EXPECT_EQ(500, mod_mul(15, 100, 1000));

  EXPECT_EQ(121704964, mod_mul<long long>(123897123, 12387123982, 123412421));
  EXPECT_EQ(5306660808504233892,
            mod_mul<long long>(983475987235822983, 3234987329847383934,
                               6473292374838378342));
  EXPECT_EQ(
      160348183393232245,
      mod_mul<long long>(5624398623487263287, 2340923408932939303, INT64_MAX));

  EXPECT_EQ(1, mod_mul(UINT64_MAX - 1, UINT64_MAX - 1, UINT64_MAX));
  EXPECT_EQ(12, mod_mul(UINT64_MAX - 3, UINT64_MAX - 4, UINT64_MAX));
  EXPECT_EQ(101, mod_mul(UINT64_MAX - 1, UINT64_MAX - 101, UINT64_MAX));
  EXPECT_EQ(350, mod_mul(UINT64_MAX - 35, UINT64_MAX - 10, UINT64_MAX));
}

TEST(ModPowTest, WorksWhenOverflowDoesNotNeedControl) {
  EXPECT_EQ(90, mod_pow(2342, 14233, 2011));
  EXPECT_EQ(10817, mod_pow(2017, 1238912398, 65536));
  EXPECT_EQ(12, mod_pow(22342, 1238912398, 13));
  EXPECT_EQ(8001, mod_pow(25237, 131312, 65536));
}

namespace {
class ModInverseTest : public ::testing::Test {
  using int_t = long;
  int_t mod = 11;

protected:
  int_t normalize(int_t x) const {
    x %= mod;
    return x < 0 ? x + mod : x;
  }
  void set_mod(int_t m) {
    assert(m > 0);
    mod = m;
  }
  void check_inverses(int_t x, int_t y) const {
    ASSERT_EQ(1, gcd(x, mod));
    ASSERT_EQ(1, gcd(y, mod));
    const int_t inv_x = mod_inverse(x, mod);
    const int_t inv_y = mod_inverse(y, mod);
    EXPECT_EQ(normalize(y), inv_x);
    EXPECT_EQ(normalize(x), inv_y);
    EXPECT_EQ(1 % mod, mod_mul(normalize(x), normalize(y), mod));
  }
  void check_non_invertible(int_t x) const {
    ASSERT_NE(1, gcd(x, mod));
    EXPECT_EQ(mod, mod_inverse(x, mod));
  }
};
} // end anonymous namespace

TEST_F(ModInverseTest, PrimeModulesTest) {
  set_mod(2), check_inverses(1, 1);
  set_mod(3), check_inverses(2, 2);
  set_mod(7), check_inverses(2, 4);
  set_mod(47), check_inverses(6, 8);
  set_mod(373), check_inverses(17, 22);
  set_mod(7919), check_inverses(55, 144);
  set_mod(1000000007), check_inverses(504, 1984127);
  set_mod(2147483647), check_inverses(32768, 65536);
}

TEST_F(ModInverseTest, NonPrimeModulesTest) {
  set_mod(1), check_inverses(0, 0);
  set_mod(4), check_inverses(1, 1);
  set_mod(8), check_inverses(3, 3);
  set_mod(9), check_inverses(2, 5);

  set_mod(63);
  check_inverses(1, 1);
  check_inverses(2, 32);
  check_inverses(4, 16);
  check_inverses(8, 8);
  check_inverses(1, 64);
  check_inverses(1, 190);
  check_inverses(2, 95);
  check_inverses(1, 316);
  check_inverses(2, 158);
  check_inverses(4, 79);

  // 585,690,336 = 2^5 * 3^2* 7^5 * 11^2
  // 585,690,335 = 5 * 617 * 189851
  set_mod(585690335);
  check_inverses(1089, 537824);
  check_inverses(363, 1613472);
  check_inverses(4312, 135828);
  check_inverses(12936, 45276);
  check_inverses(17248, 33957);
  check_inverses(539, 1086624);
  check_inverses(3696, 158466);
  check_inverses(3872, 151263);
  check_inverses(2, 292845168);
}

TEST_F(ModInverseTest, OutsideBoundsTest) {
  // 2118588821 = 683 * 823 * 3769
  set_mod(2118588821);

  check_non_invertible(0);
  check_non_invertible(683);
  check_non_invertible(823);
  check_non_invertible(3769);
  check_non_invertible(-393854880);
  check_non_invertible(-2143446713);
  check_non_invertible(770251461);
  check_non_invertible(1599487648);

  check_inverses(-133711905, 1383926620);
  check_inverses(-372047867, 724363770);
  check_inverses(-404620562, 362006296);
  check_inverses(-708632711, 1104498801);
  check_inverses(-795755684, 229364503);
  check_inverses(33378331, 581869302);
  check_inverses(545404204, 778808546);
  check_inverses(949333985, 958761031);

  // 5201843 = 2017 * 2579
  set_mod(5201843);

  check_non_invertible(0);
  check_non_invertible(2017);
  check_non_invertible(2579);
  check_non_invertible(56476);
  check_non_invertible(79941263);
  check_non_invertible(1407993071);
  check_non_invertible(-923786);
  check_non_invertible(-1082713498);

  check_inverses(-795755684, 4601445);
  check_inverses(4892046, 581869302);
  check_inverses(-404620562, 4309062);
  check_inverses(-708632711, 3159960);
  check_inverses(878686, 545404204);
  check_inverses(-133711905, 2535877);
  check_inverses(-372047867, 2692923);
  check_inverses(1143855, 949333985);
  check_inverses(-1579004998, 4763700);
  check_inverses(2615886, 1323567403);
}
