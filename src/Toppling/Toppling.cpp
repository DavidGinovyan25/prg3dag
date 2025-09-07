#include "Expansion.h"
#include <iostream>
#include <cstring> // memcpy

// Очистка двумерного массива (удаление памяти)
void Expansion::CleanArray(uint64_t **&grid) {
    if (!grid) return;
    for (int i = 0; i < bmp_grid.image_geo.len_y; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    grid = nullptr;
}

// Проверка, является ли индекс краем по размеру side
bool Expansion::IsEdge(int index, int32_t side) {
    return index == 0 || index == side - 1;
}

bool Expansion::SwitchStateForX(int y, int x) {
    for (int i = 0; i < x; ++i) {
        if (bmp_grid.pixel_grid[y][i] >= 4) {
            return true;
        }
    }
    return false;
}

bool Expansion::SwitchStateForY(int y, int x) {
    for (int i = 0; i < y; ++i) {
        if (bmp_grid.pixel_grid[i][x] >= 4) {
            return true;
        }
    }
    return false;
}

void Expansion::CopyArray(uint64_t**& grid, int shift_y, int shift_x) {
    for (int y = 0; y < bmp_grid.image_geo.len_y; ++y) {
        for (int x = 0; x < bmp_grid.image_geo.len_x; ++x) {
            grid[y + shift_y][x + shift_x] = bmp_grid.pixel_grid[y][x];
        }
    }    
}

// Главная функция выполнения итераций с поддержкой расширения сетки
void Expansion::Iterations() {
    const uint64_t MAX_ITER = 1000000; // или передавай параметр
    const uint64_t SAVE_FREQ = 1;    // частота сохранения картинок

    // 1. Инициализация — считаем размеры и сдвиги по начальному файлу
    bmp_grid.image_geo.ExtractExtremePoints();
    bmp_grid.image_geo.CalculateImageSize();

    bmp_grid.PrepearBmpGrid(bmp_grid.pixel_grid);
    bmp_grid.PlaceSendPixel();

    uint64_t iter = 0;
    bool stable = false;

    while (iter < MAX_ITER && !stable) {
        stable = true;

        // Проверяем, нужно ли расширять сетку
        bool expand_left = SwitchStateForY(bmp_grid.image_geo.len_y, 0);
        bool expand_right = SwitchStateForY(bmp_grid.image_geo.len_y, bmp_grid.image_geo.len_x - 1);
        bool expand_top = SwitchStateForX(0, bmp_grid.image_geo.len_x);
        bool expand_bottom = SwitchStateForX(bmp_grid.image_geo.len_y - 1, bmp_grid.image_geo.len_x);

        // Если расширяем — считаем новые размеры и создаем новую сетку
        int new_len_x = bmp_grid.image_geo.len_x + (expand_left ? 1 : 0) + (expand_right ? 1 : 0);
        int new_len_y = bmp_grid.image_geo.len_y + (expand_top ? 1 : 0) + (expand_bottom ? 1 : 0);

        int shift_x = (expand_left ? 1 : 0);
        int shift_y = (expand_top ? 1 : 0);

        // Если расширение есть
        if (expand_left || expand_right || expand_top || expand_bottom) {
            uint64_t **new_grid = new uint64_t*[new_len_y];
            for (int i = 0; i < new_len_y; ++i) {
                new_grid[i] = new uint64_t[new_len_x]{};
            }

            // Копируем старую сетку в новую с сдвигом (если расширяем сверху/слева)
            CopyArray(new_grid, shift_y, shift_x);

            // Очищаем старую сетку
            CleanArray(bmp_grid.pixel_grid);

            // Обновляем геометрию
            bmp_grid.image_geo.len_x = new_len_x;
            bmp_grid.image_geo.len_y = new_len_y;
            bmp_grid.image_geo.shift_x += shift_x;
            bmp_grid.image_geo.shift_y += shift_y;

            bmp_grid.pixel_grid = new_grid;
        }

        // Создаем копию текущего состояния для вычисления следующего
        uint64_t **new_state = nullptr;
        bmp_grid.PrepearBmpGrid(new_state);

        // Копируем текущие значения в new_state
        CopyArray(new_state);

        // Итерация обвала песчинок
        for (int y = 0; y < bmp_grid.image_geo.len_y; ++y) {
            for (int x = 0; x < bmp_grid.image_geo.len_x; ++x) {
                if (bmp_grid.pixel_grid[y][x] >= 4) {
                    stable = false;
                    new_state[y][x] -= 4;
                    if (y > 0)
                        ++new_state[y - 1][x];
                    if (y < bmp_grid.image_geo.len_y - 1)
                        ++new_state[y + 1][x];
                    if (x > 0)
                        ++new_state[y][x - 1];
                    if (x < bmp_grid.image_geo.len_x - 1)
                        ++new_state[y][x + 1];
                }
            }
        }

        // Обновляем основную сетку
        CleanArray(bmp_grid.pixel_grid);
        bmp_grid.pixel_grid = new_state;
        ++iter;
        // Сохраняем картинку, если нужно
        if (SAVE_FREQ > 0 && iter % SAVE_FREQ == 0) {
            // Для теста сохраняем в файл "frame_iter.bmp"
            std::string filename = "frame_" + std::to_string(iter) + ".bmp";
            std::cout << "Saving iteration " << iter << " to BMP\n";
            bmp_grid.ExportToBmp(bmp_grid.pixel_grid); // если нужен filename — переделать ExportToBmp
        }
    }
    std::cout << "Finished after " << iter << " iterations\n";
}
