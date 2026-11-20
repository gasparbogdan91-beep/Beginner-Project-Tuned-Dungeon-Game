DUNGEON v3 (3D-ish) - all layers 1280x720 unless noted. Draw order, back to front:
1 layer0_room.png        (0,0)   room: back wall, side walls, ceiling, floor
2 layer1_pillars_props.png (0,0) pillars, crates, barrel, chains, grate
3 torch_glow.png         pulse alpha 0.84-1.0 sin; centred on (196,244) and (1084,244)
4 torch_smoke_sheet.png  8 frames, 48px wide each; at (196-24, 92) and (1084-24, 92)
5 torch_flame_sheet.png  6 frames, 56x88 each; top-left (168,220) and (1056,220); ~8 fps
6 layer2_light_shaft.png (0,0)
7 fog_tile.png           1280 wide, tile + scroll left slowly; draw at y=464 and y=536
8 characters             hero feet ~y=590 on left, monster on right (mirror it)
9 layer3_foreground.png  (0,0) vignette, ribs, rocks, skull
Drip: from (672,144) falling to ~(672,600); then drip_ripple_sheet.png (56px frames) at (644,600).
