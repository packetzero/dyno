#pragma once
#ifndef _DYNOBJ_H_
#define _DYNOBJ_H_

#include <string>
#include <map>
#include <functional> // std::hash
#include <memory>
#include "dyno.hpp"

struct SchemaId {
  uint32_t schemaId;
  std::string schemaName;

  SchemaId(std::string name, uint32_t id=0) : schemaId(id), schemaName(name) {}
};

typedef std::shared_ptr<SchemaId> SPSchemaId;

// forward declarations for alloc

class FieldDefTest;
struct FieldDef;
typedef std::shared_ptr<FieldDef> SPFieldDef;

/*
 * FieldDef is a typed identifier of a table column or object field.
 * The application uses a string name or integer id to identify the field.
 * If the application uses schema-relative name or identifiers, then it can
 * make the identifiers globally unique by using the optional schemaId field
 * or prefixing name with table/object name.
 *
 * For example:
 *   name : "name" => name : "person.name"
 *   id : 2 => schemaId : 4, id : 2
 *
 * Applications should only use alloc() to receive a const shared_ptr to the
 * FieldDef.
 */
struct FieldDef {
  DynType       typeId;
  std::string   name;
  uint32_t      id;
  SPSchemaId    schema;

  static const SPFieldDef alloc(DynType typeId_, std::string name_, uint32_t id_ = 0) {
    FieldDef *tmp = new FieldDef(typeId_, name_, id_, nullptr);
    return std::shared_ptr<FieldDef>(tmp);
  }
  static const SPFieldDef alloc(DynType typeId_, uint32_t id_, SPSchemaId schema_ = nullptr) {
    FieldDef *tmp = new FieldDef(typeId_, "", id_, schema_);
    return std::shared_ptr<FieldDef>(tmp);
  }
  static const SPFieldDef alloc(DynType typeId_, std::string name_, uint32_t id_, SPSchemaId schema_ = nullptr) {
    FieldDef *tmp = new FieldDef(typeId_, name_, id_, schema_);
    return std::shared_ptr<FieldDef>(tmp);
  }
  static const SPFieldDef alloc(DynType typeId_, std::string name_, SPSchemaId schema_) {
    FieldDef *tmp = new FieldDef(typeId_, name_, 0, schema_);
    return std::shared_ptr<FieldDef>(tmp);
  }

  bool valid() const {
    return (typeId != TNONE && typeId < NUM_TYPES);
  }

protected:
  FieldDef(DynType typeId_, std::string name_,
    uint32_t id_, SPSchemaId schema_) : typeId(typeId_), name(name_),
    id(id_), schema(schema_) {
  }

friend FieldDefTest;
};

/*
 * DynMap is a typed map of DynVal
 * Rather than using map<string,string>, DynMap
 * Allows the values to be flexible types, and the keys can
 * be an id or string.
 * Using const SPFieldDef provides a few advantages:
 * - speed: pointer comparison rather than string comparison in map indexing
 * - memory: shared names, rather than multiple string copies
 * - names are defined once, no chance to misspell throughout code
 */
typedef std::map<const SPFieldDef, DynVal> DynMap;

class Dyno {
public:

/**
 * Normalize will take an DynMap object and convert the values to match
 * the SPFieldDef types.
 */
static void Normalize(DynMap &obj) {
  for (auto it = obj.begin(); it != obj.end(); it++) {
    const SPFieldDef spf = it->first;
    if (spf->typeId != it->second.type()) {
      DYN_TO(it->second, spf->typeId, obj[spf]);
    }
  }
}
}; // class dyno

#endif // _DYNOBJ_H_
