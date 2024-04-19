#pragma once

#include <cstdint>
#include <vector>

namespace RoadRunner {
    class Server;
    namespace entity{
		class Entity {
	
			private:
				static int entityCounter;
		
			public:
				RoadRunner::Server *server;
		
				float x = 0;
				float y = 0;
				float z = 0;
				float yaw = 0;
				float pitch = 0;
				float headYaw = 0;
				int32_t entity_id = 0;
		
				float fallDistance = 0;
		
				int health = 0;
				int fire = 0;
		
				Entity(Server *server);
		
				~Entity() {
					
				}
		
				void setPos(float x, float y, float z){
					//TODO bb
					this->x = x;
					this->y = y;
					this->z = z;
				}
	
		};
    }
}
