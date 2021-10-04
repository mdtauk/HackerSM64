#ifndef SURFACE_LOAD_H
#define SURFACE_LOAD_H

#include <PR/ultratypes.h>

#include "surface_collision.h"
#include "types.h"

// For the static assert macro
#include "macros.h"

#if EXTENDED_BOUNDS_MODE == 0 // 1x, normal cell size
    #define LEVEL_BOUNDARY_MAX 0x2000L //  8192
    #define CELL_SIZE          0x400   //  1024, NUM_CELLS = 16
#elif EXTENDED_BOUNDS_MODE == 1 // 2x, normal cell size
    #define LEVEL_BOUNDARY_MAX 0x4000L // 16384
    #define CELL_SIZE          0x400   //  1024, NUM_CELLS = 32
#elif EXTENDED_BOUNDS_MODE == 2 // 1x, smaller cell size
    #define LEVEL_BOUNDARY_MAX 0x2000L //  8192
    #define CELL_SIZE          0x200   //   512, NUM_CELLS = 32
#elif EXTENDED_BOUNDS_MODE == 3 // 4x, normal cell size
    #define LEVEL_BOUNDARY_MAX 0x8000L // 32768
    #define CELL_SIZE          0x400   //  1024, NUM_CELLS = 64
#endif

STATIC_ASSERT(((EXTENDED_BOUNDS_MODE >= 0) && (EXTENDED_BOUNDS_MODE <= 3)), "You must set a valid extended bounds mode!");

// The amount of cells in each axis in an area.
#define NUM_CELLS                   (2 * LEVEL_BOUNDARY_MAX / CELL_SIZE)
// The maximum amount of collision surfaces (static and dynamic combined)
#define SURFACE_POOL_SIZE           (LEVEL_BOUNDARY_MAX / 2) // Vanilla: 2300. Modes: 0: 4096, 1: 8192, 2: 8192, 3: 16384
// How many SurfaceNodes can fit in Surface. This is done so that the maximum sizes for both can contain the same amount.
#define SURFACE_NODE_STRUCT_DIFF    3.5 // = (56 / 16) = (sizeof(struct Surface) / sizeof(struct SurfaceNode))
// The maximum amount of SurfaceNodes (static and dynamic combined)
#define SURFACE_NODE_POOL_SIZE      (s32)(SURFACE_POOL_SIZE * SURFACE_NODE_STRUCT_DIFF) // Vanilla: 7000. Modes: 0: 14336, 1: 28672, 2: 28672, 3: 57344

// Flags for error messages
#define NOT_ENOUGH_ROOM_FOR_SURFACES (1 << 0)
#define NOT_ENOUGH_ROOM_FOR_NODES    (1 << 1)

// Use this to convert game units to cell coordinates
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
extern s16 sSurfaceNodePoolSize;
extern s16 sSurfacePoolSize;

void alloc_surface_pools(void);
#ifdef NO_SEGMENTED_MEMORY
u32 get_area_terrain_size(TerrainData *data);
#endif
void load_area_terrain(s32 index, TerrainData *data, RoomData *surfaceRooms, s16 *macroObjects);
void clear_dynamic_surfaces(void);
void load_object_collision_model(void);

#endif // SURFACE_LOAD_H
