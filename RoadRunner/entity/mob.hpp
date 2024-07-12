#ifndef MOB_HPP
#define MOB_HPP
#include <entity/entity.hpp>

namespace RoadRunner {
	struct Server;
	namespace entity{
		struct Mob : Entity{
			//TODO fields
			Mob(Server* server);
		};
	}
}


#endif // MOB_HPP
