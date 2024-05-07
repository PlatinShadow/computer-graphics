
_Lars Pfrenger, Laurin Bischof_


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
			- MVP Matrix application in Vertex Shader
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
- c)
	- **Application Stage**
	    - glUseProgram: Activates a shader program, which determines how vertex and fragment shaders process data.
	    - glUniform: Sets values of uniform variables in a shader program, influencing shader behavior across multiple invocations.
	    
	- **Geometry Stage**
	    - glEnableVertexAttribArray: Enables a vertex attribute array for use in vertex processing.
	    - glVertexAttribPointer: Specifies the format and source of vertex array data, setting up input for vertex shaders.
	    
	- **Rasterization Stage**
	    - glViewport: Defines the area of the framebuffer that the final image will be rendered into.
	    - glEnable(GL_CULL_FACE), glDisable(GL_CULL_FACE): Enables or disables face culling, controlling which faces (front or back) are rendered or discarded.
		
## Question 2
- a)
	- glDisable(GL_CULL_FACE) can be used to achieve this effect
	- Benefits: increased performane and less overdraw because faces that face away form the camera are not visible.
	- glFrontFace(GL_CCW) can be used to specify that the front sides of triangles have a counterclockwise winding

