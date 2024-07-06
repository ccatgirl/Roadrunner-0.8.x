#pragma once

namespace RoadRunner {
	namespace block{
		namespace material{
			struct Material{
				static Material
					*air,
					*dirt,
					*wood,
					*stone,
					*metal,
					*water,
					*lava,
					*leaves,
					*plant,
					*replaceable_plant,
					*sponge,
					*cloth,
					*fire,
					*sand,
					*decoration,
					*glass,
					*explosive,
					*coral,
					*ice,
					*topSnow,
					*snow,
					*cactus,
					*clay,
					*vegetable,
					*portal,
					*cake,
					*web
				;
				static void initMaterials();
				//TODO maybe teardownMaterials too?

				bool alwaysDestroyable = 1;
				bool flammable = 0;
				bool translucent = 0;
				bool replaceable = 0;

				Material(){}

				bool blocksLight();
				bool blocksMotion();
				bool isAlwaysDestroyable();
				bool isFlammable();
				bool isLiquid();
				bool isReplaceable();
				bool isSolid();
				bool isSolidBlocking();
				bool letsWaterThough();
			};
			struct GasMaterial : public Material{
				bool blocksLight(){
					return false;
				}

				bool blocksMotion(){
					return false;
				}

				bool isSolid(){
					return false;
				}
			};

			struct LiquidMaterial : public Material{
				bool blocksMotion(){
					return false;
				}

				bool isSolid(){
					return false;
				}

				bool isLiquid(){
					return true;
				}
			};

			struct DecorationMaterial : public Material{
				DecorationMaterial() : Material(){
					this->flammable = this->translucent = this->alwaysDestroyable = this->replaceable = false; //TODO not sure does *(_DWORD *)&v8->isFlammable = 0; mean that all those 4 will be false + not sure should it be in constructor or not
				}
				bool blocksLight(){
					return false;
				}

				bool blocksMotion(){
					return false;
				}

				bool isSolid(){
					return false;
				}
			};

			struct WebMaterial : public Material{
				WebMaterial() : Material(){
					this->alwaysDestroyable = false;
				}
				bool blocksMotion(){
					return false;
				}
			};
		}
	}
}
