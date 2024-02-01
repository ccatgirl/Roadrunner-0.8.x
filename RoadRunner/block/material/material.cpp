#include <block/material/material.hpp>

using RoadRunner::block::material::Material;
Material
    *Material::air,
    *Material::dirt,
    *Material::wood,
    *Material::stone,
    *Material::metal,
    *Material::water,
    *Material::lava,
    *Material::leaves,
    *Material::plant,
    *Material::replaceable_plant,
    *Material::sponge,
    *Material::cloth,
    *Material::fire,
    *Material::sand,
    *Material::decoration,
    *Material::glass,
    *Material::explosive,
    *Material::coral,
    *Material::ice,
    *Material::topSnow,
    *Material::snow,
    *Material::cactus,
    *Material::clay,
    *Material::vegetable,
    *Material::portal,
    *Material::cake,
    *Material::web
;
void Material::initMaterials(){
    Material::air = new GasMaterial();
    Material::air->replaceable = true;
    Material::dirt = new Material();
    Material::wood = new Material();
    Material::wood->flammable = true;
    Material::stone = new Material();
    Material::stone->alwaysDestroyable = false;
    Material::metal = new Material();
    Material::metal->alwaysDestroyable = false;
    Material::water = new LiquidMaterial();
    Material::water->replaceable = true;
    Material::lava = new LiquidMaterial();
    Material::lava->replaceable = true;
    Material::leaves = new Material();
    Material::leaves->flammable = Material::leaves->translucent = true;
    Material::plant = new DecorationMaterial();
    Material::replaceable_plant = new DecorationMaterial();
    Material::replaceable_plant->flammable = Material::replaceable_plant->replaceable = true;
    Material::sponge = new Material();
    Material::cloth = new Material();
    Material::cloth->flammable = true;
    Material::fire = new GasMaterial();
    Material::fire->replaceable = true;
    Material::sand = new Material();
    Material::decoration = new DecorationMaterial();
    Material::glass = new Material();
    Material::glass->translucent = true;
    Material::explosive = new Material();
    Material::explosive->flammable = Material::explosive->translucent = true;
    Material::coral = new Material();
    Material::ice = new Material();
    Material::ice->translucent = true;
    Material::topSnow = new DecorationMaterial();
    Material::topSnow->alwaysDestroyable = false;
    Material::topSnow->translucent = Material::topSnow->replaceable = true;
    Material::snow = new Material();
    Material::snow->alwaysDestroyable = false;
    Material::cactus = new Material();
    Material::cactus->translucent = true;
    Material::clay = new Material();
    Material::vegetable = new Material();
    Material::portal = new Material();
    Material::cake = new Material();
    Material::web = new WebMaterial();
}

bool Material::blocksLight(){
    return true;
}

bool Material::blocksMotion(){
    return true;
}

bool Material::isAlwaysDestroyable(){
    return this->alwaysDestroyable;
}

bool Material::isFlammable(){
    return this->flammable;
}

bool Material::isLiquid(){
    return false;
}

bool Material::isReplaceable(){
    return this->replaceable;
}

bool Material::isSolid(){
    return true;
}

bool Material::isSolidBlocking(){
    return this->translucent ? false : this->blocksMotion();
}

bool Material::letsWaterThough(){
    return this->isLiquid() ? false : !this->isSolid();
}