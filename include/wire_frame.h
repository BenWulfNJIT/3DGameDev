#ifndef __WIRE_FRAME_H__
#define __WIRE_FRAME_H__

#include "entity.h"


Entity *wire_frame_line_new();

void wire_frame_line_move(Entity* wireFrame, Vector3D startPos, Vector3D rotation, float length);

#endif
