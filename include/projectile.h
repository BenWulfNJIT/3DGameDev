#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__




#include "entity.h"

Entity *projectile_new(Vector3D position, Vector3D velocity, int airttl, int gravity);




#endif
