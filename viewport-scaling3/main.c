#include <raylib.h>

#define RESOLUTION_COUNT 4

typedef enum {
    KEEP_ASPECT_INTEGER,
    KEEP_HEIGHT_INTEGER,
    KEEP_WIDTH_INTEGER,
    KEEP_ASPECT,
    KEEP_HEIGHT,
    KEEP_WIDTH,
    VIEWPORT_TYPE_COUNT,
} ViewportType;

static void ResizeRenderSize(ViewportType viewportType, int *screenWidth, int *screenHeight, int gameWidth, int gameHeight, Rectangle *sourceRect, Rectangle *destRect, RenderTexture2D *target);

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - viewport scaling");

    // Preset resolutions that could be created by subdividing screen resolution
    Vector2 resolutionList[RESOLUTION_COUNT] = {
        (Vector2){ 64, 64},
        (Vector2){ 256, 240},
        (Vector2){ 320, 180},
        (Vector2){ 3840, 2160},
    };

    RenderTexture2D target = (RenderTexture2D){0};
    Rectangle sourceRect = (Rectangle){0};
    Rectangle destRect = (Rectangle){0};

    ViewportType viewportType = KEEP_ASPECT_INTEGER;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // --- UPDATE

        // --- DRAW
        BeginTextureMode(target);

        EndTextureMode();

        BeginDrawing();        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

static void ResizeRenderSize(ViewportType viewportType, int *screenWidth, int *screenHeight, int gameWidth, int gameHeight, Rectangle *sourceRect, Rectangle *destRect, RenderTexture2D *target) {
    *screenWidth = GetScreenWidth();
    *screenHeight = GetScreenHeight();

    switch(viewportType) {

    }

    UnloadRenderTexture(*target);
    *target = LoadRenderTexture((int)sourceRect->width, -(int)sourceRect->height);
}