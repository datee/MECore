//
// Created by ryen on 12/7/24.
//

#ifndef ASSETBASE_H
#define ASSETBASE_H

#include "haxe/HaxeEngineObject.h"

namespace me::asset {
    class AssetBase : public haxe::HaxeEngineObject {
        // some kind of guid
        // a collection of sub-assets

        public:
        explicit AssetBase(const haxe::TypeName& typeName, const bool preserve = true) : haxe::HaxeEngineObject(typeName, preserve) {}
    };
}

#endif //ASSETBASE_H
