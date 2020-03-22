/**
 * @file ls_fs_images.h
 *
 */

#ifndef LS_FS_IMAGES_H
#define LS_FS_IMAGES_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
/**
 * Create images from variable and file
 */
void ls_fs_image_init(void);

void ls_fs_image_draw(const char *src_img, uint8_t x, uint8_t y);



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LS_FS_IMAGES_H*/
