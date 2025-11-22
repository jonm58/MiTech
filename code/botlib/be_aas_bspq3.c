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
 * name:		be_aas_bspq3.c
 *
 * desc:		BSP, Environment Sampling
 *
 * $Archive: /MissionPack/code/botlib/be_aas_bspq3.c $
 *
 *****************************************************************************/

#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"
#include "aasfile.h"
#include "botlib.h"
#include "be_aas.h"
#include "be_aas_funcs.h"
#include "be_aas_def.h"

extern botlib_import_t botimport;

//#define TRACE_DEBUG

#define ON_EPSILON		0.005

#define MAX_BSPENTITIES		4096
//bsp entity epair
typedef struct bsp_epair_s
{
	char *key;
	char *value;
	struct bsp_epair_s *next;
} bsp_epair_t;

//bsp data entity
typedef struct bsp_entity_s
{
	bsp_epair_t *epairs;
} bsp_entity_t;

//id Software BSP data
typedef struct bsp_s
{
	//true when bsp file is loaded
	int loaded;
	//entity data
	int entdatasize;
	char *dentdata;
	//bsp entities
	int numentities;
	bsp_entity_t entities[MAX_BSPENTITIES];
} bsp_t;
