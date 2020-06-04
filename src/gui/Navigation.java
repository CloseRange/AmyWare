package gui;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.event.MenuListener;
import javax.swing.event.MenuEvent;
import javax.swing.BorderFactory;
import util.SaveManager;

import util.TestRunner;

public class Navigation implements MenuListener, ActionListener, KeyListener {
  public static JMenuBar menu;
  public static JMenu mFile, mOptions, mTest;
  public static JMenuItem miSave, miLoad, miExit, miCompile, miRun, miStop;
  public static Navigation listener;
  public static void init() {
    listener = new Navigation();
    menu = new JMenuBar();
    menu.setBackground(Pallette.background);

    // mFile = new JMenu("File");
    mFile = menu("File");
    mOptions = menu("Options");
    mTest = menu("Test");
    // mOptions = new JMenu("Options");
    // mTest = new JMenu("Test");

    miSave = item("Save");
    miLoad = item("Open");
    miExit = item("Quit");
    mFile.add(miSave);
    mFile.add(miLoad);
    mFile.add(miExit);

    miCompile = item("Compile", "compile.png");
    miRun = item("Run", "start.png");
    miStop = item("Stop", "start.png");
    miStop.setVisible(false);

    mTest.add(miCompile);
    mTest.add(miRun);
    mTest.add(miStop);

    menu.add(mFile);
    menu.add(mOptions);
    menu.add(mTest);
  }
  private static JMenuItem item(String txt) { return item(txt, ""); }
  private static JMenuItem item(String txt, String ico) {
    JMenuItem itm;
    if(ico == "") itm = new JMenuItem(txt);
    else itm = new JMenuItem(txt, getScaledImage(new ImageIcon("../res/" + ico), 32, 32));
    itm.addActionListener(listener);
    itm.setBackground(Pallette.background);
    itm.setForeground(Pallette.tint);
    itm.setBorderPainted(false);
    itm.setFocusPainted(false);
    itm.addMouseListener(new java.awt.event.MouseAdapter() {
      public void mouseEntered(java.awt.event.MouseEvent evt) {
        itm.setBackground(Pallette.highlight);
      }
      public void mouseExited(java.awt.event.MouseEvent evt) {
        itm.setBackground(Pallette.background);
      }
    });

    return itm;
  }
  private static JMenu menu(String txt) {
    JMenu itm;
    itm = new JMenu(txt);
    itm.setBackground(Pallette.background);
    itm.setOpaque(true);
    itm.setForeground(Pallette.tint);
    itm.setBorderPainted(false);
    itm.setFocusPainted(false);
    itm.addMouseListener(new java.awt.event.MouseAdapter() {
      public void mouseEntered(java.awt.event.MouseEvent evt) {
        itm.setBackground(Pallette.highlight);
      }
      public void mouseExited(java.awt.event.MouseEvent evt) {
        itm.setBackground(Pallette.background);
      }
    });

    return itm;
  }
  private static ImageIcon getScaledImage(ImageIcon srcImgICN, int w, int h){
    Image srcImg = srcImgICN.getImage();
    BufferedImage resizedImg = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
    Graphics2D g2 = resizedImg.createGraphics();

    g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
    g2.drawImage(srcImg, 0, 0, w, h, null);
    g2.dispose();

    return new ImageIcon(resizedImg);
  }
  @Override
  public void menuSelected(MenuEvent me) {
  }
  @Override
  public void actionPerformed(ActionEvent ev) {
    if(ev.getSource().equals(miRun)) {
      TestRunner.start();
    } else if(ev.getSource().equals(miStop)) {
      TestRunner.stop();
    } else if(ev.getSource().equals(miLoad)) {
      SaveManager.load();
    } else if(ev.getSource().equals(miExit)) {
      SaveManager.load();
    }
  }
  @Override
  public void menuDeselected(MenuEvent me) {}
  @Override
  public void menuCanceled(MenuEvent me) {}
  @Override
  public void keyTyped(KeyEvent k) {}
  @Override
  public void keyPressed(KeyEvent k) {}
  @Override
  public void keyReleased(KeyEvent k) {}

}
