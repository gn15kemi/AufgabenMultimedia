#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h" 
 #define BINS 3
 #define BIN_SIZE (255 / BINS)

/*---------------------------------------*/
void manipulate(bitmap_pixel_rgb_t* pixels, int count);

/*--------------------------------------*/

void bin_comp(bitmap_component_t *c);

/*--------------------------------------*/


int main(void)
{ // Read the bitmap pixels.
	bitmap_error_t error;
	int width, height;
	bitmap_pixel_rgb_t* pixels;

	error = bitmapReadPixels(
		"sails.bmp",
		(bitmap_pixel_t**)&pixels,
		&width,
		&height,
		BITMAP_COLOR_SPACE_RGB
		);
	
		assert(error == BITMAP_ERROR_SUCCESS);
		printf("Bitmap dimensions: %d x %d\n", width, height);

		// Manipulate the pixels.
		manipulate(pixels, width * height);

		// write the pixel back  // une structure
		bitmap_parameters_t params =
		{	///Is this bitmap bottom-up?
	    	
			.bottomUp = BITMAP_BOOL_TRUE,

			//Width in pixels:
			 .widthPx = width,

			//Height in pixels:
			 .heightPx = height,

			//Which color depth is used?
			.colorDepth = BITMAP_COLOR_DEPTH_24,

			//Which compression is used?
			.compression = BITMAP_COMPRESSION_NONE,

			//Which kind of DIB header is used?
			.dibHeaderFormat = BITMAP_DIB_HEADER_INFO,

			//The color space the user provides:
			.colorSpace = BITMAP_COLOR_SPACE_RGB
		};
		
		error = bitmapWritePixels(
			"sails_mod.bmp", //const char* filePath,// ici sa modifie completement le fichier// creer un nouveau fichier modifie appele sails_modifi
		BITMAP_BOOL_TRUE ,
		 &params, 
		 (bitmap_pixel_t*)pixels//const bitmap_pixel_t* pixels
		 );

			assert(error == BITMAP_ERROR_SUCCESS); //La fonction assert() est généralement utilisée pour aider à vérifier qu'un programme fonctionne correctement
		// free the memory that has been allocated by the bitmap library.
		free(pixels);
	return 0;
}
/*------------------------------------*/
void manipulate(bitmap_pixel_rgb_t* pixels, int count)
{
	for(int i=0; i < count; i++)
	{
		bitmap_pixel_rgb_t* pix = &pixels[i];

				 // pix -> b = 0; oder (*pix).b = 0; another manner to Write it.// blue color disappear
	bin_comp(&pix->r);
	bin_comp(&pix->g);
	bin_comp(&pix->b);


	}
}
/*----------------------------------*/
void bin_comp(bitmap_component_t *c)
{ 
  *c = (bitmap_component_t)(BIN_SIZE * ((int)*c / BIN_SIZE));
}
/*----------------------------------*/