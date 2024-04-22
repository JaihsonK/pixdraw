#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define mouseX GetMouseX()
#define mouseY GetMouseY()
#define mouseD GetMouseDelta()

struct
{
    int width;
    int height;
} header;

int windowWidth, windowHeight;

Color *screen_cache; // data to be exported (not necessarily what is outputted)

void drawpix_cache(int x, int y, Color colour)
{
    if (x < 0 || y < 0 || x >= windowWidth || y >= windowHeight)
        return;
    screen_cache[x + (y * windowWidth)] = colour;
}

void drawpix(int x, int y, Color colour)
{
    drawpix_cache(x, y, colour);
    if (colour.a == 0)
        colour = BLACK;
    DrawPixel(x, y, colour);
}

Color new_colour()
{
    uint32_t hex;
    printf("\npixdraw: Please enter hex code for your custom colour. Please format in RGBA (8 digit hex).\nIf you have a 6 digit hex code, just append \"FF\"\n");
    scanf("%x", &hex);

    uint8_t r = hex >> 24, g = (hex >> 16) & 0x00FF, b = (hex & 0x0000FF00) >> 8, a = hex & 0xFF;

    return (Color){r, g, b, a};
}

bool update()
{
    PollInputEvents();
    return (WindowShouldClose());
}

void stat(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp)
        return;
    
    fread(&header, sizeof(header), 1, fp);

    printf("\nSTATS on %s\nwidth: %d\nheight: %d\n", filename, header.width, header.height);
}

int main(int argc, char **argv)
{
    bool edit_mode = false;
    windowWidth = 500, windowHeight = 500; // default 500x500 canvas

    if (argc >= 3)
    {
        //possible usages:
        //1. pixdraw stat <filename>
        //2. pixdraw <width> <height>
        //3. pixdraw <filename>
        //4. pixdraw

        //1.
        if(strcmp(argv[1], "stat") == 0)
        {
            stat(argv[2]);
            return 0;
        }
        
        // 2. and 4.
        windowWidth = (atoi(argv[1]) > 15) ? atoi(argv[1]) : 500; // only accept user-defined canvas width if it is bigger than 50x50 pixels
        windowHeight = (atoi(argv[2]) > 15) ? atoi(argv[2]) : 500;
    }
    else if (argc == 2)
    {
        //3.
        //assume that argument is path to a file

        FILE *fp = fopen(argv[1], "r");
        if(!fp)
            printf("pixdraw: cannot open file %s", argv[1]);
        else
        {
            edit_mode = true;
            fread(&windowWidth, sizeof(int), 1, fp);
            fread(&windowHeight, sizeof(int), 1, fp);

            screen_cache = malloc(windowHeight * windowWidth * sizeof(Color));
            fread(screen_cache, sizeof(Color) * windowHeight * windowWidth, 1, fp);
            fclose(fp);
        } 
    }
    if(!edit_mode)
        screen_cache = malloc(windowHeight * windowWidth * sizeof(Color));

    InitWindow(windowWidth, windowHeight, "pixdraw | free canvas by Jaihson Kresak");
    while (!IsWindowReady())
        ;

    for (int x = 0; x < windowWidth; x++)
        for (int y = 0; y < windowHeight; y++)
        {
            if(!edit_mode)
            {
                drawpix_cache(x, y, BLANK); // user picture on top of BLANK
                DrawPixel(x, y, BLACK);     // user sees BLACK backdrop
            }
            else
                DrawPixel(x, y, screen_cache[x + (y * windowWidth)]);
        }

    Color current_colour = WHITE;
    int brush_size = 1;
    int key_pressed;
    unsigned frame_counter = 0;
    while (!update())
    {

        switch ((key_pressed = GetKeyPressed()))
        {
        case KEY_KP_0:
        case KEY_KP_1:
        case KEY_KP_2:
        case KEY_KP_3:
        case KEY_KP_4:
        case KEY_KP_5:
        case KEY_KP_6:
        case KEY_KP_7:
        case KEY_KP_8:
        case KEY_KP_9:
            brush_size = 1 + (key_pressed - KEY_KP_0);
            break;
        }

        switch (key_pressed)
        {
        case KEY_Y:
            current_colour = YELLOW;
            break;

        case KEY_O:
            current_colour = ORANGE;
            break;

        case KEY_P:
            current_colour = PINK;
            break;

        case KEY_R:
            current_colour = RED;
            break;

        case KEY_M:
            current_colour = MAROON;
            break;

        case KEY_G:
            current_colour = GREEN;
            break;

        case KEY_B:
            current_colour = BLUE;
            break;

        case KEY_V:
            current_colour = VIOLET;
            break;

        case KEY_W:
            current_colour = WHITE;
            break;

        case KEY_C:
            current_colour = BLACK;
            break;

        case KEY_N:
            current_colour = new_colour();
            break;

        case KEY_E:
            current_colour = BLANK;
            break;
        }

        if (key_pressed == KEY_H)
        {
            printf("\n142\n");
            while (!update() && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                ;
            int initialX = mouseX, initialY = mouseY, secondX, deltaX;
        second_click:
            printf("\n146\n");
            while (!update() && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                ;
            secondX = mouseX;

            deltaX = initialX - secondX;
            //BeginDrawing();
            if (deltaX < 0) // movement to right
            {
                for (int i = -deltaX; i > 0; i--)
                    for (int j = 0; j < brush_size; j++)
                        drawpix(initialX + i, initialY + j, current_colour);
            }
            else if (deltaX > 0) // movement to left
            {
                for (int i = -deltaX; i < 0; i++)
                    for (int j = 0; j < brush_size; j++)
                        drawpix(initialX + i, initialY + j, current_colour);
            }
            else
                goto second_click;
            //EndDrawing();
        }
        else if(key_pressed == KEY_U)
        {
            printf("\n174\n");
            while (!update() && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                ;
            int initialX = mouseX, initialY = mouseY, secondY, deltaY;
        second_click_v:
            printf("\n179\n");
            while (!update() && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                ;
            secondY = mouseY;

            deltaY = initialY - secondY;
            //BeginDrawing();
            if (deltaY < 0) // downward movement
            {
                for (int i = -deltaY; i > 0; i--)
                    for (int j = 0; j < brush_size; j++)
                        drawpix(initialX + i, initialY + j, current_colour);
            }
            else if (deltaY > 0) // upward movement
            {
                for (int i = -deltaY; i < 0; i++)
                    for (int j = 0; j < brush_size; j++)
                        drawpix(initialX + i, initialY + j, current_colour);
            }
            else
                goto second_click_v;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            while (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !update())
            {
                BeginDrawing();

                int tmpX = mouseX, tmpY = mouseY; // temporary mouse x and y coordinates to prevent them from changing while drawing
                // draw brush_size * brush_size blocks at a time
                for (int i = 0; i < brush_size; i++)
                    for (int j = 0; j < brush_size; j++)
                        drawpix(tmpX + i, tmpY + j, current_colour);

                EndDrawing();
            }
        else if (!(frame_counter % 20000))
        {
            BeginDrawing();
            for(int x = 0; x < windowWidth; x++)
                for(int y = 0; y < windowHeight; y++)
                {
                    drawpix(x, y, screen_cache[x + (y * windowWidth)]);
                }          
            EndDrawing();
        }  
        frame_counter++;
    }

    // export screen_cache to file
    CloseWindow();

    char buf[101];
    printf("pixmap: Enter file to export drawing to: ");
    scanf("%s", buf);

    FILE *fp = fopen(buf, "w");
    if (!fp)
        goto out;
    fseek(fp, SEEK_SET, 0);

    header.height = windowHeight;
    header.width = windowWidth;

    fwrite(&header, sizeof(header), 1, fp);
    fwrite(screen_cache, windowHeight * windowWidth * sizeof(Color), 1, fp);
    fclose(fp);
    printf("\nwriting successful\n");

out:
    free(screen_cache);
    printf("\nending\n");
    return 0;
}