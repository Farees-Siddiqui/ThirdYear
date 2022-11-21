Timer timer = new Timer();
Rectangle boxR, boxL;
int[] testCaseD = {250, 250, 250, 500, 500, 500, 1000, 1000, 1000};
int[] testCaseW = {15, 30, 45, 15, 30, 45, 15, 30, 45};
int index = 0;
int r=5, g=150, b=5;
boolean isLeft = false;

int trials = 6;
int testCases = 9;
double[] avgTimes = new double[testCases];
int[] times = new int[trials];
int leftClicks = 0;
int rightClicks = 0;


void settings() {
  size(1200, 800);
}

void setup() {
  // Called only once at startup; used for initialization
  // Initialize the objects
  boxL = new Rectangle((1200-testCaseD[index])/2, 50, testCaseW[index], 500);
  boxR = new Rectangle((1200+testCaseD[index])/2, 50, testCaseW[index], 500);
  boxR.setColor(r, g, b);
  boxL.setColor(255-r, 255-g, 255-b);
}

void draw() {
  // Automatically called every few seconds
  // Render the rectangles
  background(155);
  boxR.render();
  boxL.render();
}

void swap() {
  isLeft = !isLeft;
  if (isLeft) {
    boxL.setColor(r, g, b);
    boxR.setColor(255-r, 255-g, 255-b);
  } else {
    boxR.setColor(r, g, b);
    boxL.setColor(255-r, 255-g, 255-b);
  }
}

double getAvgTime() {
  int tot = 0;
  for (int i = 0; i < times.length; i++){
    tot += times[i];
  }
  
  return tot/trials;
}

void returnTimes() {
  for (int i = 0; i < avgTimes.length; i++) {
    println(avgTimes[i]);
    
  }
  System.exit(0);
}

void mousePressed() {
  // This method is called whenever a mouse press occurs.
  // Use the global variables mouseX and mouseY to get current mouse coordinates.
  // Handle checks for clicks on rectangles, alternating the target rectangle
  // the timer start/pause/reset, and the results output here.

  /* YOUR CODE HERE */



  if (index < testCases) {

    if (timer.paused) {
      timer.start();
    }

    if (!boxL.isInside(mouseX, mouseY) && !boxR.isInside(mouseX, mouseY)) {
      swap();
      timer.reset();
      timer.start();
    }

    if (isLeft && boxL.isInside(mouseX, mouseY)) {
      swap();
      if (leftClicks < 3) {
        times[leftClicks++ + rightClicks] = timer.getTime();
        timer.reset();
        timer.start();
      }
    } else if (!isLeft && boxR.isInside(mouseX, mouseY)) {
      swap();
      if (rightClicks < 3) {
        times[leftClicks + rightClicks++] = timer.getTime();
        timer.reset();
        timer.start();
      }
    }

    if (leftClicks == 3 && rightClicks == 3) {
      avgTimes[index] = getAvgTime();
      index++;
      if (index >= testCases) {
        returnTimes();
      }
      leftClicks = 0;
      rightClicks = 0;
      boxL = new Rectangle((1200-testCaseD[index])/2, 50, testCaseW[index], 500);
      boxR = new Rectangle((1200+testCaseD[index])/2, 50, testCaseW[index], 500);
      if (isLeft) {
        boxL.setColor(r, g, b);
        boxR.setColor(255-r, 255-g, 255-b);
      } else {
        boxR.setColor(r, g, b);
        boxL.setColor(255-r, 255-g, 255-b);
      }
    }
  }
}


/***** CODE BELOW HERE IS UTILITY FOR YOU TO USE, NO NEED TO CHANGE. *******/

/*
Simple class to record elapsed time.
 Usage:
 Timer timer = new Timer();
 timer.start();   // start counting time from 0
 timer.pause();   // pause
 timer.start();   // continue counting from when it was paused
 timer.pause();   // pause again
 timer.getTime(); // get accumulated time in miliseconds
 timer.reset();   // make it ready for a new run
 */
class Timer {

  int accTime   = 0,
    lastStart = 0;

  boolean paused = true;

  public void start() {
    this.lastStart = millis();
    this.paused    = false;
  }

  public void pause() {
    this.accTime += millis() - lastStart;
    paused = true;
  }

  public int getTime() {
    return paused ? accTime : accTime + (millis() - lastStart);
  }

  public void reset() {
    this.accTime   = 0;
    this.lastStart = 0;
    this.paused    = true;
  }

  public boolean isPaused() {
    return this.paused;
  };
}


class Rectangle {
  int x, y, w, h;
  int r = 0, g = 0, b = 0; // default color is black

  // constructor
  public Rectangle(int x, int y, int w, int h) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  };

  public void setColor(int r, int g, int b) {
    this.r = r;
    this.g = g;
    this.b = b;
  };

  /* Draws the rectangle */
  public void render() {
    fill(this.r, this.g, this.b);
    rect(x, y, w, h);
  }

  /* Check if a given point lies within this rectangle */
  public boolean isInside(int x, int y) {
    x = x - this.x;
    y = y - this.y;
    return x >= 0 && x <= this.w && y >= 0 && y <= this.h;
  }
}
