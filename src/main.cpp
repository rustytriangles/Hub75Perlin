#include "display.hpp"
#include "hub75util.hpp"
#include "perlin.hpp"
#include "pixel.hpp"
#include "util.hpp"

volatile bool flip = false;

Pixel backbuffer[FB_WIDTH][FB_HEIGHT];
Pixel frontbuffer[FB_WIDTH][FB_HEIGHT];

void hub75_flip () {
    flip = true; // TODO: rewrite to semaphore
}

void hub75_display_update() {

    // Ridiculous register write nonsense for the FM6126A-based 64x64 matrix
    FM6126A_write_register(0b1111111111111110, 12);
    FM6126A_write_register(0b0000001000000000, 13);

    while (true) {
        if (flip) {
            memcpy((uint8_t *)backbuffer, (uint8_t *)frontbuffer, FB_WIDTH * FB_HEIGHT * sizeof(Pixel));
            flip = false;
        }

        push_buffer(&backbuffer[0][0], FB_WIDTH, FB_HEIGHT);
    }
}

int main() {
    // 1.3v allows overclock to ~280000-300000 but YMMV. Faster clock = faster screen update rate!
    // vreg_set_voltage(VREG_VOLTAGE_1_30);
    // sleep_ms(100);

    // 200MHz is roughly about the lower limit for driving a 64x64 display smoothly.
    // Just don't look at it out of the corner of your eye.
    set_sys_clock_khz(200000, false);

    init_pins();

    // Launch the display update routine on Core 1, it's hungry for cycles!
    multicore_launch_core1(hub75_display_update);

    Perlin p;

    const float scale = 3.f / (float)FB_HEIGHT;

    std::srand(std::time(nullptr));

    const int max_steps = 30000;
    int frame = 0;

    const float min_ang_step = 0.f;
    const float max_ang_step = 0.2f;
    const float min_x_step = 0.f;
    const float max_x_step = 0.05f;
    const float min_h_step = 0.001f;
    const float max_h_step = 0.005f;

    float ang = 0.f;
    const float zr = 10.f;
    float x_off = 0.f;
    float h = 0.f;

    float ang_step = random_between(min_ang_step, max_ang_step);
    float x_step = random_between(min_x_step, max_x_step);
    float h_step = random_between(min_h_step, max_h_step);

    while (true) {

        if (frame > max_steps) {
            ang = 0.f;
            x_off = 0.f;
            h = 0.f;

            ang_step = random_between(min_ang_step, max_ang_step);
            x_step = random_between(min_x_step, max_x_step);
            h_step = random_between(min_h_step, max_h_step);

            frame = 0;
        }

        for (int i=0; i<FB_WIDTH; i++) {
            float x = scale * (float)i + x_off;
            for (int j=0; j<FB_HEIGHT; j++) {
                float y = scale * (float)j;
                float z = scale * (zr + zr*(float)sin(ang));
                float v = fade(octaves(p, x,y,z, 3));
//                float v = p.eval(x,y,z);
                frontbuffer[i][j] = hsv_to_rgb(h, 1.f-v, 0.25f + 0.75f*v);
            }
        }

        ang += ang_step;
        x_off += x_step;
        h = fmod(h+h_step, 1.f);

        hub75_flip();

        sleep_ms(1);
    }
}
