#pragma once
#ifndef _DYNOBJ_H_
#define _DYNOBJ_H_

#include <string>
#include <functional> // std::hash
#include "dyno.hpp"

class FieldDefTest;

struct FieldDef;
typedef std::shared_ptr<FieldDef> SPFieldDef;

struct FieldDef {
  DynType       typeId;
  std::string   name;
  uint32_t      id;
  uint32_t      schemaId;  // default=0 (e.g. same as Row.schemaId)
  size_t        _hashCode;

  static const SPFieldDef alloc(DynType typeId_, std::string name_, uint32_t id_ = 0) {
    FieldDef *tmp = new FieldDef(typeId_, name_, id_, 0);
    return std::shared_ptr<FieldDef>(tmp);
//    return std::make_shared<FieldDef>(typeId_, name_, id_, 0);
  }
  static const SPFieldDef alloc(DynType typeId_, uint32_t id_, uint32_t schemaId_) {
    FieldDef *tmp = new FieldDef(typeId_, "", id_, schemaId_);
    return std::shared_ptr<FieldDef>(tmp);
//    return std::make_shared<FieldDef>(typeId_, "", id_, schemaId_);
  }

  bool operator<(const FieldDef &b) const {
    return (_hashCode < b._hashCode);
  }

private:
  FieldDef(DynType typeId_, std::string name_,
    uint32_t id_, uint32_t schemaId_) : typeId(typeId_), name(name_),
    id(id_), schemaId(schemaId_) {

    _hashCode = calcHash();
  }

  size_t calcHash() {
    char tmp[128];
    snprintf(tmp, sizeof(tmp), "%x%x%x", typeId, id, schemaId);

    std::string s = name;
    s += tmp;

    std::hash<std::string> hash_fn;
    return hash_fn(s);
  }

friend FieldDefTest;
};


typedef std::map<SPFieldDef, DynVal> DynMap;

#endif // _DYNOBJ_H_
