#ifndef _LAYOUT_HEADER_GUARD_
#define _LAYOUT_HEADER_GUARD_

#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>

#include "display.h"

#define MARGINLEFTRIGHT 2

#define DISP_WIDTH 296
#define DISP_HEIGHT 128

namespace Layout {

enum Alignment { center, left, right };

enum Style { normal, box, thickbox, line_box };

class TextBox {
   public:
    TextBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
            const uint8_t *font, uint16_t bg = GxEPD_WHITE,
            uint16_t fg = GxEPD_BLACK, enum Alignment align = center,
            enum Style style = normal)
        : x(x),
          y(y),
          width(width),
          height(height),
          font(font),
          font_height(0),
          bg(bg),
          fg(fg),
          align(align),
          style(style) {}

    void updateContent(String new_content);

    void setAlignment(enum Alignment new_align) {
        align = new_align;
        updateConfig();
    }

    void setStyle(enum Style new_style) {
        style = new_style;
        updateConfig();
    }

    void clear();

    void render();

    uint16_t x, y;
    uint16_t height, width;
    uint16_t bg, fg;

   private:
    uint16_t cur_x, cur_y;
    uint16_t font_height = 0;
    uint16_t text_width = 0;
    const uint8_t *font;
    uint8_t max_chars;
    enum Alignment align;
    enum Style style;
    String content;
    String rendered_content;
    void updateConfig();
};

class LayoutMain {
   public:
    TextBox TB_title;
    TextBox TB_main;
    TextBox TB_sub;

    LayoutMain()
        : TB_title(0, 0, DISP_WIDTH, DISP_HEIGHT / 5, u8g2_font_helvB12_tf,
                   GxEPD_WHITE, GxEPD_BLACK, center, normal),
          TB_main(0, 1 * DISP_HEIGHT / 5, DISP_WIDTH, 2 * DISP_HEIGHT / 5,
                  u8g2_font_helvB24_tf, GxEPD_WHITE, GxEPD_BLACK, center,
                  thickbox),
          TB_sub(0, 3 * DISP_HEIGHT / 5, DISP_WIDTH, 2 * DISP_HEIGHT / 5,
                 u8g2_font_inb30_mr, GxEPD_WHITE, GxEPD_BLACK, center, normal) {
    }

    void refreshAll();

    void updateTitle(String new_string);
    void updateMain(String new_string);
    void updateSub(String new_string);

   private:
    void updatePartial(TextBox &TB, String new_string);
};

}  // namespace Layout

#endif
