#include "main.h"

void colorSwitchInit()
{
  /*Create styles for the switch*/
  static lv_style_t bg_style;
  static lv_style_t indic_style;
  static lv_style_t knob_on_style;
  static lv_style_t knob_off_style;

  lv_style_copy(&bg_style, &lv_style_plain);
  bg_style.body.radius = LV_RADIUS_CIRCLE;

  lv_style_copy(&indic_style, &lv_style_plain);
  indic_style.body.radius = LV_RADIUS_CIRCLE;
  indic_style.body.padding.hor = 0;
  indic_style.body.padding.ver = 0;

  lv_style_copy(&knob_off_style, &lv_style_plain);
  knob_off_style.body.main_color = LV_COLOR_BLUE;
  knob_off_style.body.grad_color = LV_COLOR_BLUE;
  knob_off_style.body.radius = LV_RADIUS_CIRCLE;
  knob_off_style.body.shadow.width = 0;
  knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&knob_on_style, &lv_style_plain);
  knob_on_style.body.main_color = LV_COLOR_RED;
  knob_on_style.body.grad_color = LV_COLOR_RED;
  knob_on_style.body.radius = LV_RADIUS_CIRCLE;
  knob_on_style.body.shadow.width = 0;
  knob_on_style.body.shadow.type = LV_SHADOW_BOTTOM;

  /*Create a switch and apply the styles*/
  lv_obj_t * sw1 = lv_sw_create(lv_scr_act(), NULL);
  lv_sw_set_style(sw1, LV_SW_STYLE_BG, &bg_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_INDIC, &indic_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_ON, &knob_on_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_OFF, &knob_off_style);

  lv_obj_set_size(sw1, 120, 45);
  lv_obj_align(sw1, NULL, LV_ALIGN_IN_RIGHT_MID, -69, 0);
}

void sizeSwitchInit()
{
  /*Create styles for the switch*/
  static lv_style_t bg_style;
  static lv_style_t indic_style;
  static lv_style_t knob_on_style;
  static lv_style_t knob_off_style;

  lv_style_copy(&bg_style, &lv_style_plain);
  bg_style.body.radius = LV_RADIUS_CIRCLE;

  lv_style_copy(&indic_style, &lv_style_plain);
  indic_style.body.radius = LV_RADIUS_CIRCLE;
  indic_style.body.padding.hor = 0;
  indic_style.body.padding.ver = 0;

  lv_style_copy(&knob_off_style, &lv_style_plain);
  knob_off_style.body.main_color = LV_COLOR_PURPLE;
  knob_off_style.body.grad_color = LV_COLOR_PURPLE;
  knob_off_style.body.radius = 60;
  knob_off_style.body.shadow.width = 0;
  knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&knob_on_style, &lv_style_plain);
  knob_on_style.body.main_color = LV_COLOR_YELLOW;
  knob_on_style.body.grad_color = LV_COLOR_YELLOW;
  knob_on_style.body.radius = 20;
  knob_on_style.body.shadow.width = 0;
  knob_on_style.body.shadow.type = LV_SHADOW_BOTTOM;

  /*Create a switch and apply the styles*/
  lv_obj_t * sw1 = lv_sw_create(lv_scr_act(), NULL);
  lv_sw_set_style(sw1, LV_SW_STYLE_BG, &bg_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_INDIC, &indic_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_ON, &knob_on_style);
  lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_OFF, &knob_off_style);

  lv_obj_set_size(sw1, 120, 45);
  lv_obj_align(sw1, NULL, LV_ALIGN_IN_LEFT_MID, 69, 0);
}

void showLabels()
{
  lv_obj_t * sizeLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(sizeLabel,
    "This switch is to select\nthe size of the zone");
  lv_obj_t * colorLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(colorLabel,
    "This switch is to select\nthe color");
  lv_obj_t * sizeExplanation = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(sizeExplanation,
    "Purple = Small Goal\nYellow = Big Goal");
  lv_obj_t * teamName = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(teamName,
    "Menlo Mallards\n94027A");

  lv_obj_align(sizeLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_align(colorLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
  lv_obj_align(sizeExplanation, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
  lv_obj_align(teamName, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
}
