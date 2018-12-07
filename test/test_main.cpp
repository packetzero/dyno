#include <gtest/gtest.h>
#include "../include/dyno.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int status= RUN_ALL_TESTS();
  return status;
}

class SetTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
};


TEST_F(SetTest, int32) {
  // construct assign
  DynVal v = 345;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TINT32, v.getTypeId());
  ASSERT_EQ(345,(int32_t)v);

  // equals assign

  v = DynVal();
  int32_t ival1 = 123456;
  v = ival1;
  ASSERT_EQ(TINT32, v.getTypeId());
  ASSERT_EQ(ival1, (int32_t)v);
  ASSERT_EQ(ival1, v.as_i32());

  // as_s
  ASSERT_EQ("123456", v.as_s());

  // repeat for negative

  int32_t ival2 = -123456;
  v = ival2;

  ASSERT_EQ(ival2, (int32_t)v);
  ASSERT_EQ(ival2, v.as_i32());
  ASSERT_EQ("-123456", v.as_s());

}


TEST_F(SetTest, uint32) {
  // construct assign
  DynVal v = 345U;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TUINT32, v.getTypeId());
  ASSERT_EQ(345U,(uint32_t)v);

  // equals assign

  v = DynVal();
  uint32_t ival1 = 123456;
  v = ival1;
  ASSERT_EQ(TUINT32, v.getTypeId());
  ASSERT_EQ(ival1, (uint32_t)v);
  ASSERT_EQ(ival1, v.as_u32());

  // as_s
  ASSERT_EQ("123456", v.as_s());
}

TEST_F(SetTest, int64) {
  // construct assign
  DynVal v = (int64_t)123456123123;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TINT64, v.getTypeId());
  ASSERT_EQ(123456123123,(int64_t)v);

  // equals assign

  v = DynVal();
  int64_t ival1 = 2123456123123;
  v = ival1;
  ASSERT_EQ(TINT64, v.getTypeId());
  ASSERT_EQ(ival1, (int64_t)v);
  ASSERT_EQ(ival1, v.as_i64());

  // as_s
  ASSERT_EQ("2123456123123", v.as_s());

  // repeat for negative

  int64_t ival2 = -2123456123123;
  v = ival2;

  ASSERT_EQ(ival2, (int64_t)v);
  ASSERT_EQ(ival2, v.as_i64());
  ASSERT_EQ("-2123456123123", v.as_s());
}

TEST_F(SetTest, uint64) {
  // construct assign
  DynVal v = (uint64_t)123456123123U;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TUINT64, v.getTypeId());
  ASSERT_EQ(123456123123U,(uint64_t)v);

  // equals assign

  v = DynVal();
  uint64_t ival1 = 2123456123123U;
  v = ival1;
  ASSERT_EQ(TUINT64, v.getTypeId());
  ASSERT_EQ(ival1, (uint64_t)v);
  ASSERT_EQ(ival1, v.as_u64());

  // as_s
  ASSERT_EQ("2123456123123", v.as_s());

}

TEST_F(SetTest, int8) {
  // construct assign
  DynVal v = (int8_t)123;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TINT8, v.getTypeId());
  ASSERT_EQ(123,(int8_t)v);

  // equals assign

  v = DynVal();
  int8_t ival1 = 29;
  v = ival1;
  ASSERT_EQ(TINT8, v.getTypeId());
  ASSERT_EQ(ival1, (int8_t)v);
  ASSERT_EQ(ival1, v.as_i8());

  // as_s
  ASSERT_EQ("29", v.as_s());

  // repeat for negative

  int8_t ival2 = -123;
  v = ival2;

  ASSERT_EQ(ival2, (int8_t)v);
  ASSERT_EQ(ival2, v.as_i8());
  ASSERT_EQ("-123", v.as_s());

}

TEST_F(SetTest, uint8) {
  // construct assign
  DynVal v = (uint8_t)223;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TUINT8, v.getTypeId());
  ASSERT_EQ(223,(uint8_t)v);

  // equals assign

  v = DynVal();
  uint8_t ival1 = 222;
  v = ival1;
  ASSERT_EQ(TUINT8, v.getTypeId());
  ASSERT_EQ(ival1, (uint8_t)v);
  ASSERT_EQ(ival1, v.as_u8());

  // as_s
  ASSERT_EQ("222", v.as_s());
}

TEST_F(SetTest, doubles) {
  // construct assign
  double dval = 12345678.9;
  DynVal v = dval;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TFLOAT64, v.getTypeId());
  ASSERT_EQ(dval,(double)v);

  // equals assign

  v = DynVal();
  dval = 98765.4321;
  v = dval;
  ASSERT_EQ(TFLOAT64, v.getTypeId());
  ASSERT_EQ(dval, (double)v);
  ASSERT_EQ(dval, v.as_double());

  // as_s
  const std::string s = v.as_s();
  // can have trailing 0's in decimal, so search for substring
  ASSERT_TRUE(s.find("98765.4321") != std::string::npos);

  // repeat for negative

  dval = -98765.4321;
  v = dval;

  ASSERT_EQ(TFLOAT64, v.getTypeId());
  ASSERT_EQ(dval, (double)v);
  ASSERT_EQ(dval, v.as_double());

  const std::string s2 = v;
  // can have trailing 0's in decimal, so search for substring
  ASSERT_TRUE(s2.find("-98765.4321") != std::string::npos);
}

TEST_F(SetTest, floats) {
  // construct assign
  float dval = 12345.9;
  DynVal v = dval;
  ASSERT_TRUE(v.valid());
  ASSERT_EQ(TFLOAT32, v.getTypeId());
  ASSERT_EQ(dval,(float)v);

  // equals assign

  v = DynVal();
  dval = 987.4321;
  v = dval;
  ASSERT_EQ(TFLOAT32, v.getTypeId());
  ASSERT_EQ(dval, (float)v);
  ASSERT_EQ(dval, v.as_float());

  // as_s
  const std::string s = v.as_s();
  // can have trailing 0's in decimal, so search for substring
  ASSERT_TRUE(s.find("987.4321") != std::string::npos);

  // repeat for negative

  dval = -987.4321;
  v = dval;

  ASSERT_EQ(TFLOAT32, v.getTypeId());
  ASSERT_EQ(dval, (float)v);
  ASSERT_EQ(dval, v.as_float());

  const std::string s2 = v;
  // can have trailing 0's in decimal, so search for substring
  ASSERT_TRUE(s2.find("-987.4321") != std::string::npos);
}
