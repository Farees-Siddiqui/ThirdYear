## <font style = "color:#005b6d">Goals</font>
- By the end of the lecture we will:
	- Know the key concepts in basic graphics
	- Understand the traditional graphics pipeline

## <font style = "color:#005b6d">Introduction</font>
- Introduce the graphics pipeline that is used on OpenGL and other packages
- This isn't the only way to do it, global illumination does it different but a good model for most of the course
- Introduce some of the concepts and terminology before we start OpenGL programming
## <font style = "color:#005b6d">What's the shape</font>
The below is a completely computer generated image, What are the shapes involved in rendering something like this bunny?

![[Pasted image 20230303014935.png]]

As we can see in the version below that the bunny shape is infact made up of lots of smaller triangles

![[Bunny_S1.png]]

## <font style = "color:#005b6d">Displays</font>
- We start with geometry, a collection of triangles
- We need some way of displaying them
- We need a display device!
- There are many technologies that we can use for display, will come back and examine some of them later
- For the time being, we will examine one, the LCD display, which is used in laptops and monitors

## <font style = "color:#005b6d">Liquid Crystal Displays</font>
- Liquid crystals are large molecules taht change their optical properties when an electric field is applied to them
- There are many types of liquid crystals that behave in different ways, display manufacturers have labs that investigate them, we wont look at the detail
- LCD displays are made up of many small cells containing liquid crystals
- LCD's dont have color, they are basically black and white (on or off)
- To get color we need to use a color filter, for each pixel we have three of them (Red, Green, Blue)
- **Fun note: Apple iphone screens are made by samsung**
- See below for a diagram of an LCD display
![[Pasted image 20230303015533.png]]
- Each cell or pixel is only capable of displaying a single color, so they can be viewed as small rectangles with a solid color
- We display an image by specifying the color of each pixel on the screen
- There are approx 1-2M pixels on the screen, so this is a lot of information to specify

## <font style = "color:#005b6d">Pixel Raster</font>
- When we have lots of tiny pixels, it looks like we have a continuous image and not blocky
- If we blow the image up however we can see them
![[Pasted image 20230303015949.png]]

## <font style = "color:#005b6d">Rasters</font>

- View the pixels as a 2D-array of cells, we need to provide a value for each of these cells
- The graphics card has a 2D array of memory, with one entry for each of these cells
- This is called a frambuffer
- The graphics card produces an electrical signal that transfers the pixels from the frame buffer to the display
- Several standards for this: VGA, HDMI, DVI, and Display Port

## <font style = "color:#005b6d">Liquid Crystal Display Resolution</font>
- Each LCD monitor has a native resolution, the actual number of pixels in the display
- This is the resolution that you should use, you can change the display resolution in the operating system, but this will produce a blurry or hard to read image since the display must attempt to approximate the new resolution
- This was not the case with older CRT monitors which could handle a range of resolutions

## <font style = "color:#005b6d">Representing Color</font>
- How do we represent color
- This si a hard problem that people are still working on, will come back to this later in the course
- Human vision is extremely complicated
- Our response to light intensity is not linear, it is logarithmic, this has an impact on display design
- Also, several different wavelengths can produce the same colors.
- We use an approximation to represent color, it is based on the red, green, blue, or RGB Color space
- A color is a triple (r, g, b) where r, g and b are either integers (usually from 0-255) or floating points (from 0-1)
- This triple gives the amount of red green and blue in the color


## <font style = "color:#005b6d">Display Gamut</font>
- The total color space is called a gamut
- Note that the RGB space doesnt include all the colors, and is a different color space that used with printers
- It turns out RGB is a close match to the colors produced by monitors so it is used in computer graphics
- We cannot use a primary based system to get all colors, unless we allow negative colors
![[Pasted image 20230303021148.png]]
## <font style = "color:#005b6d">Sending the pixels</font>
- Finally we need an organized way of getting the pixels onto the screen, the information that flows down the VGA/HDMI/DVI cable
- We use a scanning pattern for this and send the pixels sequentially. They are sent one at a time in an organized way
- We start with the pixel in the top left corner of the screen and send the first row of pixels one row at a time
- This is repeated row by row until the bottom of the screen is reached
- Once the bottom of the screen is reached, we go back to the top and start over
- This is similar to the pattern used in TV, but not quite the same
- At the end of each line and the end of each screen there is a small amount of time that isnt used, this is requried by CRT monitors to return the beam to the start of the line or top of the screen, called horizontal and vertical retrace

## <font style = "color:#005b6d">Refresh Rate</font>
- The number of times, per second, that we send the image to the screen is called the refresh rate
- This is at least 60Hz and is sometimes much higher
- This was very important for CRT monitors, but not as much of a concern for LCD's
- The graphics card will generate all of the signals requried to drive an LCD or CRT, so we dont need to worry about this

## <font style = "color:#005b6d">Rendering</font>
- Redering is the process of converting geometrical information, called the model, into the pixels in the framebuffer
- There are many rendering algorithms that have been developed 
- There are also many ways of classifying rendering algorithms
- One of the improtant ones is whether the algorithm is "real-time" 
- We will mainly be working with real time for this course
- For games and other interactive applications we want a real-time algorithm, must generate many FPS
- On the other hand if I'm producing special effects for a movie I do not really care how fast the rendering is
- I want the images to look good
- There is a trade-off between speed and quality, its very hard to get both
- OpenGL conentrates on speed and the expense of quality
- Global illumination is the other way around, examine it later in the course

## <font style = "color:#005b6d">Graphics Pipeline </font>
- Go from a geometrical model to pixels
- This is a complex process, so we will divide it into a number of steps
- These steps form the graphics pipeline
- Each step performs one part of the transformation, can concentrate on a particular type of computation
- Facilitates Implementation in hardware

## <font style = "color:#005b6d">Models</font>

- We need to have some representation inside the computer of the objects we are producing an image of, this is called a **model**
- Model is usually mathematical in nature, but in a digital form, something that we can store and manipulate on a computer
- There are many possible representations, we will study some of them in the course
- This is a very large topic, we will only touch a part of it
- Triangles are handy, we can use them to represent almost anything as long as we use enough of them
- Triangles are also quite simple, they are easy to manipulate and work with, we understand their mathematics
- The only problem is we quite often need a large number of them
- If an object is curved it can be very difficult to represent it by triangles, after all trianles are flat
- Not unusual to have models with millions of triangles
- This takes up a lot of memory and can be slow to manipulate
- Now that we have a model, whats next?

## <font style = "color:#005b6d">Graphics Pipeline</font>
- So we now have the two ends of the graphics pipeline:
	- Model - Triangles
	- Display - pixels
- Now we need to be able to convert the model into pixels, and we want to do this as efficiently as possible
- This is the purpose of a graphics pipeline
- The triangles are 3D and the image is 2D, this is the first problem we need to solve
- We need to **project** the 3D triangles onto the 2D screen space
- There are a number of projections that work in basically the same way
- We will be using a **perspective projection** since it gives the most realistic apprearance
- This is similar to the projection that our eyes use
- When we perform a perspective projection we need to know where we are projecting from, aka the eye location
- We also need to know the direction that we are looking
- The viewing transformation is made up of:
	- Projection, in our case perspective
	- Eye location
	- Viewing direction
	- Up direction
- In the case of a perspective projection this defines a **viewing frustum**, a pyramid with its apex at the viewer’s eye and its axis along the viewing direction
- All the triangles inside the viewing frustum will be visible on the screen, those outside will not

![[Pasted image 20230303023609.png]]

- We need to be careful to remove the triangles outside of the viewing frustum
- If we don’t they will appear on the screen in incorrect positions, basically they will confuse the algorithms and hardware
- The process of eliminating them is called clipping
- Note that some triangles may intersect the viewing frustum, in this case we just process the visible part of the triangle
<br>
- We need to have a **colour for our triangles**, otherwise nothing will appear on the screen
- But, mathematically triangles don’t have colour, they are just geometry
- We solve this problem by defining a **lighting model and material properties** for our objects
<br>
- In the real world we use lights to illuminate things, we do the same thing in graphics
- We give the lights a position and/or direction in space, and we can also assign a colour to them (more later)
- We also need to assign material properties to the triangles, how they interact with light, how much of the light gets reflected
<br>
- One of the most important properties that we need are normal vectors, they determine how light is reflected off of the triangle surfaces
- Since each triangle is flat its easy to compute a normal vector for it
- To compute the normal vector we just compute the cross product of 2 vectors in the triangle
- We then compute a normal vector for each vertex, by averaging the normal vectors of the triangles it appears in
- Thus for each vertex of a triangle we have its position and its normal vector
<br>
- Along with the material properties this allow us to compute the colour at each vertex
- We can then interpolate the vertex colours across the surface of the triangle to get a colour at every position
- This is called Gouraud shading


## <font style = "color:#005b6d">Local and Global Axes</font>
- Global: "World" Frame of reference
- Local: "Object" Frame of reference
![[Pasted image 20230303023815.png]]

## <font style = "color:#005b6d">Normal Vector</font>

![[Pasted image 20230303024110.png]]

## <font style = "color:#005b6d">Shading</font>
![[Pasted image 20230303024537.png]]
- We could compute the colour at each vertex and use Gouraud shading
- This is what OpenGL used to do, but it’s not the most realistic
- It is better to interpolate the normal vector than color over the surface of the polygon and then compute the colour at each pixel
- This is called Phong shading
- This is what we now do in OpenGL
<br>
- We now have the first few stages on the graphics pipeline
- For each triangle we need to do the following things:
	- Transform the vertices into global or world coordinates
	- Project the vertices
	- Clip the triangle to the viewing frustum
- Only the third operation needs all the triangle information, otherwise each vertex can be processed independently
<br>
- Note that all of these operations are geometrical in nature, they are independent of the pixels on the display
- Most of the operations just involve the triangle vertices
- We will write GPU programs for doing this processing, they are called vertex programs or vertex shaders
- This is viewed as the first stage in our pipeline
<br>
- We now have the projected triangle, all its vertices will lie on the display surface, now working in 2D
- But, the display surface is made up of pixels, we need to know which pixels to set for the triangle
- This is called filling, we set all of the pixels inside of the triangle’s outline
- There are efficient algorithms for this that are implemented in the GPU hardware
<br>
- As we fill each pixel we compute its colour from the interpolated normal vector, light position and material properties
- What have we overlooked?
	- We are projecting many triangles onto the same plane
	- In 3D space, some of these triangles are in front of other triangles, so they completely or partially hide the other triangles

- In the case of the bunny, we only see the triangles that are on the closest side, we don’t see the ones on the other side
- The surfaces of solid objects hide the other surfaces that are behind them
- If our image doesn’t have this property they won’t look very realistic
- This has been called the **hidden surface problem** and many algorithms have been developed for solving it
<br>
- Current graphics cards solve the hidden surface problem in hardware
- A common technique is based on a <font style="color:cyan">depth buffer or z buffer</font>, which is an addition to the frame buffer that holds the image
- The depth buffer is usually a 16 or 24 bit number that holds the current depth of the corresponding pixel. The size of this buffer is the same size as the image (i.e if the image is 1024x1024 so is the z-buffer)
- If a potential pixel is closer to viewer, draw it and update the depth buffer.
<br>
- When a vertex is projected onto the display screen, the screen coordinates are called the x and y coordinates of the vertex, they form the 2D coordinates of the vertex
- We can also produce a third coordinate, called the depth of the vertex, the distance from the viewer to the vertex
- This information is interpolated across the triangle in the same way as the vertex colour
<br>
- At the start of computing each image the z buffer is initialized to the largest possible value
- Before we set the value of a pixel we first check the z buffer
	- If pixel depth is less than the current contents of the z buffer, draw the pixel and update the z buffer
	- Otherwise the pixel isn’t drawn
- In other words, if the new pixel is closer to the viewer we draw it, otherwise we skip it
<br>
- We are performing a simple comparison that enables or blocks the writing of a pixel
- This is very efficient and more or less comes for free
- This is now the standard way of doing hidden surface removal
- At this point we have our image on the screen
<br>
- The second set of steps in our pipeline are:
	- Compute the pixels covered by the triangle
	- Compute the colour of the pixel
	- Interpolate the depth value of the pixel
	- Perform hidden surface using z buffer
- Note that all of the pixels in the triangle can be processed in parallel, since they don’t depend on each other
<br>
- Note that all of these operations involve pixels, we call them fragments
- The fragments contribute to the pixels on the display, in our case fragments and pixels are the same thing
- In more advanced applications, they are different
- We call this part of the pipeline fragment processing
- Again, we will write fragment programs that run on the GPU
<br>
- Note that we have divided the graphics pipeline into two parts:
	- The first part deals with geometrical information, the information associated with the triangle vertices
	- The second part deals with the individual pixels covered by the triangle
- This is a common division that we will see throughout the course
<br>
- The graphics pipeline is important for two reasons:
	- It provides an outline for most of the topics that will be covered in this course
	- It provides a model for graphics programming, which we explore in the next part of the course
<br>
