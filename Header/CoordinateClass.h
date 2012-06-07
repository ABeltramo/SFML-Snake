#ifndef COORDINATECLASS_H_INCLUDED
#define COORDINATECLASS_H_INCLUDED
class Coordinate{
	public:
		int x;
		int y;
		bool operator==(Coordinate a){
			if(a.x == this->x && a.y == this->y)
				return true;
			else
				return false;
		}
		void operator=(Coordinate b){
			this->x = b.x;
			this->y = b.y;
		}
};

#endif