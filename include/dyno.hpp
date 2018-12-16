#pragma once
#ifndef _DYNO_H_
#define _DYNO_H_

#include <math.h>
#include <stdint.h>
#include <string>

enum DynType {
    TNONE,
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
  DynType  type() { return typeId; }
  bool     valid() const { return typeId != TNONE; }

  void operator=(const std::string s) { typeId=TSTRING; strval = s; }
  void operator=(const char * s) { typeId=TSTRING; strval = std::string(s); }

  void operator=(int8_t val) { typeId=TINT8; i8val=val; }
  void operator=(uint8_t val) { typeId=TUINT8; u8val=val; }
  void operator=(int16_t val) { typeId=TINT16; i16val=val; }
  void operator=(uint16_t val) { typeId=TUINT16; u16val=val; }
  void operator=(int32_t val) { typeId=TINT32; i32val=val; }
  void operator=(uint32_t val) { typeId=TUINT32; u32val=val; }
  void operator=(int64_t val) { typeId=TINT64; i64val=val; }
  void operator=(uint64_t val) { typeId=TUINT64; u64val=val; }
  void operator=(double val) { typeId=TFLOAT64; dval=val; }
  void operator=(float val) { typeId=TFLOAT32; dval=val; }

  DynVal() : typeId(DynType::TNONE), i64val(0), strval() {}
  DynVal(int32_t val) : typeId(TINT32), i32val(val), strval() {}
  DynVal(uint32_t val) : typeId(TUINT32), u32val(val), strval() {}
  DynVal(int64_t val) : typeId(TINT64), i64val(val), strval() {}
  DynVal(uint64_t val) : typeId(TUINT64), u64val(val), strval() {}
  DynVal(int16_t val) : typeId(TINT16), i16val(val), strval() {}
  DynVal(uint16_t val) : typeId(TUINT16), u16val(val), strval() {}
  DynVal(int8_t val) : typeId(TINT8), i8val(val), strval() {}
  DynVal(uint8_t val) : typeId(TUINT8), u8val(val), strval() {}
  DynVal(double val) : typeId(TFLOAT64), dval(val), strval() {}
  DynVal(float val) : typeId(TFLOAT32), dval(val), strval() {}
  DynVal(std::string val) : typeId(TSTRING), i64val(0), strval(val) {}
  DynVal(const char *val) : typeId(TSTRING), i64val(0), strval(std::string(val)) {}

  operator int8_t() const { return as_i8(); }
  operator uint8_t() const { return as_u8(); }
  operator int32_t() const { return as_i32(); }
  operator uint32_t() const { return as_u32(); }
  operator int64_t() const { return as_i64(); }
  operator uint64_t() const { return as_u64(); }
  operator double() const { return as_double(); }
  operator float() const { return as_float(); }
  operator const std::string() const { return as_s(); }
  operator std::string() { return as_s(); }

  bool operator==(const std::string& b) const { return b == as_s(); }
  bool operator==( std::string& b)  { return b == as_s(); }
  bool operator==(int32_t b) const { return b == as_i32(); }
  bool operator==(uint32_t b) const { return b == as_u32(); }
  bool operator==(int64_t b) const { return b == as_i64(); }
  bool operator==(uint64_t b) const { return b == as_u64(); }
  bool operator==(uint8_t b) const { return b == as_u8(); }
  bool operator==(int8_t b) const { return b == as_i8(); }
  bool operator==(double b) const { return b == as_double(); }
  bool operator==(float b) const { return b == as_float(); }

  int32_t as_i32() const {
    switch(typeId) {
      case TINT32:
        return i32val;
      case TUINT32:
        return (int32_t)u32val;
      case TINT8:
        return (int32_t)i8val;
      case TUINT8:
        return (int32_t)u8val;
      case TINT64:
        return (int32_t)i64val;
      case TUINT64:
        return (int32_t)u64val;
      case TFLOAT64:
        return (int32_t)floor(dval);
      case TSTRING:
        return (int32_t)atoi(strval.c_str());
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  uint32_t as_u32() const {
    switch(typeId) {
      case TUINT32:
        return u32val;
      case TINT32:
        return (uint32_t)i32val;
      case TINT8:
        return (uint32_t)i8val;
      case TUINT8:
        return (uint32_t)u8val;
      case TINT64:
        return (uint32_t)i64val;
      case TUINT64:
        return (uint32_t)u64val;
      case TFLOAT64:
        return (uint32_t)floor(dval);
      case TSTRING:
        return (uint32_t)atol(strval.c_str());
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  int64_t as_i64() const {
    switch(typeId) {
      case TINT64:
        return i64val;
      case TUINT64:
        return (int64_t)u64val;
      case TINT32:
        return (int64_t)i32val;
      case TUINT32:
        return (int64_t)u32val;
      case TINT8:
        return (int64_t)i8val;
      case TUINT8:
        return (int64_t)u8val;
      case TFLOAT64:
        return (int64_t)floor(dval);
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  uint64_t as_u64() const {
    switch(typeId) {
      case TUINT64:
        return u64val;
      case TINT64:
        return (uint64_t)i64val;
      case TINT32:
        return (uint64_t)i32val;
      case TUINT32:
        return (uint64_t)u32val;
      case TINT8:
        return (uint64_t)i8val;
      case TUINT8:
        return (uint64_t)u8val;
      case TFLOAT64:
        return (uint64_t)floor(dval);
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  float as_float() const {
    switch(typeId) {
      case TFLOAT32:
      case TFLOAT64:
        return (float)(dval);
      case TUINT64:
        return (float)u64val;
      case TINT64:
        return (float)i64val;
      case TINT32:
        return (float)i32val;
      case TUINT32:
        return (float)u32val;
      case TINT8:
        return (float)i8val;
      case TUINT8:
        return (float)u8val;
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  double as_double() const {
    switch(typeId) {
      case TFLOAT64:
        return dval;
      case TFLOAT32:
        return (double)dval;
      case TUINT64:
        return (double)u64val;
      case TINT64:
        return (double)i64val;
      case TINT32:
        return (double)i32val;
      case TUINT32:
        return (double)u32val;
      case TINT8:
        return (double)i8val;
      case TUINT8:
        return (double)u8val;
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }


  int8_t as_i8() const {
    switch(typeId) {
      case TINT8:
        return i8val;
      case TUINT8:
        return (int8_t)u8val;
      case TINT32:
        return (int8_t)i32val;
      case TUINT32:
        return (int8_t)u32val;
      case TINT64:
        return (int8_t)i64val;
      case TUINT64:
        return (int8_t)u64val;
      case TFLOAT64:
        return (int8_t)floor(dval);
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  uint8_t as_u8() const {
    switch(typeId) {
      case TUINT8:
        return u8val;
      case TINT8:
        return (uint8_t)i8val;
      case TINT32:
        return (uint8_t)i32val;
      case TUINT32:
        return (uint8_t)u64val;
      case TUINT64:
        return (uint8_t)u64val;
      case TINT64:
        return (uint8_t)i64val;
      case TFLOAT64:
        return (uint8_t)floor(dval);
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

  const std::string as_s() const {
    switch(typeId) {
      case TSTRING:
        return strval;
      case TINT32:
        return std::to_string(i32val);
      case TUINT32:
        return std::to_string(u32val);
      case TINT64:
        return std::to_string(i64val);
      case TUINT64:
        return std::to_string(u64val);
      case TFLOAT64:
        return std::to_string(dval);
      case TFLOAT32:
        return std::to_string(dval);
      case TINT8:
        return std::to_string(i8val);
      case TUINT8:
        return std::to_string(u8val);
      case TNONE:
      default:
        throw new std::runtime_error("unset");
        break;
    }
  }

protected:
  DynType  typeId;

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

#define DYN_TO(VAL, TYPEID, DEST) { \
  switch(TYPEID) { \
    case TINT32: \
      (DEST) = DynVal((VAL).as_i32()); \
      break; \
    case TUINT32: \
      (DEST) = DynVal((VAL).as_u32()); \
      break; \
    case TINT8: \
      (DEST) = DynVal((VAL).as_i8()); \
      break; \
    case TUINT8: \
      (DEST) = DynVal((VAL).as_u8()); \
      break; \
    case TINT64: \
      (DEST) = DynVal((VAL).as_i64()); \
      break; \
    case TUINT64: \
      (DEST) = DynVal((VAL).as_u64()); \
      break; \
    case TFLOAT64: \
      (DEST) = DynVal((VAL).as_double()); \
      break; \
    case TFLOAT32: \
      (DEST) = DynVal((VAL).as_float()); \
      break; \
    case TSTRING: \
      (DEST) = DynVal((VAL).as_s()); \
      break; \
    case TNONE: \
    default: \
      throw new std::runtime_error("unset"); \
      break; \
  } \
} // end macro DYN_TO()


#endif //_DYNO_H_
