/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

/*****************************************************************************
 * name:		be_aas_entity.c
 *
 * desc:		AAS entities
 *
 * $Archive: /MissionPack/code/botlib/be_aas_entity.c $
 *
 *****************************************************************************/

#include "../qcommon/q_shared.h"
#include "aasfile.h"
#include "botlib.h"
#include "be_aas.h"
#include "be_aas_funcs.h"
#include "be_interface.h"
#include "be_aas_def.h"

#define MASK_SOLID		CONTENTS_PLAYERCLIP

//===========================================================================
//
// Parameter:			-
// Returns:				-
// Changes Globals:		-
//===========================================================================
void AAS_EntityInfo(int entnum, aas_entityinfo_t *info)
{
	if (!aasworld.initialized)
	{
		botimport.Print(PRT_FATAL, "AAS_EntityInfo: aasworld not initialized\n");
		Com_Memset(info, 0, sizeof(aas_entityinfo_t));
		return;
	} //end if

	if (entnum < 0 || entnum >= aasworld.maxentities)
	{
		botimport.Print(PRT_FATAL, "AAS_EntityInfo: entnum %d out of range\n", entnum);
		Com_Memset(info, 0, sizeof(aas_entityinfo_t));
		return;
	} //end if

	Com_Memcpy(info, &aasworld.entities[entnum].i, sizeof(aas_entityinfo_t));
} //end of the function AAS_EntityInfo
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void AAS_ResetEntityLinks(void)
{
	int i;
	for (i = 0; i < aasworld.maxentities; i++)
	{
		aasworld.entities[i].areas = NULL;
		aasworld.entities[i].leaves = NULL;
	} //end for
} //end of the function AAS_ResetEntityLinks
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void AAS_InvalidateEntities(void)
{
	int i;
	for (i = 0; i < aasworld.maxentities; i++)
	{
		aasworld.entities[i].i.valid = qfalse;
		aasworld.entities[i].i.number = i;
	} //end for
} //end of the function AAS_InvalidateEntities
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void AAS_UnlinkInvalidEntities(void)
{
	int i;
	aas_entity_t *ent;

	for (i = 0; i < aasworld.maxentities; i++)
	{
		ent = &aasworld.entities[i];
		if (!ent->i.valid)
		{
			AAS_UnlinkFromAreas( ent->areas );
			ent->areas = NULL;
			AAS_UnlinkFromBSPLeaves( ent->leaves );
			ent->leaves = NULL;
		} //end for
	} //end for
} //end of the function AAS_UnlinkInvalidEntities
