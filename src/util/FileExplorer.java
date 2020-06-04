package util;

import java.io.File;
import java.util.List;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.BoxLayout;
import java.awt.Color;
import gui.Pallette;
import java.awt.event.*;
import java.awt.*;
import javax.swing.BorderFactory;


public class FileExplorer {
  public String location, extension;
  public List<File> files;
  public List<JButton> buttons;
  public JFrame frame;
  private ExplorerAction callback;
  public FileExplorer(String location, String extension, ExplorerAction callback) {
    this.location = location;
    this.extension = extension;
    this.callback = callback;
    frame = new JFrame();
    files = new ArrayList<File>();
    buttons = new ArrayList<JButton>();
    int c = fileSearch(location) +1;
    int s = c * 64;
    frame.setPreferredSize(new Dimension(500, s));
    frame.setMaximumSize(new Dimension(500, s));
    frame.setMinimumSize(new Dimension(500, s));
    frame.setLayout(new GridLayout(c, 1));
    frame.setLocationRelativeTo(null);
    frame.setUndecorated(true);
    // frame.setLayout(new BoxLayout(frame, BoxLayout.Y_AXIS));

    for(File f : files) {
      JButton b = makeButton(f.getName(), f, false);
      frame.add(b);
    }
    frame.add(makeButton("Cancle", null, true));
    frame.setAlwaysOnTop(true);
    frame.getRootPane().setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Pallette.tint));
    frame.pack();
    frame.setVisible(true);
  }
  private JButton makeButton(String text, File f, boolean IsCancle) {
    JButton b = new JButton(text);
    b.setBorderPainted(false);
    b.setFocusPainted(false);
    // b.setContentAreaFilled(false);
    b.setForeground(Pallette.tint);
    b.setBackground(Pallette.background);
    b.addMouseListener(new java.awt.event.MouseAdapter() {
      public void mouseEntered(java.awt.event.MouseEvent evt) {
        b.setBackground(Pallette.highlight);
      }
      public void mouseExited(java.awt.event.MouseEvent evt) {
        b.setBackground(Pallette.background);
      }
    });
    b.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if(IsCancle) callback.onCancle();
        else callback.onSelect(f);
        frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
      }
    });
    return b;
    // buttons.add(b);
  }
  private int fileSearch(String path) {
    int i = 0;
    File root = new File(path);
    File[] list = root.listFiles();
    for(File f : list) {
      String fname = f.getAbsolutePath();
      if(f.isDirectory()) {
        i += fileSearch(f.getAbsolutePath());
      } else {
        if(fname.substring(fname.lastIndexOf(".") + 1).equals(extension)) {
          i++;
          files.add(f);
        }
      }
    }
    return i;
  }
}
