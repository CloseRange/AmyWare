package util;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.file.Paths;
import gui.Navigation;

public class TestRunner implements Runnable {
  public static boolean running = false;
  private static TestRunner runningThread;
  private static Thread thread;
  private static Process process;
  private String name;
  public TestRunner(String name) {
    this.name = name;
  }
  public void run() {
    try {
      process = Runtime.getRuntime().exec("java -cp D:\\Programs\\Java\\MakotasTavern\\scr; Main");
      try(BufferedReader input = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
          String line;
          while ((line = input.readLine()) != null) {
              System.out.println("-" + line);
              Console.write(line);
          }
          running = false;
          Navigation.miRun.setVisible(true);
          Navigation.miStop.setVisible(false);
      }
    } catch(Exception e) {e.printStackTrace();}
  }
  public static void start() {
    if(running) return;
    Console.clear();
    running = true;
    runningThread = new TestRunner("gameTest");
    thread = new Thread(runningThread, "gameTest");
    thread.start();
    Navigation.miRun.setVisible(false);
    Navigation.miStop.setVisible(true);
  }
  public static void stop() {
    if(!running) return;
    process.destroy();
  }
}
