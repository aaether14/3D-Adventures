#ifndef BASE_STATE_SAVER_HPP
#define BASE_STATE_SAVER_HPP



#include <string>



class AStateSaver
{



private:


	bool should_reset;
	std::string source_path;


public:


	virtual void Save() = 0;
	virtual void Load() = 0;
	virtual void Reset() = 0;


	inline void SetShouldReset(bool should_reset){ this->should_reset = should_reset; }
	inline bool ShouldReset(){ return should_reset; }

	inline void SetPath(std::string source_path){ this->source_path = source_path; }
	inline std::string GetPath(){ return source_path; }


};





#endif