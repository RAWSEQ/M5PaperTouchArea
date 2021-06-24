#include <M5EPD.h>
#include "GridUtil.h"

class M5PaperTouchAreas;

struct M5PTAreaColors {
  uint16_t bg;
  uint16_t text;
  uint16_t outline;
};

struct M5PTAEventContext {
  tp_finger_t finger;
  String label;
  String code;
};

struct M5PTAEvent {
  void (*func)(M5PTAEventContext&);
};

struct M5PTArea {
  int id;
  String code;
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
  String label;
  int16_t font_size;
  int16_t radius;
  int font_linepos;
  M5PTAreaColors bc;
};

class M5PaperTouchAreas {
  public:
    M5PaperTouchAreas* add(int16_t x, int16_t y, int16_t w, int16_t h, String label = "", String code = "", int font_size = -1, int radius = -1);
    M5PaperTouchAreas* add_grid(int x, int y, int w, int h, String label = "", String code = "", int font_size = -1, int radius = -1);
    M5PaperTouchAreas* set_bc(M5PTAreaColors bc);
    M5PaperTouchAreas* set_font_linepos(int pos);
    GridUtil* getGutil();
    void loop();
    void draw(int id = -1);
    void clear(int id = -1);
    M5PTAEvent e_touch;
    M5PTAEvent e_release;
    std::vector<M5PTArea> areas;
    M5EPD_Canvas* current_canvas;
    int default_font_size = 4;
    int default_radius = 15;
    int default_font_linepos = 0;
    M5PTAreaColors default_bc = {0, 15, 15};
    GURect gur;
    GridUtil gutil;
    bool is_finger_up = true;
    int id_counter = 0;
    int current_id = 0;
  private:
    int getAreasIdx(int id);
};
