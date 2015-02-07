/*
ID: webmast33
LANG: JAVA
TASK: castle
 */
import java.io.*;
import java.util.*;

public class castle {

  int m;
  int n;
  int[][] component;
  int[][] map;
  int currentComponent;
  int[] areas;
  int[][] walls;

  final static int UNCHECK = -3;
  final static int TO_VISIT = -2;

  public String[] solve(int n, int m, int[][] map) {
    // Init
    init(m, n, map);
    floodfill();

    int maxArea = maxArea();
    findWalls();
    int maxCombined = findMaxCombined();

    String[] res = new String[4];
    res[0] = String.valueOf(currentComponent);
    res[1] = String.valueOf(maxArea);
    res[2] = String.valueOf(maxCombined);
    res[3] = decodeWall();

    return res;
  }

  private String decodeWall() {
    String d = (maxWall % 100 == 1) ? "N" : "E";
    maxWall /= 100;
    int i =  maxWall % 100;
    maxWall /= 100;
    int j = n - maxWall % 100;
    return String.format("%d %d %s", i, j, d);
  }

  int maxWall = 0;

  private int findMaxCombined() {
    int maxComb = 0;
    for (int i = 0; i <= currentComponent; i++) {
      for (int j = i + 1; j <= currentComponent; j++) {
        if (walls[i][j] > 0) { // can be combine
          int area = areas[i] + areas[j];
          if (area > maxComb) {
            maxComb = area;
            maxWall =  walls[i][j];
          } else if (area == maxComb) {
            maxWall = Math.max(maxWall, walls[i][j]);
          }
        }
      }
    }
    return maxComb;
  }

  private void findWalls() {
    // (i, j, N/E) => 10^4 * i + 100 * j + 1/0
    walls = new int[currentComponent + 1][currentComponent + 1];
    for (int i = 0; i < m; i++) {
      for (int j = n - 1; j >= 0; j--) {
        int thisComp = component[i][j];
        if (i - 1 >= 0) {
          int neighborComp = component[i - 1][j];
          if (thisComp != neighborComp) {
            // i, j, N
            int wall = 10000 * (n - j - 1) +100 * (i + 1) +  1;
            walls[thisComp][neighborComp] = Math.max(walls[thisComp][neighborComp], wall);
            walls[neighborComp][thisComp] = Math.max(walls[neighborComp][thisComp], wall);
          }
        }
        if (j + 1 < n) {
          int neighborComp = component[i][j + 1];
          if (thisComp != neighborComp) {
            // i, j, E
            int wall =  10000 * (n - j - 1) + 100 * (i + 1) +0;
            walls[thisComp][neighborComp] = Math.max(walls[thisComp][neighborComp], wall);
            walls[neighborComp][thisComp] = Math.max(walls[neighborComp][thisComp], wall);
          }
        }
      }
    }
  }

  private int maxArea() {
    int res = 0;
    areas = new int[currentComponent + 1];

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        areas[component[i][j]]++;
      }
    }

    for (int i = 0; i < areas.length; i++) {
      res = Math.max(res, areas[i]);
    }

    return res;
  }

  private void init(int m, int n, int[][] map) {
    this.m = m;
    this.n = n;
    this.map = map;
    component = new int[m][n];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        component[i][j] = UNCHECK;
      }
    }
  }

  private void floodfill() {
    currentComponent = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (component[i][j] == UNCHECK) {
          component[i][j] = TO_VISIT;
          currentComponent++;
          fill(currentComponent);
        }
      }
    }
  }

  private void fill(int currentComponent) {
    int visited = 0;
    do {
      visited = 0;
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
          if (component[i][j] == TO_VISIT) {
            visited++;
            component[i][j] = currentComponent;
            // find neighbors
            if ((map[i][j] & 1) == 0) {
              if (component[i][j - 1] == UNCHECK) component[i][j - 1] = TO_VISIT;
            }
            if ((map[i][j] & 2) == 0) {
              if (component[i - 1][j] == UNCHECK) component[i - 1][j] = TO_VISIT;
            }
            if ((map[i][j] & 4) == 0) {
              if (component[i][j + 1] == UNCHECK) component[i][j + 1] = TO_VISIT;
            }
            if ((map[i][j] & 8) == 0) {
              if (component[i + 1][j] == UNCHECK) component[i + 1][j] = TO_VISIT;
            }
          }
        }
      }
    } while (visited > 0);
  }

  public static void main(String[] args) throws IOException {
    String problemName = "castle";
    BufferedReader f = new BufferedReader(new FileReader(problemName + ".in"));

    StringTokenizer st = new StringTokenizer(f.readLine());
    int m = Integer.parseInt(st.nextToken());
    int n = Integer.parseInt(st.nextToken());

    int[][] map = new int[n][m];

    for (int i = 0; i < n; i++) {
      st = new StringTokenizer(f.readLine());
      for (int j = 0; j < m; j++) {
        map[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    String[] res = (new castle()).solve(m, n, map);

    // output Span
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(problemName + ".out")));
    for (String r : res) {
      out.println(r);
    }
    out.close(); // close the output file
    System.exit(0); // don't omit this!
  }

}