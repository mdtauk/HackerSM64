#ifndef SURFACE_LOAD_H
#define SURFACE_LOAD_H

#include <PR/ultratypes.h>

#include "surface_collision.h"
#include "types.h"


// -- Set LEVEL_BOUNDARY_MAX in config.h --


// The level is split into a NUM_CELLS by NUM_CELLS grid of collision cells.
// This is the number of cells along each axis in an area.
#define NUM_CELLS   32
// The distance across a single collision cell.
#define CELL_SIZE   (2 * LEVEL_BOUNDARY_MAX / NUM_CELLS)


//! TODO: Make these two allocate dynamically:
// The maximum amount of collision surfaces (static and dynamic combined)
#define SURFACE_POOL_SIZE           (LEVEL_BOUNDARY_MAX / 2) // Vanilla: 2300
// The maximum amount of SurfaceNodes (static and dynamic combined).
// Each cell has a SurfaceNode for every surface which intersects it,
// so each cell a surface intersects with gets its own SurfaceNode.
// Multiply SURFACE_POOL_SIZE by the average amount of cells the surfaces intersect.
// Larger surfaces means more SurfaceNodes.
#define SURFACE_NODE_POOL_SIZE      (SURFACE_POOL_SIZE * 4) // Vanilla: 7000


// Flags for error messages
#define NOT_ENOUGH_ROOM_FOR_SURFACES (1 << 0)
#define NOT_ENOUGH_ROOM_FOR_NODES    (1 << 1)


// Use this to convert game units to cell coordinates:
#define GET_CELL_COORD(p)   ((((p) + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & (NUM_CELLS - 1));


extern u8 gSurfacePoolError;

struct SurfaceNode
{
    struct SurfaceNode *next;
    struct Surface *surface;
};

enum SpatialPartitions
{
    SPATIAL_PARTITION_FLOORS,
    SPATIAL_PARTITION_CEILS,
    SPATIAL_PARTITION_WALLS,
    SPATIAL_PARTITION_WATER,
    MUM_SPATIAL_PARTITIONS
};

typedef struct SurfaceNode SpatialPartitionCell[MUM_SPATIAL_PARTITIONS];

extern SpatialPartitionCell  gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
extern SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];
extern struct SurfaceNode *sSurfaceNodePool;
extern struct Surface     *sSurfacePool;
extern s32 sSurfaceNodePoolSize;
extern s32 sSurfacePoolSize;

void alloc_surface_pools(void);
#ifdef NO_SEGMENTED_MEMORY
u32 get_area_terrain_size(TerrainData *data);
#endif
void load_area_terrain(s32 index, TerrainData *data, RoomData *surfaceRooms, s16 *macroObjects);
void clear_dynamic_surfaces(void);
void load_object_collision_model(void);

#endif // SURFACE_LOAD_H
