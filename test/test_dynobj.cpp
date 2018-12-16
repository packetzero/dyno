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

  const SPFieldDef NUMBER = FieldDef::alloc(TINT32, "age");
  obj[NUMBER] = "32";

  int int1 = obj[NUMBER].as_i32();
  ASSERT_EQ(32, int1);
  ASSERT_EQ(32, (int32_t)obj[NUMBER]);
}

TEST_F(DynObjTest, multifield) {
  DynMap obj;

  const SPFieldDef NAME = FieldDef::alloc(TSTRING, "name");
  const SPFieldDef NUMBER = FieldDef::alloc(TINT32, "number");
  const SPFieldDef ACTIVE = FieldDef::alloc(TUINT8, "active");
  obj[NAME] = "Kareem";
  obj[NUMBER] = 33;
  obj[ACTIVE] = false;

  ASSERT_EQ(obj[NAME], "Kareem");
  ASSERT_EQ(obj[NUMBER], 33);
  ASSERT_EQ(0, (uint8_t)obj[ACTIVE]);
  ASSERT_EQ(obj[ACTIVE], (uint8_t)false);
}

static const SPFieldDef UID = FieldDef::alloc(TINT64, "uid");
static const SPFieldDef HEIGHT = FieldDef::alloc(TINT32, "height");

TEST_F(DynObjTest, normalize) {
  DynMap obj;

  const SPFieldDef NAME = FieldDef::alloc(TSTRING, "name");
  const SPFieldDef NUMBER = FieldDef::alloc(TUINT32, "number");
  const SPFieldDef ACTIVE = FieldDef::alloc(TUINT8, "active");
  // other fields described staticly above

  obj[NAME] = "Kareem";
  obj[NUMBER] = 33;
  obj[ACTIVE] = false;
  obj[UID] = 2348429;
  obj[HEIGHT] = "86";

  // current types based on assignments

  ASSERT_EQ(TSTRING, obj[NAME].type());
  ASSERT_EQ(TINT32, obj[NUMBER].type());
  ASSERT_EQ(TINT32, obj[ACTIVE].type());
  ASSERT_EQ(TINT32, obj[UID].type());
  ASSERT_EQ(TSTRING, obj[HEIGHT].type());

  Dyno::Normalize(obj);

  // types should now match FieldDef

  ASSERT_EQ(TSTRING, obj[NAME].type());
  ASSERT_EQ(TUINT32, obj[NUMBER].type());
  ASSERT_EQ(TUINT8, obj[ACTIVE].type());
  ASSERT_EQ(TINT64, obj[UID].type());
  ASSERT_EQ(TINT32, obj[HEIGHT].type());

  // sanity check on values

  ASSERT_EQ(obj[NAME], "Kareem");
  ASSERT_EQ(obj[NUMBER], 33);
  ASSERT_EQ(0, (uint8_t)obj[ACTIVE]);
  int64_t uid64 = 2348429;
  ASSERT_EQ(obj[UID], uid64);
  ASSERT_EQ(obj[HEIGHT], 86);
}
