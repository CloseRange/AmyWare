package util;

import java.io.File;

public interface ExplorerAction {
  void onSelect(File f);
  void onCancle();
}
