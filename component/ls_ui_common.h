#ifndef __LS_COMMON_H__
#define __LS_COMMON_H__

#include <stdio.h>
#include <stdint.h>

void lv_ex_cont_1(const char *src_img);

void ls_img_update(uint8_t signal, uint8_t battery, uint8_t volume);

void ls_one_interface(void);



#endif

