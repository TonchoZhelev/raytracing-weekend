#include <stdio.h>

int main(int argc, char** argv) {
    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            double r = double(i) / (image_width - 1);
            double g = double(j) / (image_height - 1);
            double b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }

    return 0;
}
