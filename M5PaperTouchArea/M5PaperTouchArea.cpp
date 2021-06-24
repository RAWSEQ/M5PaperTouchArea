#include "M5PaperTouchArea.h"

M5PaperTouchAreas* M5PaperTouchAreas::add(int16_t x, int16_t y, int16_t w, int16_t h, String label, String code, int font_size, int radius) {
  M5PTArea ar = {
    this->id_counter,
    code,
    x,
    y,
    w,
    h,
    label,
    (font_size >= 0) ? font_size : this->default_font_size,
    (radius >= 0) ? radius : this->default_radius,
    this->default_font_linepos,
    this->default_bc,
  };
  this->current_id = this->id_counter;
  this->areas.push_back(ar);
  this->id_counter++;
  return this;
}

M5PaperTouchAreas* M5PaperTouchAreas::add_grid(int x, int y, int w, int h, String label, String code, int font_size, int radius) {
  gur = gutil.convert(x, y, w, h);
  return this->add(gur.x, gur.y, gur.w, gur.h, label, code, font_size, radius);
}

M5PaperTouchAreas* M5PaperTouchAreas::set_bc(M5PTAreaColors bc) {
  this->areas[this->getAreasIdx(this->current_id)].bc = bc;
}

M5PaperTouchAreas* M5PaperTouchAreas::set_font_linepos(int pos) {
  this->areas[this->getAreasIdx(this->current_id)].font_linepos = pos;
}

GridUtil* M5PaperTouchAreas::getGutil() {
  return &gutil;
}

int M5PaperTouchAreas::getAreasIdx(int id) {
  int idx = 0;
  for (auto ar : this->areas) {
    if (ar.id == this->current_id) break;
    idx++;
  }
  return idx;
}

void M5PaperTouchAreas::loop() {
  if(M5.TP.avaliable()){
    tp_finger_t fi = M5.TP.readFinger(0);
    M5.TP.update();
    bool fu = M5.TP.isFingerUp();

    if (this->is_finger_up != fu) {
      this->is_finger_up = fu;

      for (auto ar : this->areas) {
        if (ar.x <= fi.x && (ar.x + ar.w) >= fi.x && ar.y <= fi.y && (ar.y + ar.h) >= fi.y) {
          M5PTAEventContext ct = M5PTAEventContext();
          ct.finger = fi;
          ct.label = ar.label;
          ct.code = ar.code;
          if(!this->is_finger_up){
            if (this->e_touch.func) this->e_touch.func(ct);
          } else {
            if (this->e_release.func) this->e_release.func(ct);
          }
        }
      }
    }
  }
}

void M5PaperTouchAreas::draw(int id) {
  for (auto ar : this->areas) {
    if (id >= 0 && ar.id != id) continue;
    this->current_canvas->fillRoundRect(ar.x, ar.y, ar.w, ar.h, ar.radius ,ar.bc.bg);
    this->current_canvas->drawRoundRect(ar.x, ar.y, ar.w, ar.h, ar.radius ,ar.bc.outline);
    this->current_canvas->setTextColor(ar.bc.text);
    this->current_canvas->setTextDatum(CC_DATUM);
    this->current_canvas->setTextSize(ar.font_size);
    this->current_canvas->drawString(ar.label, ar.x + (ar.w / 2), ar.y + (ar.h / 2) + ar.font_linepos);
  }
}

void M5PaperTouchAreas::clear(int id) {
  for (int i = this->areas.size() - 1; i >= 0; --i) {
    if (id >= 0 && this->areas[i].id != id) continue;
    this->areas.erase(this->areas.begin() + i);
    this->areas.shrink_to_fit();
  }
}
