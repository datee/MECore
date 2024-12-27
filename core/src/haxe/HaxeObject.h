//
// Created by ryen on 12/24/24.
//

#ifndef HAXEOBJECT_H
#define HAXEOBJECT_H

#include <memory>
#include <string>
#include <vector>

#define HAXE_INCLUDE
extern "C" {
#include <hl.h>
#include <hlmodule.h>
}

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

        [[nodiscard]] inline int GetInt(const std::string& name) const { return hl_dyn_geti(object, hl_hash_utf8(name.c_str()), vmType); }
        [[nodiscard]] inline float GetFloat(const std::string& name) const { return hl_dyn_getf(object, hl_hash_utf8(name.c_str())); }
        [[nodiscard]] inline double GetDouble(const std::string& name) const { return hl_dyn_getd(object, hl_hash_utf8(name.c_str())); }
        [[nodiscard]] inline void* GetPtr(const std::string& name) const { return hl_dyn_getp(object, hl_hash_utf8(name.c_str()), vmType); }

        inline void SetInt(const std::string& name, int value) const { hl_dyn_seti(object, hl_hash_utf8(name.c_str()), vmType, value); }
        inline void SetFloat(const std::string& name, float value) const { hl_dyn_setf(object, hl_hash_utf8(name.c_str()), value); }
        inline void SetDouble(const std::string& name, double value) const { hl_dyn_setd(object, hl_hash_utf8(name.c_str()), value); }
        inline void SetPtr(const std::string& name, void* value) const { hl_dyn_setp(object, hl_hash_utf8(name.c_str()), vmType, value); }
        inline void SetPtr(const std::string& name, HaxeObject* value) const { hl_dyn_setp(object, hl_hash_utf8(name.c_str()), vmType, value->object); }

        vdynamic* CallMethod(const std::u16string& name, std::vector<vdynamic*> args) const;
        vdynamic* CallVirtualMethod(const std::u16string& name, std::vector<vdynamic*> args) const;
    };

    typedef std::shared_ptr<HaxeObject> HaxeObjectPtr;
}

#endif //HAXEOBJECT_H
