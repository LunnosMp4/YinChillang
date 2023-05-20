#include "Game.hpp"

Texture2D skyboxFront = LoadTexture("front.png");
Texture2D skyboxBack = LoadTexture("back.png");
Texture2D skyboxLeft = LoadTexture("left.png");
Texture2D skyboxRight = LoadTexture("right.png");
Texture2D skyboxUp = LoadTexture("up.png");
Texture2D skyboxDown = LoadTexture("down.png");

Mesh skyboxMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
Model skyboxModel = LoadModelFromMesh(skyboxMesh);


skyboxModel.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxFront;
skyboxModel.materials[1].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxBack;
skyboxModel.materials[2].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxRight;
skyboxModel.materials[3].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxLeft;
skyboxModel.materials[4].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxUp;
skyboxModel.materials[5].maps[MATERIAL_MAP_CUBEMAP].texture = skyboxDown;

skyboxModel.materials[0].shader = GetShaderDefault();

BeginDrawing();
ClearBackground(RAYWHITE);

BeginMode3D(camera);

DrawModel(skyboxModel, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

// Draw other 3D objects in the scene

EndMode3D();

DrawFPS(10, 10);

EndDrawing();
