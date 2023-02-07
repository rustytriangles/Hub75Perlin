#include "display.hpp"
#include "hub75util.hpp"
#include "perlin.hpp"
#include "pixel.hpp"

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

    const double scale = 3. / (double)FB_HEIGHT;

    double ang = 0.;
    const double ang_step = 0.25;

    while (true) {

        for (int i=0; i<FB_WIDTH; i++) {
            double x = scale * (double)i;
            for (int j=0; j<FB_HEIGHT; j++) {
                double y = scale * (double)j;
                double z = scale * (1. + sin(ang));
                double v = octaves(p, x,y,z, 4);
                frontbuffer[i][j] = hsv_to_rgb(v, 0.75, 0.5);
            }
        }

        ang += ang_step;
        hub75_flip();

        sleep_ms(1);
    }
}
