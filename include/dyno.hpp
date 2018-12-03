#pragma once

#include <stdint.h>
#include <string>


enum DynType {
    NONE,
    TSTRING,         // 1
    TINT32,          // 2
    TUINT32,         // 3
    TINT64,          // 4
    TUINT64,         // 5
    TINT16,          // 6
    TUINT16,         // 7
    TINT8,           // 8
    TUINT8,          // 9

    TFLOAT32,        // 10
    TFLOAT64,        // 11
    TBYTES,          // 12

    NUM_TYPES
};

struct DynVal {
public:
  DynType           getTypeEnum() const { return typeId; }

  uint8_t  as_u8() const;
  uint16_t as_u16() const;
  uint32_t as_u32() const;
  uint64_t as_u64() const;

  int8_t   as_i8() const;
  int16_t  as_i16() const;
  int32_t  as_i32() const;
  int64_t  as_i64() const;

  float   as_float() const;
  double  as_double() const;

  const std::string  as_s() const;

  void operator=(const std::string s);
  void operator=(int8_t val) { typeId=TINT8; i8val=val; }
  void operator=(uint8_t val) { typeId=TUINT8; u8val=val; }
  void operator=(int16_t val) { typeId=TINT16; i16val=val; }
  void operator=(uint16_t val) { typeId=TUINT16; u16val=val; }
  void operator=(int32_t val) { typeId=TINT32; i32val=val; }
  void operator=(uint32_t val) { typeId=TUINT32; u32val=val; }
  void operator=(int64_t val) { typeId=TINT64; i64val=val; }
  void operator=(uint64_t val) { typeId=TUINT64; u64val=val; }
  void operator=(double val) { typeId=TFLOAT64; dval=val; }

  DynVal() : typeId(DynType::NONE), i64val(0), strval() {}
  DynVal(int32_t val) : typeId(TINT32), i32val(val), strval() {}
  DynVal(uint32_t val) : typeId(TUINT32), u32val(val), strval() {}
  DynVal(int64_t val) : typeId(TINT64), i64val(val), strval() {}
  DynVal(uint64_t val) : typeId(TUINT64), u64val(val), strval() {}
  DynVal(int16_t val) : typeId(TINT16), i16val(val), strval() {}
  DynVal(uint16_t val) : typeId(TUINT16), u16val(val), strval() {}
  DynVal(int8_t val) : typeId(TINT8), i8val(val), strval() {}
  DynVal(uint8_t val) : typeId(TUINT8), u8val(val), strval() {}
  DynVal(double val) : typeId(TFLOAT64), dval(val), strval() {}
  DynVal(std::string val) : typeId(TSTRING), i64val(0), strval(val) {}

protected:
  DynType  typeId;
  bool isValid;

  union {
    int32_t  i32val;
    uint32_t u32val;
    int64_t  i64val;
    uint64_t u64val;
    int16_t  i16val;
    uint16_t  u16val;
    int8_t   i8val;
    uint8_t  u8val;
    double   dval;
  };
  std::string strval;
};

struct DynFieldMeta {
  uint32_t      id;
  uint32_t      schemaId;  // default=0 (e.g. same as Row.schemaId)
  DynType       typeId;
  std::string   name;
};

typedef std::shared_ptr<DynFieldMeta> SPFieldMeta;

struct DynValWithSchema : public DynVal {
  const SPFieldMeta getMeta();

  struct DynFieldMeta {
    uint32_t      id;
    uint32_t      schemaId;  // default=0 (e.g. same as Row.schemaId)
    DynType       typeId;
    std::string   name;
  };

  typedef std::shared_ptr<DynFieldMeta> SPFieldMeta;


}

struct DynObj {
  // has schema assigned?

  /**
   * @brief Used to access a row column value.
   * For example to access the "pid" column, use row["pid"].  To then set
   * that value, row["pid"] = 2345
   * @returns instance of a column value wrapper used to set the value.
   */
  const DynVal& operator[](const std::string columnName) const;
  const DynVal& operator[](int columnIndex) const;
  const DynVal& operator[](uint64_t columnIndex) const;
};
