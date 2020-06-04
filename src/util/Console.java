package util;

import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.BorderFactory;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import gui.Pallette;
import gui.GUI;
import gui.FontTable;
import java.awt.Color;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.text.AttributeSet;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyleContext;

public class Console {
  public static JScrollPane frame;
  public static JTextArea textArea;
  // public static JScrollPane scroll;
  public static void init() {
    textArea = new JTextArea();
    textArea.setFont(FontTable.mainFont.generate());
    // scroll = new JScrollPane(frame);
    textArea.setEditable(false);
    textArea.setLineWrap(true);
    textArea.setWrapStyleWord(true);
    // frame.setBorder(BorderFactory.createEmptyBorder());
    textArea.setBackground(Pallette.background);
    textArea.setForeground(Pallette.tint);
    textArea.setMinimumSize(new Dimension(600, 200));
    frame = new JScrollPane(textArea);
    frame.setFont(GUI.font);
    // frame.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLL)

  }
  public static void write(String text) {
    textArea.append(text + "\n");
    JScrollBar vertical = frame.getVerticalScrollBar();
    vertical.setValue( vertical.getMaximum() );
  }
  public static void clear() {
    textArea.setText("");
  }

  // public static void appendToConsole(String msg, Color c) {
  //   StyleContext sc = StyleContext.getDefaultStyleContext();
  //   AttributeSet aset = sc.addAttribute(SimpleAttributeSet.EMPTY, StyleConstants.Foreground, c);
  //
  //   aset = sc.addAttribute(aset, StyleConstants.FontFamily, "Lucida Console");
  //   aset = sc.addAttribute(aset, StyleConstants.Alignment, StyleConstants.ALIGN_JUSTIFIED);
  //
  //   int len = frame.getDocument().getLength();
  //   frame.setCaretPosition(len);
  //   frame.setCharacterAttributes(aset, false);
  //   frame.replaceSelection(msg);
  // }
}
