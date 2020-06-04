package gui;

import java.awt.Color;


public class Pallette {
  public static Color background, highlight, textBase, textNormal, textSystem, textVariable, textBuiltIn, textClass, textComment, tint;
  public static void init() {
    background = new Color(34, 34, 34);
    highlight = new Color(68, 68, 68);

    textBase = new Color(250, 250, 250);
    textNormal = new Color(192, 192, 192);
    textSystem = new Color(255, 184, 113);
    textVariable = new Color(118, 179, 193);
    textBuiltIn = new Color(224, 114, 114);
    textClass = new Color(252, 126, 189);
    textComment = new Color(90, 152, 90);

    tint = new Color(3, 157, 91);
  }
}
