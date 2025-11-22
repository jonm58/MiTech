// Copyright (C) 1999-2005 ID Software, Inc.
// Copyright (C) 2023-2025 Noire.dev
// SourceTech — GPLv2; see LICENSE for details.

#include "../qcommon/q_shared.h"
#include "botlib.h"
#include "be_interface.h"
#include "be_ai_goal.h"
#include "be_ai_move.h"

int BotTouchingGoal(const vec3_t origin, const bot_goal_t* goal) {
	int i;
	vec3_t boxmins, boxmaxs;
	vec3_t absmins, absmaxs;

	AAS_PresenceTypeBoundingBox(PRESENCE_NORMAL, boxmins, boxmaxs);
	VectorSubtract(goal->mins, boxmaxs, absmins);
	VectorSubtract(goal->maxs, boxmins, absmaxs);
	VectorAdd(absmins, goal->origin, absmins);
	VectorAdd(absmaxs, goal->origin, absmaxs);

	for(i = 0; i < 3; i++) {
		if(origin[i] < absmins[i] || origin[i] > absmaxs[i]) return qfalse;
	}
	return qtrue;
}
