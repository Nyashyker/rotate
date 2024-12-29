#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define null (void *)0

typedef enum {
    UP,
    RIGHT,
    LEFT,
    DOWN,
} Vector;

typedef struct {
    unsigned int x;
    unsigned int y;
    bool valid;
} Cords;



char* move_state_to_str(const Vector move_state);
void show_matrix(const Cords *const buffer, const unsigned int max_box_size);
Cords* clockwise_expanding_spiral_cords(Cords *const buffer, const unsigned int max_box_size);


int main(int argc, char **argv)
{
    unsigned int box_size;
    if (argc == 2) {
        const unsigned long tmp = strtoul(argv[1], null, 10);
        if (tmp > UINT_MAX) { goto standard_size; }
        box_size = atoi(argv[1]);
    } else if (argc == 1) {
        printf("Уведіть розмір сітки: ");
        if (scanf("%iu", &box_size) != 1) { goto standard_size; }
    } else {
standard_size:
        box_size = 13;
    }

    Cords* rez_buf = calloc(box_size * box_size, sizeof(Cords));

    clockwise_expanding_spiral_cords(rez_buf, box_size);
    show_matrix(rez_buf, box_size);

    free(rez_buf);
    return 0;
}

char* move_state_to_str(const Vector move_state)
{
    switch (move_state)
    {
        case UP: return "UP   ";
        case RIGHT: return "RIGHT";
        case LEFT: return "LEFT ";
        case DOWN: return "DOWN ";
    }
}


Cords* clockwise_expanding_spiral_cords(Cords *const buffer, const unsigned int max_box_size)
{
    const long center = max_box_size / 2 - !(max_box_size % 2);

    Cords position = {center, center, true};
    Vector move_state = UP;
    unsigned int imagine_box_size = 0;

    for (size_t i = 0; i < max_box_size * max_box_size; i++)
    {
        buffer[i] = position;

        switch (move_state)
        {
            case DOWN: // наразі рух: УНИЗ
                if (position.y < center + imagine_box_size) {
                    position.y++;
                } else { // повертаємо: НАЛІВО
                    move_state = LEFT;
                    position.x--;
                }
            break;

            case LEFT: // наразі рух: НАЛІВО
                if (position.x > center - imagine_box_size) {
                    position.x--;
                } else { // повертаємо: УГОРУ
                    move_state = UP;
                    position.y--;
                }
            break;

            case UP: // наразі рух: УГОРУ
                if (position.y > center - imagine_box_size) {
                    position.y--;
                } else { // повертаємо: НАПРАВО
                    move_state = RIGHT;
                    position.x++;
                }
            break;

            case RIGHT: // наразі рух: НАПРАВО
                if (position.x <= center + imagine_box_size) {
                    position.x++;
                } else { // повертаємо: УНИЗ
                    imagine_box_size++;
                    move_state = DOWN;
                    position.y++;
                }
            break;
        }
    }

    return buffer;
}


void show_matrix(const Cords *const buffer, const unsigned int max_box_size)
{
    unsigned int *const matrix = calloc(max_box_size * max_box_size, sizeof(unsigned int));

    for (size_t i = 0; i < max_box_size * max_box_size; i++){
        const Cords cords = buffer[i];
        if (!cords.valid) { break; }
        matrix[cords.y * max_box_size + cords.x] = i + 1;
    }


    const unsigned short num_len = log10(max_box_size * max_box_size) + 1;
    const unsigned long border_size = max_box_size * num_len + (max_box_size - 1) * 2 + 2 * 2;


    // Border
    printf("+");
    for (unsigned long i = 0; i < border_size; i++) {
        if (i % (num_len + 2) > 1) {
            printf("-");
        } else {
            printf(" ");
        }
    }
    printf("+\n\n");
    // Matrix itself
    for (unsigned int y = 0; y < max_box_size; y++) {
        printf("|  ");
        for (unsigned int x = 0; x < max_box_size; x++) {
            printf("%0*d  ", num_len, matrix[y * max_box_size + x]);
        }
        printf("|\n\n");
    }
    // Border
    printf("+");
    for (unsigned long i = 0; i < border_size; i++) {
        if (i % (num_len + 2) > 1) {
            printf("-");
        } else {
            printf(" ");
        }
    }
    printf("+\n");

    free(matrix);
}
