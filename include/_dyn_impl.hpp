#pragma once

int32_t DynVal::as_i32() const {
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
    case TNONE:
    default:
      throw new std::runtime_error("unset");
      break;
  }
}

uint32_t DynVal::as_u32() const {
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
    case TNONE:
    default:
      throw new std::runtime_error("unset");
      break;
  }
}

int64_t DynVal::as_i64() const {
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

uint64_t DynVal::as_u64() const {
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

float DynVal::as_float() const {
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

double DynVal::as_double() const {
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


int8_t DynVal::as_i8() const {
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

uint8_t DynVal::as_u8() const {
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

const std::string DynVal::as_s() const {
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
