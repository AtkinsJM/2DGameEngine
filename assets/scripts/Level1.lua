-- Get the current time of day from the OS
local currentSystemHour = os.date("*t").hour
local mapTextureAssetId = "terrain-texture-day"

-- Set terrain texture to either day or night depending on local time
if currentSystemHour >= 6 and currentSystemHour < 18 then
    mapTextureAssetId = "terrain-texture-day"
else
    mapTextureAssetId = "terrain-texture-night"
end

local WHITE_COLOR = {
    r = 255, 
    g = 255, 
    b = 255, 
    a = 255
}

local RED_COLOR = {
    r = 255, 
    g = 0, 
    b = 0, 
    a = 255
}

local GREEN_COLOR = {
    r = 0,
    g = 255,
    b = 0,
    a = 255
}

local BLUE_COLOR = {
    r = 0,
    g = 0,
    b = 255,
    a = 255
}

Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "./assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "./assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "helicopter-texture", file = "./assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "projectile-texture", file = "./assets/images/bullet-enemy.png" },
        [4] = { type="texture", id = "obstacles-texture", file = "./assets/images/obstacles.png" },
        [5] = { type="texture", id = "truck-left-texture", file = "./assets/images/truck-left.png" },
        [6] = { type="texture", id = "truck-right-texture", file = "./assets/images/truck-right.png" },
        [7] = { type="texture", id = "truck-down-texture", file = "./assets/images/truck-down.png" },
        [8] = { type="texture", id = "tank-big-down-texture", file = "./assets/images/tank-big-down.png" },
        [9] = { type="texture", id = "tank-big-left-texture", file = "./assets/images/tank-big-left.png" },
        [10] = { type="texture", id = "tank-big-right-texture", file = "./assets/images/tank-big-right.png" },
        [11] = { type="texture", id = "tank-small-left-texture", file = "./assets/images/tank-small-left.png" },
        [12] = { type="texture", id = "tank-small-right-texture", file = "./assets/images/tank-small-right.png" },
        [13] = { type="texture", id = "army-group-1-texture", file = "./assets/images/army-group-1.png" },
        [14] = { type="texture", id = "army-group-2-texture", file = "./assets/images/army-group-2.png" },
        [15] = { type="texture", id = "army-group-3-texture", file = "./assets/images/army-group-3.png" },
        [16] = { type="texture", id = "rock-big-1-texture", file = "./assets/images/rock-big-1.png" },
        [17] = { type="texture", id = "rock-big-2-texture", file = "./assets/images/rock-big-2.png" },
        [18] = { type="texture", id = "rock-big-3-texture", file = "./assets/images/rock-big-3.png" },
        [19] = { type="texture", id = "rock-big-4-texture", file = "./assets/images/rock-big-4.png" },
        [20] = { type="texture", id = "rock-small-1-texture", file = "./assets/images/rock-small-1.png" },
        [21] = { type="texture", id = "tree-small-1-texture", file = "./assets/images/tree-small-1.png" },
        [22] = { type="texture", id = "tree-small-2-texture", file = "./assets/images/tree-small-2.png" },
        [23] = { type="texture", id = "tree-small-3-texture", file = "./assets/images/tree-small-3.png" },
        [24] = { type="texture", id = "tree-small-4-texture", file = "./assets/images/tree-small-4.png" },
        [25] = { type="texture", id = "tree-small-5-texture", file = "./assets/images/tree-small-5.png" },
        [26] = { type="texture", id = "tree-small-6-texture", file = "./assets/images/tree-small-6.png" },
        [27] = { type="texture", id = "tree-small-7-texture", file = "./assets/images/tree-small-7.png" },
        [28] = { type="texture", id = "tree-small-8-texture", file = "./assets/images/tree-small-8.png" },
        [29] = { type="texture", id = "start-texture", file = "./assets/images/start.png" },
        [30] = { type="texture", id = "heliport-texture", file = "./assets/images/heliport.png" },
        [31] = { type="texture", id = "bullet-friendly-texture", file = "./assets/images/bullet-friendly.png" },
        [32] = { type="texture", id = "radar-texture", file = "./assets/images/radar.png" },
        [33] = { type="sound", id = "blades-sound", file = "./assets/sounds/blades.wav" },
        [34] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 15 },
        [35] = { type="font", id = "charriot-font-small", file = "./assets/fonts/charriot.ttf", fontSize = 12 },
        [36] = { type="font", id = "charriot-font-large", file = "./assets/fonts/charriot.ttf", fontSize = 18 },
        [37] = { type="texture", id = "collision-texture", file = "./assets/images/collision-texture.png" }
    },
    map = {
        textureAssetId = mapTextureAssetId,
        file = "./assets/tilemaps/jungle.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "player",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 200,
                        y = 200
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "helicopter-texture",
                    animated = true,
                    frameCount = 2,
                    animationSpeed = 90,
                    directional = true,
                    fixed = false
                },
                collider = {
                    tag = "PLAYER",
                    collisionType = 0
                },
                input = {
                    keyboard = {
                        up = "up",
                        left = "left",
                        down = "down",
                        right = "right",
                        shoot = "space"
                    }
                },
                label = {
                    position = {
                        x = 0,
                        y = 40
                    },
                    text = "Player",
                    fontId = "charriot-font-small",
                    color = GREEN_COLOR
                }
            }
        },
        [1] = {
            name = "tank-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 0,
                        y = 100
                    },
                    velocity = {
                        x = 50,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tank-big-right-texture",
                    animated = false
                },
                collider = {
                    tag = "ENEMY",
                    collisionType = 1
                },
                label = {
                    position = {
                        x = 0,
                        y = 40
                    },
                    text = "Enemy",
                    fontId = "charriot-font-small",
                    color = RED_COLOR
                },
                projectileEmitter = {
                    speed = 125,
                    range = 375,
                    angle = 0,
                    spawnDelay = 2.0,
                    isLooping = true,
                    projectile = {
                        name = "projectile",
                        layer = 4,
                        textureAssetId = "projectile-texture",
                        size = 4,
                        scale = 1,
                        colliderTag = "Projectile",
                        colliderType = 3
                    }
                    
                }
            }
        },
        [2] = {
            name = "radar",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = 720,
                        y = 15
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "radar-texture",
                    animated = true,
                    frameCount = 8,
                    animationSpeed = 150,
                    directional = false,
                    fixed = true
                }
            }
        },
        [3] = {
            name = "labelLevelName",
            layer = 5,
            components = {
                label = {
                    position = {
                        x = 10,
                        y = 10
                    },
                    text = "Level 1",
                    fontId = "charriot-font-large",
                    color = WHITE_COLOR
                }
            }
        },
        [4] = {
            name = "labelPlayerPosition",
            layer = 5,
            components = {
                label = {
                    position = {
                        x = 10,
                        y = 40
                    },
                    text = "Position: (x, y)",
                    fontId = "charriot-font",
                    color = WHITE_COLOR
                }
            }
        }
    }
}
