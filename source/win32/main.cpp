#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// #include "tgaimage.h"


// const TGAColor white = TGAColor(255, 255, 255, 255);
// const TGAColor red = TGAColor(255, 0, 0, 255);

void draw_line(int x0, int y0, int x1, int y1);

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../vendor/stb_image/stb_image_write.h"

// TGAImage image_tga(50, 50, TGAImage::RGB);

struct Image {
	const int width;
	const int height;
	const int64_t channel_number;
	uint8_t *pixels;
};
typedef struct Image Image;

struct Color {
	int r, g, b;
};
typedef struct Color Color;

void image_set_pixel(Image *image, int x, int y, Color color) {
	if (x == 0 && y == 0) return;

	int64_t index = image->width * y + x;
	if (index < 0) return;
	index *= image->channel_number;
	image->pixels[index++] = (uint8_t)color.r;
	image->pixels[index++] = (uint8_t)color.g;
	image->pixels[index++] = (uint8_t)color.b;
}

Image image = { 50, 50, 3 };

int main(int argc, char **argv)
{


	image.pixels = (uint8_t *)calloc(image.width * image.height * image.channel_number, sizeof(image.pixels));
	// image_set_pixel(&image, 25, 25, { 255, 255, 255});
	draw_line(0, 0, 0, 40); // 50 50 does not reach edge

	/*** NOTICE!! You have to use uint8_t array to pass in stb function  ***/
	// Because the size of color is normally 255, 8bit.
	// If you don't use this one, you will get a weird imge.
	// uint8_t *pixels = new uint8_t[width * height * CHANNEL_NUM];

	// int index = 0;
	// for (int j = image.height - 1; j >= 0; --j)
	// {
	// 	for (int i = 0; i < image.width; ++i)
	// 	{
	// 		float r = (float)i / (float)image.width;
	// 		float g = (float)j / (float)image.height;
	// 		float b = 0.2f;
	// 		int ir = int(255.99 * r);
	// 		int ig = int(255.99 * g);
	// 		int ib = int(255.99 * b);

	// 		image.pixels[index++] = ir;
	// 		image.pixels[index++] = ig;
	// 		image.pixels[index++] = ib;
	// 	}
	// }

	// if CHANNEL_NUM is 4, you can use alpha channel in png
	stbi_flip_vertically_on_write(true);
	stbi_write_png("render.png", (int)image.width, (int)image.height, (int)image.channel_number, image.pixels, (int) (image.width * image.channel_number));
	free(image.pixels);

	// image_tga.set(0, 0, red);

	// image_tga.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	// image_tga.write_tga_file("output.tga");

	// printf("%d", getchar() != EOF);

	return 0;
}

void draw_line(int x0, int y0, int x1, int y1)
{
	if (x0 > x1)
	{
		int temp_x = x0;
		x0 = x1;
		x1 = temp_x;

		int temp_y = y0;
		y0 = y1;
		y1 = temp_y;
	}

	float a = (y1 - y0) / (float)(x1 - x0);
	float y = (float)y0;
	for (float x = (float)x0; x < (float)x1; x+= 0.1f)
	{
		image_set_pixel(&image, (int)x, (int)y, { 255, 255, 255});
		// image.set(x, y, red);
		y = y + a;
	}
}
