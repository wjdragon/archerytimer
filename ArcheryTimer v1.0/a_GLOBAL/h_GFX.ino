void centerText(String text)
{
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  display.setCursor((SCREEN_WIDTH - width) / 2, display.getCursorY());    //only center on X axis, keep current Y axis
  display.println(text);
}
