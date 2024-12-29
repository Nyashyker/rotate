#include <stdio.h>
#include <stdlib.h>

#define BOX_SIZE 12

enum Vector {
    UP,//    = -1,
    RIGHT,// = +1,
    LEFT,//  = -1,
    DOWN,//  = +1,
};

struct Cords {
    unsigned int x;
    unsigned int y;
};

void show_matrix(struct Cords* buffer, const unsigned int max_box_size);
struct Cords* clockwise_expanding_spiral_cords(struct Cords* buffer, const unsigned int max_box_size);

int main(int argc, char **argv)
{
    struct Cords* rez_buf = calloc(BOX_SIZE * BOX_SIZE, sizeof(struct Cords));
    printf("Буфер виділився:\n");
    show_matrix(rez_buf, BOX_SIZE);
    clockwise_expanding_spiral_cords(rez_buf, BOX_SIZE);
    printf("Функція спрацювала...\n");
    printf("---\n");
    show_matrix(rez_buf, BOX_SIZE);
    printf("---\n");
    printf("Матриця успішно вивелася!\n");
    printf("Програму завершено)\n");

    return 0;
}

struct Cords* clockwise_expanding_spiral_cords(struct Cords* buffer, const unsigned int max_box_size)
{
    const unsigned int center = max_box_size / 2;

    struct Cords position = {center, center};

    // Стан руху по уявному квадрату із центру
    enum Vector state = DOWN;
    // розмір сторони квадрату (менша половина)
    unsigned int imagine_matrix_size = 1;

    // Уведення початку
    buffer[0] = position;
    position.x++;

    for (size_t i = 1; i < max_box_size * max_box_size; i++)
    {
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

        // Не даємо вийти за межі діапазону
        if (imagine_matrix_size >= center) {
            break;
        }
    }

    return buffer;
}

void show_matrix(struct Cords* buffer, const unsigned int max_box_size)
{
    // ХЗ як це по-людськи зробити
    int matrix[BOX_SIZE][BOX_SIZE] = {};

    // Так, воно спамить у нульову комірку
    // якщо не весь буфер ще містить щось змістовне
    // Але для моєї задачі це задовільно
    // Тож і фіг із ним
    for (size_t i = 0; i < max_box_size*max_box_size; i++){
        const struct Cords cords = buffer[i];
        matrix[cords.y][cords.x] = i + 1;
    }

    for (unsigned int y = 0; y < max_box_size; y++) {
        for (unsigned int x = 0; x < max_box_size; x++) {
            printf("%03d\t", matrix[y][x]);
        }
        printf("\n");
    }
}
