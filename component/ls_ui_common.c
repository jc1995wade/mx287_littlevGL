#include "ls_ui_common.h"

#include "lvgl/lvgl.h"

typedef struct {
	uint8_t hor;
	uint8_t ver;
}m_size_t;


typedef struct {	
	m_size_t    size;
	const char *path;
	lv_obj_t   *img_obj;
}m_label_t;

typedef struct {
	m_size_t  size;
	m_label_t signal;
	m_label_t battery;
	m_label_t volume;
}m_taskbar_t;

static m_taskbar_t s_top_taskbar; 

static lv_obj_t * img_signal;
static lv_obj_t * img_battery;
static lv_obj_t * img_volume;


static lv_obj_t *canvas;

static const char *img_signal_path[] = {
	"/root/ui_res/signal_0.png",
	"/root/ui_res/signal_1.png",
	"/root/ui_res/signal_2.png",
	"/root/ui_res/signal_3.png",
	"/root/ui_res/signal_4.png",
	NULL
};

static const char *img_battery_path[] = {
	"/root/ui_res/battery_0.png",
	"/root/ui_res/battery_1.png",
	"/root/ui_res/battery_2.png",
	"/root/ui_res/battery_3.png",
	"/root/ui_res/battery_4.png",
	NULL
};

static const char *img_volume_path[] = {
	"/root/ui_res/volume_0.png",
	"/root/ui_res/volume_1.png",
	"/root/ui_res/volume_2.png",
	"/root/ui_res/volume_3.png",
	"/root/ui_res/volume_4.png",
	NULL
};

m_taskbar_t *get_static_taskbar(void)
{
	return &s_top_taskbar;
}



void ls_taskbar_init()
{
	m_taskbar_t *taskbar = get_static_taskbar();
	
	taskbar->size.hor = lv_disp_get_hor_res(NULL);
	taskbar->size.ver = 10;
}

static lv_color_t *get_static_buffer(int num)
{
	return malloc(sizeof(lv_color_t)*num);
}

void ls_one_interface(void)
{
	m_taskbar_t *taskbar = get_static_taskbar();
	
	lv_coord_t hres = lv_disp_get_hor_res(NULL);
	lv_coord_t vres = lv_disp_get_ver_res(NULL);
	printf("hres=%d, vres=%d\n", hres, vres);

	canvas = lv_canvas_create(lv_scr_act(), NULL);
	//static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(hres, vres)];
	static lv_color_t *cbuf = NULL;
	cbuf = get_static_buffer(LV_CANVAS_BUF_SIZE_TRUE_COLOR(hres, vres));
	
	lv_canvas_set_buffer(canvas, cbuf, hres, vres, LV_IMG_CF_TRUE_COLOR);
	lv_obj_set_pos(canvas, 0, 0);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);

	taskbar->signal.img_obj = lv_img_create(canvas, NULL);
	lv_img_set_src(taskbar->signal.img_obj, img_signal_path[0]);
	lv_obj_set_pos(taskbar->signal.img_obj, 0, 0);      /*Set the positions*/
	lv_obj_set_drag(taskbar->signal.img_obj, true);

	taskbar->battery.img_obj = lv_img_create(canvas, NULL);
	lv_img_set_src(taskbar->battery.img_obj, img_battery_path[0]);
	lv_obj_set_pos(taskbar->battery.img_obj, hres-17, 0);      /*Set the positions*/
	lv_obj_set_drag(taskbar->battery.img_obj, true);

	taskbar->volume.img_obj = lv_img_create(canvas, NULL);
	lv_img_set_src(taskbar->volume.img_obj, img_volume_path[0]);
	lv_obj_set_pos(taskbar->volume.img_obj, 15, 0);      /*Set the positions*/
	lv_obj_set_drag(taskbar->volume.img_obj, true);
}



#if 0
void lv_ex_cont_1(const char *src_img)
{
	static lv_style_t style;
	lv_style_copy(&style, &lv_style_scr);
	style.body.border.width = 1;

	cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_pos(cont, 0, 20);
	lv_cont_set_style(cont, LV_CONT_STYLE_MAIN, &style);
	lv_obj_set_auto_realign(cont, true);                    /*Auto realign when the size changes*/
	lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
	lv_cont_set_fit(cont, LV_FIT_TIGHT);
	lv_cont_set_layout(cont, LV_LAYOUT_COL_M);
	

	//lv_obj_t * label;
	//label = lv_label_create(cont, NULL);
	//lv_label_set_text(label, "Short text");

	//label = lv_label_create(cont, NULL);
	//lv_label_set_text(label, "It is a long");

	//lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/
	img_bin = lv_img_create(cont, NULL);
	lv_img_set_src(img_bin, src_img);
	//lv_obj_set_pos(img_bin, x, y);      /*Set the positions*/
	lv_obj_set_drag(img_bin, true);

	//label = lv_label_create(cont, NULL);
	//lv_label_set_text(label, "Here is an");
    
}

#endif

void ls_img_update(uint8_t signal, uint8_t battery, uint8_t volume)
{
	//printf("0 : %d\n", signal);
	m_taskbar_t *taskbar = get_static_taskbar();
	
	if (signal <= 4) {
		lv_img_set_src(taskbar->signal.img_obj, img_signal_path[signal]);
		lv_obj_set_drag(taskbar->signal.img_obj, true);
		//lv_obj_invalidate(taskbar->signal.img_obj);
	}
	return ;
	if (battery <=4) {
		lv_img_set_src(taskbar->battery.img_obj, img_battery_path[signal]);
		lv_obj_set_drag(taskbar->battery.img_obj, true);
		lv_obj_invalidate(taskbar->battery.img_obj);
	}

	if (volume <=4) {
		lv_img_set_src(taskbar->volume.img_obj, img_volume_path[signal]);
		lv_obj_set_drag(taskbar->volume.img_obj, true);
		lv_obj_invalidate(taskbar->volume.img_obj);
	}
	
}


