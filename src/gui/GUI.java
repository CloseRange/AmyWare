package gui;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JSplitPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JEditorPane;
import javax.swing.BoxLayout;
import javax.swing.UIManager;
import java.awt.FlowLayout;

import javax.swing.BorderFactory;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.BorderFactory;
import java.io.File;

import util.Console;

public class GUI extends JFrame {
  private final JSplitPane fileSplit, consoleSplit, propertiesSplit;
  public final JPanel panelFile, panelConsole, panelProperties, panelWorkArea;


  public static Font font;
  public static GUI main;
  public GUI(String title, int width, int height) {
    font = FontTable.mainFont.generate();
    main = this;
    UIManager.getDefaults().put("SplitPane.border", BorderFactory.createEmptyBorder());
    // setUIFont(new javax.swing.plaf.FontUIResource("Serif",Font.ITALIC,32));
    setUIFont(font);
    panelFile = new JPanel();
    panelConsole = new JPanel();
      panelConsole.setLayout(new BorderLayout());
      panelConsole.add(Console.frame);
    panelProperties = new JPanel();
    panelWorkArea = new JPanel();
    panelFile.setLayout(new BoxLayout(panelFile, BoxLayout.Y_AXIS));
    panelProperties.setLayout(new BoxLayout(panelProperties, BoxLayout.Y_AXIS));

    fileSplit = new JSplitPane();
    consoleSplit = new JSplitPane();
    propertiesSplit = new JSplitPane();
    int s = 400;
    fileSplit.setOrientation(JSplitPane.HORIZONTAL_SPLIT);
    fileSplit.setDividerLocation(s);
    fileSplit.setLeftComponent(panelFile);
    fileSplit.setRightComponent(consoleSplit);

    consoleSplit.setOrientation(JSplitPane.VERTICAL_SPLIT);
    consoleSplit.setDividerLocation(height-s);
    consoleSplit.setBottomComponent(panelConsole);
    consoleSplit.setTopComponent(propertiesSplit);
    consoleSplit.setResizeWeight(1);

    // BasicSplitPaneDivider divider = (BasicSplitPaneDivider) consoleSplit.getComponent(2);
    // divider.setBackground(Color.red);
    // divider.setBorder(null);
    // consoleSplit.getComponent(2).setBorder(null);
    // dividerContainer.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));

    propertiesSplit.setOrientation(JSplitPane.HORIZONTAL_SPLIT);
    propertiesSplit.setDividerLocation(width-s*2);
    propertiesSplit.setLeftComponent(panelWorkArea);
    propertiesSplit.setRightComponent(panelProperties);
    propertiesSplit.setResizeWeight(1);


    panelFile.setBackground(Pallette.background);
    panelConsole.setBackground(Pallette.background);
    panelProperties.setBackground(Pallette.background);
    panelWorkArea.setBackground(Pallette.background);

    Navigation.init();
    setJMenuBar(Navigation.menu);
    add(fileSplit);
    setPreferredSize(new Dimension(width, height));     // let's open the window with a default size of 400x400 pixels
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    pack();   // calling pack() at the end, will ensure that every layout and size we just defined gets applied before the stuff becomes visible
    setVisible(true);
  }
  public static void setUIFont (Font f){
    java.util.Enumeration keys = UIManager.getDefaults().keys();
    while (keys.hasMoreElements()) {
      Object key = keys.nextElement();
      Object value = UIManager.get (key);
      if (value instanceof javax.swing.plaf.FontUIResource)
        UIManager.put (key, f);
    }
  }
}
