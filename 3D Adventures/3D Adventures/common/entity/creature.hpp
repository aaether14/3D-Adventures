#ifndef CREATURE_HPP
#define CREATURE_HPP


#include "player.hpp"



class CreatureManager
{


	Player *pl;

public:


	inline CreatureManager(){ this->pl = new Player(); }
	inline ~CreatureManager(){ this->Clean(); }
	inline void Clean(){ if (pl)delete pl; }
	inline Player*GetPlayer(){ return this->pl; }

};



#endif
