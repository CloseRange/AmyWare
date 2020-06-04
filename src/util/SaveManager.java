package util;

import java.io.File;

public class SaveManager implements ExplorerAction {
  public static String location;
  public static void init() {

  }
  public static void load() {
    new FileExplorer("D:\\Programs\\Java\\AmyWare\\Saves", "amy", new SaveManager());
  }
  @Override
  public void onSelect(File f) {

  }
  @Override
  public void onCancle() {

  }
  public void createProject() {

  }
}
