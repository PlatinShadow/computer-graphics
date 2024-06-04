### ### Question 1

#### (a)

- $R$ rotates $P_1P_2$ to be parallel to the z-axis.
- $R$rotates $P_1P_3$ to lie in the yz-plane.

#### (b)

1. **Translate $P_1$ to Origin:**
 $$
 T_1 = \begin{pmatrix}
 1 & 0 & 0 & -P_{1x} \\
 0 & 1 & 0 & -P_{1y} \\
 0 & 0 & 1 & -P_{1z} \\
 0 & 0 & 0 & 1
 \end{pmatrix}
 $$

2. **Rotate $P_3$ to lie on Positive y-axis:**
   - **Rotation Axis:** Arbitrary axis in xy-plane
 $$
 R_1 = \begin{pmatrix}
 \cos \theta & -\sin \theta & 0 & 0 \\
 \sin \theta & \cos \theta & 0 & 0 \\
 0 & 0 & 1 & 0 \\
 0 & 0 & 0 & 1
 \end{pmatrix}
 $$

3. **Rotate $P_2$ to lie in the xy-plane:**
$$
 R_2 = \begin{pmatrix}
 1 & 0 & 0 & 0 \\
 0 & \cos \phi & -\sin \phi & 0 \\
 0 & \sin \phi & \cos \phi & 0 \\
 0 & 0 & 0 & 1
 \end{pmatrix}
 $$
#### (c)

- **Transformation Matrix:**
  $$
  T = T_1 \times R_1 \times R_2
  $$
  where:
  - $T_1$ translates $P_1$ to the origin.
  - $R_1$ rotates $P_3$ to the y-axis.
  - $R_2$ rotates $P_2$ to the xy-plane.

#### (d)

- **Axis of Rotation:** Main diagonal from $(0,0,0)$ to $(1,1,1)$
- **Angle of Rotation:** $\theta$ degrees

  $$
  T_{\text{rotation}} = \begin{pmatrix}
  \cos \theta + (1 - \cos \theta)/3 & 1/3(1 - \cos \theta - \sqrt{3}\sin \theta) & 1/3(1 - \cos \theta + \sqrt{3}\sin \theta) & 0 \\
  1/3(1 - \cos \theta + \sqrt{3}\sin \theta) & \cos \theta + (1 - \cos \theta)/3 & 1/3(1 - \cos \theta - \sqrt{3}\sin \theta) & 0 \\
  1/3(1 - \cos \theta - \sqrt{3}\sin \ theta) & 1/3(1 - \cos \theta + \sqrt{3}\sin \theta) & \cos \theta + (1 - \cos \theta)/3 & 0 \\
  0 & 0 & 0 & 1
  \end{pmatrix}
  $$
