// Joel Adu - Memory Matching Game Main File

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "game.h"

int mx, my;

void drawGame(Game& memoryGame, ALLEGRO_FONT* font)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    memoryGame.drawGrid();
    memoryGame.drawObjects();
    memoryGame.drawStatus(font);
    al_flip_display();
}

int main()
{
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 600;
    const int FPS = 60;

    bool done = false;
    bool redraw = true;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_FONT* font = NULL;

    if (!al_init())
        return -1;

    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display)
        return -1;

    font = al_create_builtin_font();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    Game memoryGame;

    al_start_timer(timer);

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            mx = ev.mouse.x;
            my = ev.mouse.y;

            bool clicked = memoryGame.handleMouseClick(mx, my);

            if (clicked)
            {
                drawGame(memoryGame, font);

                if (memoryGame.compare())
                {
                    drawGame(memoryGame, font);
                }
                else
                {
                    al_rest(5.0);
                    memoryGame.hideUnmatched();
                    drawGame(memoryGame, font);
                }
            }

            if (memoryGame.gameWon())
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255, 255, 255), 180, 280, 0, "You matched all pairs!");
                al_flip_display();
                al_rest(5.0);
                done = true;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            drawGame(memoryGame, font);
        }
    }

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}