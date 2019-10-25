Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "./assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "./assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "helicopter-texture", file = "./assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "tank-texture-big-left", file = "./assets/images/tank-big-left.png" },
        [4] = { type="texture", id = "tank-texture-big-right", file = "./assets/images/tank-big-right.png" },
        [5] = { type="texture", id = "projectile-texture", file = "./assets/images/bullet-enemy.png" },
        [6] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 16 },
        [7] = { type="font", id = "charriot-font-small", file = "./assets/fonts/charriot.ttf", fontSize = 12 },
        [8] = { type="texture", id = "radar-texture", file = "./assets/images/radar.png" },
        [9] = { type="texture", id = "collision-texture", file = "./assets/images/collision-texture.png" }
    },
    map = {
        textureAssetId = "terrain-texture-night",
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
                    textureAssetId = "collision-texture",
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
                    color = XXXXX
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
                    textureAssetId = "tank-texture-big-right",
                    animated = false
                },
                collider = {
                    textureAssetId = "collision-texture",
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
                    color = XXXXX
                },
                projectileEmitter = {
                    speed = 125,
                    range = 375,
                    angle = 0,
                    spawnDelay = 2.0,
                    isLooping = true;
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
                    fontId = "charriot-font",
                    color = XXXXX
                }
            }
        }
    }
}
