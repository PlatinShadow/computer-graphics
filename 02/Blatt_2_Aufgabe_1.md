_Lars Pfrenger, Laurin Bischof_

## Question 1
- a)
	- GL_TRIANGLES:
		- Three independant vertices that are rendered in a group of 3 to form a triangle.
	- GL_TRIANGLE_STRIP:
		- Connected triangles in a strip, sharing vertices.
	- GL_TRIANGLE_FAN:
		- Connected triangles in a fan shape, sharing a central vertex
- b)
	- Using GL_TRIANGLE_FAN for 1.:
		- Vertex Buffer: \[p4, p0, p1, p2, p3, p6, p5, p0\]
	- Using GL_TRIANGLES for 2.:
		- Vertext Buffer: \[p0, p3, p1, p4, p2, p5, p3, p6, p4, p7, p5, p8\]
	- Using GL_TRIANGLE_STRIP for 3.:
		- Vertex Buffer: \[p4, p0, p5, p1, p7, p3, p6, p2, p4\] 
	