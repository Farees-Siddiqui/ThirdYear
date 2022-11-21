import java.io.Serializable;

public class Session implements Serializable{
  
  private static final long serialVersionUID = 1L;
  
  public String imageApath, imageBpath;
  
  public Rectangle regionA, regionB;

  public int seconds, participants = 0;
  
  public Session(String imageApath, String imageBpath, Rectangle regionA, Rectangle regionB, int seconds){
   this.imageApath = imageApath;
   this.imageBpath = imageBpath;
   this.regionA = regionA;
   this.regionB = regionB;
   this.seconds = seconds;
   //this.participants = participants;
  }
  
}
