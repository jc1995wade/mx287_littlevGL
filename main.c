#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_examples/lv_apps/demo/demo.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "ls_fs_images.h"
#include "ls_ui_common.h"

#define DISP_BUF_SIZE (80*LV_HOR_RES_MAX)


void* ui_update_fun(void* _val)
{
	int i = 0;
	printf("%s\n", (char*)_val);
	sleep(1);
	while(1){
		sleep(2);
		if(++i > 4) {
			i = 0;
		}
		//printf("update i=%d\n", i);
		ls_img_update(i, i, i);
	}
}

int create_ui_thread(void)
{
	int ret;
    pthread_t pid_3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&pid_3, &attr, ui_update_fun, "ui_update_fun ...");
    if (-1 == ret) {
        printf("create error!\n");
        return -1;
    }
}


int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    lv_disp_drv_register(&disp_drv);


    /*Create a Demo*/
    //demo_create();
	//printf("draw png\n");

	ls_fs_image_init();
    ls_taskbar_init();
	ls_one_interface();
	create_ui_thread();
	//ls_fs_image_draw("/root/ui_res/test.png", 0, 0);
	//printf("draw png end\n");
	/*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_task_handler();
        usleep(5000);
    }

    return 0;
}


/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
