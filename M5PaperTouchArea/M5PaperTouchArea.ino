#include <M5EPD.h>
#include "M5PaperTouchArea.h"
#include "MPlusFontsSubset.h"

// M5EPD Canvas
M5EPD_Canvas canvas(&M5.EPD);

// Module (Grid & TouchArea)
M5PaperTouchAreas _m5pta;

// Module (Grid Only)
GridUtil _gu;

void setup() {
  
  // Display Setup
  M5.begin();
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  canvas.loadFont(MPlusFontsSubset, sizeof(MPlusFontsSubset));
  canvas.createCanvas(540, 960);
  canvas.createRender(48, 256);
  canvas.fillRect(0, 0, 540, 960, 15);
  _m5pta.current_canvas = &canvas;
  _m5pta.getGutil()->setVertical(true);
  _gu.setVertical(true);
  
  // Event Setting
  _m5pta.e_touch.func = bTouch;
  _m5pta.e_release.func = bRelease;
  
  // Change Default Setting
  _m5pta.default_font_size = 48;
  _m5pta.default_radius = 15;
  _m5pta.default_font_linepos = 6;
  _m5pta.default_bc = {13,0,0};

  // Touch Area Test
  _m5pta.add_grid(1,1,1,1,"B1","b1");
  _m5pta.add_grid(2,1,1,1,"B2","b2");
  _m5pta.add_grid(3,1,1,1,"B3","b3");
  _m5pta.add_grid(4,1,1,1,"B4","b4");
  _m5pta.add_grid(5,1,1,1,"B5","b5");
  _m5pta.add_grid(1,2,3,1,"B6","b6");
  _m5pta.add_grid(4,2,2,1,"B7","b7");
  _m5pta.add_grid(1,3,2,1,"B8","b8");
  _m5pta.add_grid(3,3,3,1,"B9","b9");
  _m5pta.add_grid(1,4,5,1,"B10タッチボタン","b10");
  _m5pta.add_grid(1,5,2,1,"B11","b11");
  _m5pta.add_grid(1,6,2,2,"B12","b12");
  _m5pta.add_grid(3,7,3,3,"B13","b13");
  _m5pta.add_grid(1,8,2,1,"B14","b14");
  _m5pta.add_grid(1,9,2,1,"B15","b15");
  _m5pta.draw();

  // Grid Draw Test
  GURect g = _gu.convert(3,5,3,2);
  canvas.fillRect(g.x, g.y, g.w, g.h, 0);

  // Push Canvas
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);

}

// Touch Event
void bTouch(M5PTAEventContext& ct) {
  Serial.println("T:"+ct.code);
}

// Release Event
void bRelease(M5PTAEventContext& ct) {
  Serial.println("R:"+ct.code);
}

void loop() {
  _m5pta.loop();
}
