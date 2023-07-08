#include <stdbool.h>
#define PS2_KEYBOARD 0x60
#define KEY_RELEASED_THRESHOLD 0x80

bool key_states[128];
char key_events[59];
