#include <stdio.h>
#include <unistd.h>

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/XPT7603.h"
#include "lvgl/lvgl.h"

#define DISP_BUF_SIZE (80*LV_HOR_RES_MAX)


void set_button_style(lv_obj_t * btn) {
  

  
  // set the pressed style
  static lv_style_t style_btn_pr;
  lv_style_copy(&style_btn_pr, &lv_style_btn_pr);         /*Initialize from a built-in style*/
  style_btn_pr.body.main_color = lv_color_hex(0x27ae60);
  // style_btn_pr.body.grad_color = lv_color_hex(0xecf0f1);
  
  lv_btn_set_style(btn, LV_BTN_STYLE_PR, &style_btn_pr);    /*Set the button's released style*/
  
  // set the normal style
  static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
  lv_style_copy(&style_btn_rel, &lv_style_btn_rel);         /*Initialize from a built-in style*/
  style_btn_rel.body.main_color = lv_color_hex(0x2ecc71);
  style_btn_rel.body.grad_color = lv_color_hex(0xecf0f1);
  
  lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
}

// defining an event handler for example button presses
static void event_handler(lv_obj_t * obj, lv_event_t event)
{
  if(event == LV_EVENT_PRESSED) {
    printf("Clicked\n");
    lv_obj_t * label = lv_obj_get_child(obj, NULL);
    lv_label_set_text(label, "OK");
    set_button_style(obj);
  }
  // else if(event == LV_EVENT_VALUE_CHANGED) {
  //   printf("Toggled\n");
  // }
}

// function to create buttons
void create_button(uint8_t alignment) {
  lv_obj_t * btnLabel;

  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_event_cb(btn1, event_handler);
  lv_obj_align(btn1, NULL, alignment, 0, 0);

  btnLabel = lv_label_create(btn1, NULL);
  lv_label_set_text(btnLabel, "Press Me");
}

// main program for lv_example
int main(int argc, char *argv[]) {
  
  printf("lv_init\n");
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
  
  /*Initialize and register an input device*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = xpt7603_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/
  
  /*Create 5 buttons*/
  create_button(LV_ALIGN_IN_TOP_LEFT);
  create_button(LV_ALIGN_IN_TOP_RIGHT);
  create_button(LV_ALIGN_IN_BOTTOM_LEFT);
  create_button(LV_ALIGN_IN_BOTTOM_RIGHT);
  create_button(LV_ALIGN_CENTER);
  
  
  
  printf("starting loop\n");
  while(1) {
    lv_tick_inc(5);
    lv_task_handler();
    usleep(5000);
  }
  
  return 0;
}
