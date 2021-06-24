#include "GridUtil.h"

GURect GridUtil::convert(int x, int y, int w, int h) {

  int res_x = 0;
  if (x <= 1) {
    res_x = padding_x;
  } else {
    res_x = padding_x + ((x - 1) * gridspan_x) + margin_x_half;
  }
  
  int res_y = 0;
  if (y <= 1) {
    res_y = padding_y;
  } else {
    res_y = padding_y + ((y - 1) * gridspan_y) + margin_y_half;
  }

  int res_w = 0;
  res_w = w * gridspan_x;
  if (x > 1) {
    res_w -= margin_x_half;
  }
  if ((x - 1 + w) < gridcount_x) {
    res_w -= margin_x_half;
  }

  int res_h = 0;
  res_h = h * gridspan_y;
  if (y > 1) {
    res_h -= margin_y_half;
  }
  if ((y - 1 + h) < gridcount_y) {
    res_h -= margin_y_half;
  }

  GURect r = {
    res_x,
    res_y,
    res_w,
    res_h
  };

  return r;
}

void GridUtil::setVertical(bool is_vertical) {
  GURectSetVertical v;
  this->gridspan_x = v.gridspan_x;
  this->gridcount_x = v.gridcount_x;
  this->padding_x = v.padding_x;
  this->margin_x_half = v.margin_x_half;
  this->gridspan_y = v.gridspan_y;
  this->gridcount_y = v.gridcount_y;
  this->padding_y = v.padding_y;
  this->margin_y_half = v.margin_y_half;
}
