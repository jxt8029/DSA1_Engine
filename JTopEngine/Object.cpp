#include "Object.h"



Object::Object()
{
}

Object::Object(Transform * tr, std::string * str, Collider coll)
{
	trnsfrm = tr;
	textureFileName = str;
	collider = coll;
}


Object::~Object()
{
}
