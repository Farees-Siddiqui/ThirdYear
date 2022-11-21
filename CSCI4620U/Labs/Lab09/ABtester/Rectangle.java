
import java.io.Serializable;

public class Rectangle implements Serializable{
  
  private static final long serialVersionUID = 1L;
  
  int x, y, w, h;
  int hue = 0, s = 0, b = 0; // default color is black
 
  
  // constructor
  public Rectangle(int x, int y, int w, int h){
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  };
  
  public void setColor(int h, int s, int b){
    this.hue = h;
    this.s = s;
    this.b = b;
  };

  /* Check if a given point lies within this rectangle */
  public boolean isInside(int x, int y){
    int minX = this.w > 0 ? this.x : this.x + this.w,
        minY = this.h > 0 ? this.y : this.y + this.h,
        maxX = this.w > 0 ? this.x + this.w : this.x,
        maxY = this.h > 0 ? this.y + this.h : this.y;
    return x >= minX && x <= maxX 
        && y >= minY && y <= maxY;
  }
  
}