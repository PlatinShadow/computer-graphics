### Question 1

#### a)
The Projection matrix can be derived from the pinhole camera model. Although the pinhole model assumes that the frustrum is a box. As the view frustrum for an opengl projection is a "squished" box, the parameters of the matrix have to be adjusted to take this into account. At the end the NDC Coordinates have to be divided by the w component of the 4D Vector to perform the perspective divided by the w component of the 4D Vector, to perform the perspective divide. 
Thus the last row of the matrix equals $[0,0,-1,0]$.

#### b)
$$
P^{-1} = \begin{pmatrix}
\frac{\text{right} - \text{left}}{2 \cdot \text{near}} & 0 & 0 & \frac{\text{right} + \text{left}}{2 \cdot \text{near}} \\
0 & \frac{\text{top} - \text{bottom}}{2 \cdot \text{near}} & 0 & \frac{\text{top} + \text{bottom}}{2 \cdot \text{near}} \\
0 & 0 & 0 & -1 \\
0 & 0 & \frac{\text{far} - \text{near}}{2 \cdot \text{far} \cdot \text{near}} & \frac{\text{far} + \text{near}}{2 \cdot \text{far} \cdot \text{near}}
\end{pmatrix}
$$

#### c)
##### Direction Vector:


$\begin{pmatrix} 0 \\ 0 \\ -3 \\ -1 \end{pmatrix} \rightarrow \begin{pmatrix} 0 \\ 0 \\ 3 \end{pmatrix} \quad (\text{after normalization})$

##### Upward Vector:

$\begin{pmatrix} 0 \\ 1 \\ 0 \end{pmatrix}$

##### Near and Far Clipping Planes:

- 3./4. row of $M$:

	$\begin{pmatrix} 0 & 0 & -3 & -1 \end{pmatrix}$


- General form of $P$:

	$\begin{pmatrix}0 & 0 & -\frac{(\text{far} + \text{near})}{\text{far} - \text{near}} & -\frac{2 \cdot \text{far}\cdot \text{near}}{\text{far} - \text{near}}\end{pmatrix}$


- compare:

	$-\frac{(\text{far} + \text{near})}{\text{far} - \text{near}} = -3 \quad \text{and} \quad -\frac{2 \cdot \text{far} \cdot \text{near}}{\text{far} - \text{near}} = -1$

- Solving these equations:

	$\text{far} + \text{near} = 3 \cdot (\text{far} - \text{near})$

	$\text{far} + \text{near} = 3 \cdot \text{far} - 3 \cdot \text{near}$

	$4 \cdot \text{near} = 2 \cdot \text{far}$

	$2 \cdot \text{near} = \text{far}$

- Using:

	$-\frac{2 \cdot \text{far} \cdot \text{near}}{\text{far} - \text{near}} = -1$:

	$\frac{2 \cdot \text{far} \cdot \text{near}}{\text{far} - \text{near}} = 1$

	$\frac{2 \cdot \text{near} \cdot 2 \cdot \text{near}}{2 \cdot \text{near} - \text{near}} = 1$

	$\frac{4 \cdot \text{near}^2}{\text{near}} = 1$

	$4 \cdot \text{near} = 1$

	$\text{near} = \frac{1}{4}$

	$\text{far} = \frac{1}{2}$

##### Aspect Ratio and Field of View:

- Vertical FOV:

	$\frac{2 \cdot \text{near}}{\text{top} - \text{bottom}} = 1 \rightarrow \text{top} - \text{bottom} = 2 \cdot \text{near} = \frac{1}{2}$

- Horizontal field of view angle:

	$\frac{2 \cdot \text{near}}{\text{right} - \text{left}} = 1 \rightarrow \text{right} - \text{left} = 2 \cdot \text{near} = \frac{1}{2}$

- Aspect Ratio:

	$\frac{\text{right} - \text{left}}{\text{top} - \text{bottom}} = \frac{\frac{1}{2}}{\frac{1}{2}} = 1$
