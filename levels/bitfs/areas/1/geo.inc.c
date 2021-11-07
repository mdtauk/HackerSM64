// 0x0E0007A0
const GeoLayout bitfs_geo_0007A0[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND(BACKGROUND_FLAMING_SKY, geo_skybox_main),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 20000, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 2000, 6000, 0, -4500, -8000, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_ALPHA, bitfs_seg7_dl_07002118),
               GEO_ASM(0,                        geo_movtex_pause_control),
               GEO_ASM(MOVTEX_BITFS_LAVA_FIRST,  geo_movtex_draw_nocolor),
               GEO_ASM(MOVTEX_BITFS_LAVA_SECOND, geo_movtex_draw_nocolor),
               GEO_ASM(MOVTEX_BITFS_LAVA_FLOOR,  geo_movtex_draw_nocolor),
               GEO_RENDER_OBJ(),
               GEO_ASM(ENVFX_LAVA_BUBBLES,       geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
