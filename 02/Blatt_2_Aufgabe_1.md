_Lars Pfrenger, Laurin Bischof_

## Question 1
- a)
	- GL_TRIANGLES:
		- Three vertices are connected to form a triangle. So for a VBO of \[V1, V2, V3, V4, V5, V6\] where V1-V6 are vertices, (V1, V2, V3) would be a triangle and (V4, V5, V6) would be a triangle.
	- GL_TRIANGLE_STRIP:
		- Connected triangles in a strip, sharing vertices. Vertice are shared between a triangle so that with 4 Vertices 2 Triangles can be built. Given the Vertices \[V0, V1, V2, V3\] the two triangles would be (V0, V1, V2) and (V2, V1, V3)
	- GL_TRIANGLE_FAN:
		- Connected triangles in a fan shape, sharing a central vertex
- b)
	- Using GL_TRIANGLE_FAN for 1.:
		- Vertex Buffer: \[p4, p1, p0, p0, p5, p5, p6, p6, p3, p3, p2, p2, p1]
        - 1 draw call: glDrawArrays(GL_TRIANGLE_FAN, 0, 13)
	- Using GL_TRIANGLE_STRIP for 2.:
		- Vertex Buffer: \[p3, p4, p6, p7, p5, p8, p0, p0, p1, p3, p4, p2, p5\]
        - 1 draw call glDrawArrays(GL_TRIANGLE_STRIP, 0, 12)
	- Using GL_TRIANGLE_STRIP for 3.:
		- Vertex Buffer: \[p4, p0, p5, p1, p7, p3, p6, p2, p4\] 
        - 1 draw call glDrawArrays(GL_TRAINGLE_STRUP, 0, 9)
	