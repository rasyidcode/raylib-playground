#include <raylib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(void) {
    int virtualWidth = 480;
    int virtualHeight = 720;

    InitWindow(960, 1440, "Viewport Scaling");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

    // Set texture filtering if you want smooth or sharp pixel art
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    while(!WindowShouldClose()) {
        // 1. Compute scaling factor to fit window (with letterboxing/stretcing)
        float scale = MIN((float) GetScreenWidth() / virtualWidth, (float) GetScreenHeight() / virtualHeight);

        // 2. Draw everything to the render texture
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);

            DrawText("This is drawn at virtual resolution", 10, 10, 20, DARKGRAY);
        EndTextureMode();

        // 3. Draw render texture scaled to the real window
        BeginDrawing();
            ClearBackground(BLACK);

            // Destination rectangle centered or scaled on screen
            Rectangle destRect = {
                (GetScreenWidth() - (virtualWidth * scale)) * 0.5f,
                (GetScreenHeight() - (virtualHeight * scale)) * 0.5f,
                virtualWidth * scale,
                virtualHeight * scale
            };

            Rectangle sourceRect = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height};
            Vector2 origin = { 0.0f, 0.0f };

            DrawTexturePro(target.texture, sourceRect, destRect, origin, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}