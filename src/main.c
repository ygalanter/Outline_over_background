#include <pebble.h>
#include "effect_layer.h"

Window *my_window;
TextLayer *text_layer1;


EffectLayer* effect_layer;
EffectOffset outline;
EffectMask  background;
GColor transparent[1];


void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  window_stack_push(my_window, true);
  
  // creating text
  text_layer1 = text_layer_create(GRect(10, 50, 130, 80));
  text_layer_set_font(text_layer1, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_color(text_layer1, GColorWhite);
  text_layer_set_background_color(text_layer1, GColorClear);
  text_layer_set_text(text_layer1,"HELLO WORLD!");
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer1));
  
  effect_layer = effect_layer_create(GRect(0, 0,144,168));
  
  // creating outline effect
  outline.orig_color = GColorWhite;
  outline.offset_color = GColorRed;
  outline.offset_x = 1;
  outline.offset_y = 1;
  effect_layer_add_effect(effect_layer, effect_outline, &outline);
  
  // adding background via mask effect
  background.bitmap_background = gbitmap_create_with_resource(RESOURCE_ID_MASK_BG);
  transparent[0] = GColorBlack;
  background.mask_colors = transparent;
  effect_layer_add_effect(effect_layer, effect_mask, &background);
  
  layer_add_child(window_get_root_layer(my_window), effect_layer_get_layer(effect_layer));
  
  
  
}

void handle_deinit(void) {
  
  text_layer_destroy(text_layer1);
  
  effect_layer_destroy(effect_layer);
  
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
