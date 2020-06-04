package gui;
import java.awt.Font;


public class FontTable {
  public static FontTable.Type mainFont;
  public static void init() {
    mainFont = new FontTable.Type("Courier", Font.BOLD, 32);
  }
  public static class Type {
    public String name;
    public int type;
    public int size;
    public Font font;
    public Font generate() {
      return new Font(name, type, size);
    }
    public Type(String name, int type, int size) {
      this.name = name;
      this.type = type;
      this.size = size;
    }
  }
}
