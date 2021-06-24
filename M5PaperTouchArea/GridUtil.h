
struct GURect {
  int x;
  int y;
  int w;
  int h;
};

struct GURectSetVertical {
  int gridspan_x = 100;
  int gridcount_x = 5;
  int padding_x = 20;
  int margin_x_half = 10;
  int gridspan_y = 100;
  int gridcount_y = 9;
  int padding_y = 30;
  int margin_y_half = 10;
};

class GridUtil;

class GridUtil {
  public:
    GURect convert(int x, int y, int w, int h);
    void setVertical(bool is_vertical);
    bool is_vertical = false;
    int gridspan_x = 100;
    int gridcount_x = 9;
    int padding_x = 30;
    int margin_x_half = 10;
    int gridspan_y = 100;
    int gridcount_y = 5;
    int padding_y = 20;
    int margin_y_half = 10;
};
