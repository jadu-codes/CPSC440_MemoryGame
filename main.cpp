#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

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

    if (!al_init())
        return -1;

    al_init_primitives_addon();

    display = al_create_display(
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    if (!display)
        return -1;

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(
        event_queue,
        al_get_display_event_source(display)
    );

    al_register_event_source(
        event_queue,
        al_get_timer_event_source(timer)
    );

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

        if (redraw &&
            al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(
                al_map_rgb(0, 0, 0)
            );

            memoryGame.drawGrid();

            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}