#include <gtest/gtest.h>
#include "../include/dynobj.hpp"

class DynObjTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
};


TEST_F(DynObjTest, basic_string) {
  DynMap obj;

  const SPFieldDef NAME = FieldDef::alloc(TSTRING, "person.name");
  obj[NAME] = "Tommy";

  ASSERT_EQ(1,obj.size());
  auto dval = obj[NAME];
  ASSERT_TRUE("Tommy" == dval.as_s());
  ASSERT_TRUE("Tommy" == (std::string)obj[NAME]);
  ASSERT_EQ(obj[NAME], "Tommy");
  ASSERT_EQ(obj[NAME].type(), TSTRING);
}

TEST_F(DynObjTest, basic_ints) {
  DynMap obj;
  
  const SPFieldDef AGE = FieldDef::alloc(TINT32, "age");
  obj[AGE] = "32";

  int int1 = obj[AGE].as_i32();
  ASSERT_EQ(32, int1);
  ASSERT_EQ(32, (int32_t)obj[AGE]);
}
