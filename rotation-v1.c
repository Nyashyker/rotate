#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOX_SIZE 12


typedef enum {
    UP,//    = -1,
    RIGHT,// = +1,
    LEFT,//  = -1,
    DOWN,//  = +1,
} Vector;

typedef struct {
    unsigned int x;
    unsigned int y;
    bool valid;
} Cords;



void show_matrix(const Cords *const buffer, const unsigned int max_box_size);
Cords* clockwise_expanding_spiral_cords(Cords *const buffer, const unsigned int max_box_size);


int main(int argc, char **argv)
{
    Cords* rez_buf = calloc(BOX_SIZE * BOX_SIZE, sizeof(Cords));
    printf("Буфер виділився:\n");
    show_matrix(rez_buf, BOX_SIZE);

    clockwise_expanding_spiral_cords(rez_buf, BOX_SIZE);
    printf("Функція спрацювала...\n");

    for (int i = 0; i < BOX_SIZE * 8 - 5; i++) { printf("-"); } printf("\n");
    show_matrix(rez_buf, BOX_SIZE);
    for (int i = 0; i < BOX_SIZE * 8 - 5; i++) { printf("-"); } printf("\n");
    printf("Матриця успішно вивелася!\n");
    printf("Програму завершено)\n");

    return 0;
}


Cords* clockwise_expanding_spiral_cords(Cords *const buffer, const unsigned int max_box_size)
{
    const unsigned int center = max_box_size / 2;

    Cords position = {center, center, true};

    // Стан руху по уявному квадрату із центру
    Vector state = DOWN;
    // розмір сторони квадрату (менша половина)
    unsigned int imagine_matrix_size = 1;

    // Уведення початку
    buffer[0] = position;
    position.x++;

    for (size_t i = 1; i < max_box_size * max_box_size; i++)
    {
        // Не даємо вийти за межі діапазону
        if (imagine_matrix_size >= center) {
            break;
        }

        buffer[i] = position;

        switch (state)
        {
        case DOWN: // наразі рух: УНИЗ
            if (position.y < center + imagine_matrix_size) {
                position.y++;
            } else { // повертаємо: НАЛІВО
                state = LEFT;
                position.x--;
            }
        break;

        case LEFT: // наразі рух: НАЛІВО
            if (position.x > center - imagine_matrix_size) {
                position.x--;
            } else { // повертаємо: УГОРУ
                state = UP;
                position.y--;
            }
        break;

        case UP: // наразі рух: УГОРУ
            if (position.y > center - imagine_matrix_size) {
                position.y--;
            } else { // повертаємо: НАПРАВО
                state = RIGHT;
                position.x++;
            }
        break;

        case RIGHT: // наразі рух: НАПРАВО
            if (position.x <= center + imagine_matrix_size) {
                position.x++;
            } else { // повертаємо: УНИЗ
                imagine_matrix_size++;
                state = DOWN;
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

    for (unsigned int y = 0; y < max_box_size; y++) {
        for (unsigned int x = 0; x < max_box_size; x++) {
            printf("%03d\t", matrix[y * max_box_size + x]);
        }
        printf("\n");
    }
}
