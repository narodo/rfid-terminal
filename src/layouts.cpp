#include "Arduino.h"
#include <U8g2_for_Adafruit_GFX.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <Adafruit_GFX.h>
#include <GxEPD2_GFX.h>
#include <ArduinoLog.h>
#include "config.h"
#include "layouts.h"
#include "display.h"

extern U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
extern GxEPD2_DISPLAY display; 


namespace Layout {


void TextBox::updateContent(String new_content) {

    content = new_content;
    rendered_content= new_content;

    u8g2Fonts.setFont(font); 
    text_width =  u8g2Fonts.getUTF8Width(rendered_content.c_str());

    while(width < text_width) { // text box width
        Log.trace("%s, text_width: %d \n", rendered_content, text_width);
        rendered_content.remove(rendered_content.length() - 1 );
        rendered_content[rendered_content.length() - 1 ] = '.';
        text_width = u8g2Fonts.getUTF8Width(rendered_content.c_str());
        delay(500);
    }

    updateConfig();
}

void TextBox::updateConfig() {

    u8g2Fonts.setFont(font); 
    
    int16_t ta = u8g2Fonts.getFontAscent(); // positive
    int16_t td = u8g2Fonts.getFontDescent(); // negative; in mathematicians view
    // we didn't calculate font height yet
    if (font_height  == 0) {
        font_height = ta + td; // text box height
    }

    // y always centered in text box
    if (font_height > height)  { // if font does not fit in box align on bottom
        cur_y = y + height;
    } else {
        cur_y = y + height -  (height - font_height) / 2 ;
    }
          
    switch(align) 
    {
        case left: 
            cur_x = x + MARGINLEFTRIGHT; 
            Log.trace("Setting up alignment left (cur_x:  %d)\n",  cur_x);
            break;
        case right: 
            cur_x = x + (width - text_width) - MARGINLEFTRIGHT ;
            Log.trace("Setting up alignment right (cur_x:  %d)\n",  cur_x);
            break;
        // centered 
        default: 
            Log.trace("Setting up alignment other (cur_x:  %d)\n",  cur_x);
            cur_x = x + ((width - text_width) / 2);
            break;
    }

    Log.trace("\n\nChange content: %s, width: %d text_width: %d \n", rendered_content, width, text_width);
    Log.trace("Height: %d Font height: %d \n",  height, font_height);
    Log.trace("Align: %d Style: %d \n",  align, style);
    Log.trace("Textbox x: %d Textbox y: %d \n", x, y);
    Log.trace("Cursor x: %d y: %d \n",  cur_x, cur_y);
}

void TextBox::render() {
    
    u8g2Fonts.setFont(font);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color

    // render 
    Log.trace("Loop Render: %s, x: %d y: %d \n", content, cur_x, cur_y);
    u8g2Fonts.setCursor(cur_x, cur_y); // start writing at this position
    u8g2Fonts.print(rendered_content);

    switch(style) 
    {
        case thickbox:
            display.drawRect(x+1, y+1, width-2, height-2, fg);
        case box:
            display.drawRect(x, y, width, height, fg);
            break;
        default:
            break;
    }

}

} //namespace
