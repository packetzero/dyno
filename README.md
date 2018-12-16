# dyno - Dynamic Typed Objects and Map
This is a C++11 header-only library for dynamically typed objects without using templates.  Read on and you will see why using this library is easier than using boost::any<> if your datatypes can be limited to primitives and string.

## DynVal
DynVal is a simple object that uses assignment and type casting operators to contain primitives and std::string.
Using it is easy:
```
DynVal val = 1234;  // type() == TINT32
val.as_s();         // to string
val = "1234";       // type() now TSTRING
val.as_i32();       // coerce to int32
(int32_t)val;       // coerce using cast
```

## DynMap
C++ Applications that gather and report data in JSON format, or communicate with other
processes often resort to map<string,string>.  For large datasets, this can use up
extra memory for the repeating keys, and CPU for all of the marshaling.
DynMap is a map<const SPFieldDef,DynVal>, meaning the values can be any primitive type or string and
the keys are declared once and shared.  This has the following advantages:
 - speed: pointer comparison rather than string comparison in map indexing
 - memory: shared names, rather than multiple string copies
 - names are defined once, no chance to misspell throughout code
 - marshaling : Easier to use more efficient marshaling

## Normalize()
The `Normalize()` function will take a DynMap object and convert the values to
match the types defined in the keys (SPFieldDef).  Think of the FieldDefs as
the schema.  This puts the conversion into a single step, and the application
can then use the DynMap values as the schema defines to marshal the data without
worrying about conversion each encountered value.

```
// app defines schema for fields
static const SPFieldDef NAME = FieldDef::alloc(TSTRING, "name");
static const SPFieldDef NUMBER = FieldDef::alloc(TUINT32, "number");
static const SPFieldDef ACTIVE = FieldDef::alloc(TUINT8, "active");
static const SPFieldDef UID = FieldDef::alloc(TINT64, "uid");
static const SPFieldDef HEIGHT = FieldDef::alloc(TINT32, "height");

TEST_F(DynObjTest, normalize) {
  DynMap obj;

  // app assigns values in flexible manner

  obj[NAME] = "Kareem";
  obj[NUMBER] = 33;
  obj[ACTIVE] = false;
  obj[UID] = 2348429;
  obj[HEIGHT] = "86";

  // current types based on assignments

  ASSERT_EQ(TINT32, obj[NUMBER].type());
  ASSERT_EQ(TINT32, obj[ACTIVE].type());
  ASSERT_EQ(TINT32, obj[UID].type());
  ASSERT_EQ(TSTRING, obj[HEIGHT].type());

  Normalize(obj);

  // types should now match FieldDef

  ASSERT_EQ(TUINT32, obj[NUMBER].type());
  ASSERT_EQ(TUINT8, obj[ACTIVE].type());
  ASSERT_EQ(TINT64, obj[UID].type());
  ASSERT_EQ(TINT32, obj[HEIGHT].type());
```
