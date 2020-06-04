import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.file.Paths;

import gui.GUI;
import gui.Pallette;
import util.Console;
import gui.FontTable;
import java.io.File;

import util.FileExplorer;

public class Main {
  public static GUI gui;
  public static void main(String[] args) {
    FontTable.init();
    Pallette.init();
    Console.init();
    gui = new GUI("AmyWare", 1920, 1080);

  }
}
