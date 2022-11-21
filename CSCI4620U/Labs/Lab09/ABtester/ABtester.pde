import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import com.esotericsoftware.minlog.*;
import java.io.FileOutputStream;
import java.io.FileInputStream;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.util.Arrays;
import java.util.List;
import java.util.Collections;
import java.util.LinkedHashMap;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

static int MODE_A = 0, MODE_B = 1;
static boolean showBox = false;

int mode = MODE_A;
int clickX, clickY;

// Saves image names and button coordinates
LinkedHashMap<String, int[]> imagesAndCoordinates = new LinkedHashMap<String, int[]>();

Rectangle region;
String imageName;
String imagePath;
PImage image;

List randomKeys; // Contains shuffled keys

boolean testing = false;

PFont coverFont;

long sMoment = 0,
  interval= 5000;

FileWriter outputWriter;
SimpleDateFormat dateFormatter;

float resizeFactor = 1.0;

void setup() {
  fullScreen();
  pixelDensity(displayDensity());
  createUserFolder();
  coverFont = createFont("Arial", 36, true);

  storeImagesAndCoordinates();

  drawCoverScreen();

  try {
    outputWriter = new FileWriter(getResultFile(), true);
  }
  catch(Exception e) {
    e.printStackTrace();
  }
}

void draw() {
  if (testing) {
    // If we've been waiting for more than 5 seconds, declare this trial a failure and move on.
    // Also set the saved click coordinates to 0, so that we're not carrying over old values (rescaled by resizeFactor).
    if (millis() - sMoment >= interval) {
      clickX = 0;
      clickY = 0;
      writeResult(mode, false, interval);
      finishTrial();
    };
  }
}

void storeImagesAndCoordinates() {
  String line = "";

  // Store csv data in hashmap
  try {
    BufferedReader br = new BufferedReader(new FileReader(sketchPath("")+"/coordinates.csv"));

    while ((line = br.readLine()) != null) {
      String[] data = line.split(",");

      // If required amount data is present
      if (data.length == 5) {
        // Append images and coordinates
        imagesAndCoordinates.put(
          // Add image
          data[0],
          // Add coordinates
          new int[] {
          Integer.parseInt(data[1].replaceAll("[^0-9]", "")),
          Integer.parseInt(data[2].replaceAll("[^0-9]", "")),
          Integer.parseInt(data[3].replaceAll("[^0-9]", "")),
          Integer.parseInt(data[4].replaceAll("[^0-9]", ""))
          }
          );
      }
    }
  }
  catch (IOException e) {
    e.printStackTrace();
  }

  // RANDOMIZE ORDER
  randomKeys = new ArrayList(imagesAndCoordinates.keySet()); // Copy the keys into a List
  Collections.shuffle(randomKeys); // Shuffle keys for a random order
}

void finishTrial() {
  drawCoverScreen();
  testing = false;
}

void drawCoverScreen() {
  background(200);
  textFont(coverFont);
  textAlign(CENTER, CENTER);
  fill(0);

  if (randomKeys.isEmpty()) {
    try {
      outputWriter.close();
    }
    catch (IOException e) {
      e.printStackTrace();
    }
    text("Done - Please upload your results", width/2, height/2);
  } else {
    // Get first key and value from the map
    imageName = randomKeys.get(0).toString();
    char scenarioNum = imageName.charAt(10);
    String instructions = new String();
    switch(scenarioNum) {
    case '1':
      instructions = "You are on the Canada Post website to track your package. \n You are ready to enter the tracking number. \n\n Click where you would to start typing in the \n tracking information. \n\n";
      break;
    case '2':
      instructions = "You are trying to find a specific book at \n the library and need help.\n\n Click to open a chat with the librarian. \n\n";
      break;
    case '3':
      instructions = "You are visiting to find a specific \n product.\n\n Click the region you would use to search for your item of interest. \n\n";
      break;
    case '4':
      instructions = "You would like to help the Apache \n Software Foundation.\n\n Click where you think you should to donate money. \n\n";
      break;
    case '5':
      instructions = "Imagine you want to upload a video \n into the Internet Archive.\n\n Click the appropriate location to start the process. \n\n";
      break;
    case '6':
      instructions = "You want to know when the mall \n will be open.\n\n Click the place to read today's hours. \n\n";
      break;
    case '7':
      instructions = "You want to subscribe to recieve member deals on hotel bookings. \n\n Click the region for signup. \n\n";
      break;
    }
    text(instructions + "Press Enter to Start", width/2, height/2);
  }
}

void keyPressed() {
  if (testing) return;

  if (key != ENTER) return;

  if (randomKeys.isEmpty()) return;

  // Get value from the map
  int[] value = imagesAndCoordinates.get(randomKeys.get(0));

  if (imageName.charAt(12) == 'a') {
    mode = MODE_A;
  } else if (imageName.charAt(12) == 'b') {
    mode = MODE_B;
  }

  imagePath = sketchPath("")+"data\\"+imageName;
  image = getImage(imagePath);

  if (image == null) {
    // Because we normalize the file path, this should (hopefully) only happen if a student messes up.
    // Write out an error message and go to the next trial.
    System.out.println("ERROR: The image at " + imagePath + " could not be read.");
    randomKeys.remove(0); // Remove the current bad file path.
    finishTrial();
    return;
  }


  // Update global variables with current ABtest
  int x1 = Math.round(value[0] * resizeFactor);
  int y1 = Math.round(value[1] * resizeFactor);
  int x2 = Math.round(value[2] * resizeFactor);
  int y2 = Math.round(value[3] * resizeFactor);

  // Processing coordinates start at 0.
  x1 = Math.max(x1, 0);
  y1 = Math.max(y1, 0);
  x2 = Math.max(x2, 0);
  y2 = Math.max(y2, 0);

  if (x1 > x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }
  if (y1 > y2) {
    int temp = y1;
    y1 = y2;
    y2 = temp;
  }
  region = new Rectangle(x1, y1, (x2-x1), (y2-y1));

  // Print to see randomness
  System.out.println("[" + region.x + " " + region.y + " " + region.w + " " + region.h + "]" + " " + mode + " " + imagePath);

  background(200);
  image(image, 0, 0);
  if (showBox) rect(region.x, region.y, region.w, region.h);
  testing = true;
  sMoment = millis();

  randomKeys.remove(0); // Remove first key
}

void mousePressed() {
  if (!testing) return;

  clickX = mouseX;
  clickY = mouseY;

  if (mode == MODE_A && region.isInside(mouseX, mouseY) ||
    mode == MODE_B && region.isInside(mouseX, mouseY) ) {
    writeResult(mode, true, millis()-sMoment);
    finishTrial();
  } else {
    writeResult(mode, false, millis()-sMoment);
    finishTrial();
  }
}

void writeResult(int mode, boolean success, long time) {
  String row = String.format("%s,%s,%d,%d,%d\n", imageName, success, (int) Math.round(clickX/resizeFactor), (int) Math.round(clickY/resizeFactor), time  );
  System.out.println(row);

  try {
    outputWriter.write(row);
    outputWriter.flush();
  }
  catch(Exception e) {
    e.printStackTrace();
  }
}

File getResultFile() {
  //String path = getHomeFolderPath() + File.separator + "results.csv";
  String path = sketchPath("") + File.separator + "results.csv"; // Better path
  File f = new File(path);
  return f;
}

String getHomeFolderPath() {
  return System.getProperty("user.home") + File.separator + "ABtester";
}

void createUserFolder() {
  File homeDir = new File(getHomeFolderPath());
  if (!homeDir.exists())
    homeDir.mkdirs();
}

void resizeImage(PImage im) {
  // resize the image to fit screen

  float heightFactor = (height) / (float) im.height;
  float widthFactor = (width) / (float) im.width;
  resizeFactor = (heightFactor < widthFactor) ? heightFactor : widthFactor;

  int newWidth, newHeight;
  newWidth = Math.round(im.width * resizeFactor);
  newHeight = Math.round(im.height * resizeFactor);

  im.resize(newWidth, newHeight);
}

PImage getImage(String path) {
  path = getActualImagePath(path);

  if (path == null) {
    return null;
  }

  PImage im = loadImage(path);
  resizeFactor = 1.0;
  resizeImage(im);
  return im;
}

String getActualImagePath(String path) {
  // Normalize the file path. Note that processing / Java will also fail even on non-case sensitive OSs.
  // See https://forum.processing.org/one/topic/this-file-is-named-x-jpg-not-x-jpg-rename-the-file-or-change-your-code.html for more details.
  // Returns null if no image could be found at this path.

  String filenameActual = path;

  try {
    File file = new File(path);
    if (!file.exists()) {
      return null;
    }

    String canonicalFilePath = file.getCanonicalPath();
    filenameActual = new File(canonicalFilePath).getName();
  }
  catch (IOException e) {
    e.printStackTrace();
  }

  return filenameActual;
}


/*void loadSession(){
 
 
 try {
 
 String path = getHomeFolderPath() + File.separator + "session.bin";
 Input input = new Input(new FileInputStream(path));
 Session session = (Session)kryo.readClassAndObject(input);
 input.close();
 
 imageApath = session.imageApath;
 imageBpath = session.imageBpath;
 imageA = getImage(imageApath);
 imageB = getImage(imageBpath);
 regionA = session.regionA;
 regionB = session.regionB;
 
 interval = session.seconds * 1000;
 
 currentRegion = regionA;
 
 } catch (Exception e){
 e.printStackTrace();
 }  catch(Error e){
 e.printStackTrace();
 }
 }*/
