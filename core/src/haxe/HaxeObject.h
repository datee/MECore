//
// Created by ryen on 12/24/24.
//

#ifndef HAXEOBJECT_H
#define HAXEOBJECT_H

#include <memory>
#include "HaxeCommon.h"

namespace me::haxe {
    class HaxeType;

    class HaxeObject {
        private:
        HaxeType* type;
        hl_type* vmType;
        hl_module* module;
        vdynamic* object;

        public:
        HaxeObject(HaxeType* type, hl_type* vmType, hl_module* module, vdynamic* obj);
        ~HaxeObject();

        [[nodiscard]] inline vdynamic* GetDynamic() const { return object; }

        [[nodiscard]] inline int GetInt(const FieldName& name) const { return hl_dyn_geti(object, hl_hash_utf8(name.c_str()), vmType); }
        [[nodiscard]] inline float GetFloat(const FieldName& name) const { return hl_dyn_getf(object, hl_hash_utf8(name.c_str())); }
        [[nodiscard]] inline double GetDouble(const FieldName& name) const { return hl_dyn_getd(object, hl_hash_utf8(name.c_str())); }
        [[nodiscard]] inline void* GetPtr(const FieldName& name) const { return hl_dyn_getp(object, hl_hash_utf8(name.c_str()), vmType); }

        inline void SetInt(const FieldName& name, int value) const { hl_dyn_seti(object, hl_hash_utf8(name.c_str()), vmType, value); }
        inline void SetFloat(const FieldName& name, float value) const { hl_dyn_setf(object, hl_hash_utf8(name.c_str()), value); }
        inline void SetDouble(const FieldName& name, double value) const { hl_dyn_setd(object, hl_hash_utf8(name.c_str()), value); }
        inline void SetPtr(const FieldName& name, void* value) const { hl_dyn_setp(object, hl_hash_utf8(name.c_str()), vmType, value); }
        inline void SetPtr(const FieldName& name, HaxeObject* value) const { hl_dyn_setp(object, hl_hash_utf8(name.c_str()), vmType, value->object); }

        vdynamic* CallMethod(const FuncName& name, FuncArgs args) const;
        vdynamic* CallVirtualMethod(const FuncName& name, FuncArgs args) const;
    };

    typedef std::shared_ptr<HaxeObject> HaxeObjectPtr;
}

#endif //HAXEOBJECT_H
