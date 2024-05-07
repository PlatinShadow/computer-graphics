
_Lars Pfrenger, Laurin Bischop_


## Question 1
- a)
	- **Application Stage**
		- In this stage the Client/Application code is executed. This means in this stage all of the application specific calculations are done like setting up the scene, calculating animations, detecting collisions, culling invisible objects, calculating inverse kinematics etc. This stage also calls the rendering API (like OpenGL) to submit work to the rendering pipeline / next stage.
	- **Geometry Stage**
		- In this Stage objects/meshes are translated into the World Frame by applying their Model Matrix. 
		- The single vertices are assembled to primitives (most commonly triangles), and additional triangles can be generated on the fly in the tessellation step.
		- Then the primitives are transformed into the Camera Frame by applying the View Matrix and finally are projected into the Clip Space using the Projection Matrix 
		- Additionally points outside the Clip Space (range -1.0 to 1.0) are thrown away to save computation 
		- In OpenGL this stage is defined by fixed and custom Shaders in the pipeline
			- MVP  Matrix application in Vertex Shader
			- Additional Primitives in Tesselation or Geometry Shader
	- **Rasterization Stage**
		- In this stage the primitives are rasterized into fragments which can then be written to a framebuffer
		- After rasterization per fragement tests can be performed
			- Like depth test, transperency or stencil/masking test
		- Fragments can also be blended with other fragments in this step
- b)
	- The Geometry Stage turns vertices into primitives which can then be rasterized by the Rasterization Stage
		- Vertices are transformed into World Frame. This is used to compose the entire scene out of many objects and instances of objects. Here objects can be translated, scaled, and rotated
		- Vertices are transformed into the View Frame so that the scene is viewed from the camera
		- Vertices are projected into the Clip Space, in order to transform 3D points into 2D points that can be mapped to the actual Display 
		- Additional vertices can be added using Tesselation or Geometry Shaders
		- Primites are assembled from the vertices
		- Points out of the clipping space are thrown away to save computation
		



---
[[Interaktive Computergraphik]]
