import processing.serial.*;
import java.util.concurrent.CopyOnWriteArrayList;

Serial myPort;
int angle, distance;
CopyOnWriteArrayList<PVector> objectPositions;


void setup() {
  size(1200, 700);
  smooth();

  // Set up serial communication
  String portName = Serial.list()[0]; // Select the first available port
  myPort = new Serial(this, portName, 9600);

  // Initialize the ArrayList to store object positions
  objectPositions = new CopyOnWriteArrayList<PVector>();
}

void draw() {
  background(0); // Set the background color to black

  // Draw the radar and objects based on received angle and distance
  drawRadar();
  drawObject();
  drawLine();
  drawText();
  drawObjectPositions();
}



void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data!= null) {
    String[] values = split(data, ',');
    if (values.length == 2) {
      angle = int(values[0]);
      distance = int(values[1]);

      // Add the new object position to the ArrayList
      objectPositions.add(new PVector(width / 2 + (distance * cos(radians(angle)) * (width - width * 0.505) / 40), height - height * 0.1666 - (distance * sin(radians(angle)) * (height - height * 0.1666) / 40)));

      // Limit the ArrayList size to 100 positions
      if (objectPositions.size() > 100) {
        objectPositions.remove(0);
      }
    }
  }
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);

  // Draw the arc lines
  arc(0, 0, width - width * 0.0625, width - width * 0.0625, PI, TWO_PI);
  arc(0, 0, width - width * 0.27, width - width * 0.27, PI, TWO_PI);
  arc(0, 0, width - width * 0.479, width - width * 0.479, PI, TWO_PI);
  arc(0, 0, width - width * 0.687, width - width * 0.687, PI, TWO_PI);

  // Draw the angle lines
  line(-width / 2, 0, width / 2, 0);
  line(0, 0, (-width / 2) * cos(radians(30)), (-width / 2) * sin(radians(30)));
  line(0, 0, (-width / 2) * cos(radians(60)), (-width / 2) * sin(radians(60)));
  line(0, 0, (-width / 2) * cos(radians(90)), (-width / 2) * sin(radians(90)));
    line(0, 0, (-width / 2) * cos(radians(120)), (-width / 2) * sin(radians(120)));
  line(0, 0, (-width / 2) * cos(radians(150)), (-width / 2) * sin(radians(150)));
  line((-width / 2) * cos(radians(30)), 0, width / 2, 0);

  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  strokeWeight(9);
  stroke(255, 10, 10);

  if (distance < 40) {
    fill(255, 10, 10); // Set the object color to red when detected
    float pixsDistance = distance * ((height - height * 0.1666) * 0.025);
    line(pixsDistance * cos(radians(angle)), -pixsDistance * sin(radians(angle)), (width - width * 0.505) * cos(radians(angle)), -(width - width * 0.505) * sin(radians(angle)));
  }

  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(width / 2, height - height * 0.074);
  line(0, 0, (height - height * 0.12) * cos(radians(angle)), -(height - height * 0.12) * sin(radians(angle)));
  popMatrix();
}

void drawText(){
  pushMatrix();
  textAlign(CENTER, CENTER);
  textSize(25);
  fill(98, 245, 31);
  text("10cm", width - width * 0.3854, height - height * 0.0833);
  text("20cm", width - width * 0.281, height - height * 0.0833);
  text("30cm", width - width * 0.177, height - height * 0.0833);
  text("40cm", width - width * 0.0729, height - height * 0.0833);
  textSize(40);
  text(" Sonar Project", width - width * 0.875, height - height * 0.0277);
  text("Angle: " + angle + "°",width - width * 0.48, height - height * 0.0277);
  text(" ", width - width * 0.26, height - height * 0.0277);
  if (distance < 40) {
    text("        " + distance + " cm", width - width * 0.225, height - height * 0.0277);
  }

  popMatrix();
}

void drawObjectPositions() {
  fill(255, 10, 10);
  for (PVector pos : objectPositions) {
    ellipse(pos.x, pos.y, 5, 5);
  }
}
