/*
 * ex10_menu_navigation.c - Simple menu navigation FSM.
 * Key concept: UI state changes on button events.
 */
#include <stdio.h>

typedef enum { MENU_HOME, MENU_SETTINGS, MENU_INFO, MENU_COUNT } Menu_t;
typedef enum { BTN_NEXT, BTN_SELECT } Button_t;

int main(void)
{
    Menu_t menu = MENU_HOME;
    Button_t inputs[] = {BTN_NEXT, BTN_NEXT, BTN_SELECT};
    const char *names[] = {"HOME", "SETTINGS", "INFO"};

    for (size_t i = 0U; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        if (inputs[i] == BTN_NEXT) {
            menu = (Menu_t)((menu + 1) % MENU_COUNT);
        } else {
            printf("select %s\n", names[menu]);
        }
        printf("menu %s\n", names[menu]);
    }
    return 0;
}
