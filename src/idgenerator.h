#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include<vector>
#include "vector2d.h"
#include<list>
#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

class IDGenerator{
   public:
      static IDGenerator * instance ();
      int next () { return _id++; }

   private:
      IDGenerator () : _id(0) {}
      static IDGenerator * only_copy;
      int _id;
};

IDGenerator * IDGenerator::instance(){
   if (!only_copy) {
      only_copy = new IDGenerator();
   }
   return only_copy;
}

IDGenerator * IDGenerator::only_copy;
#endif // IDGENERATOR_H
