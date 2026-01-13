## **1\. Column space and Row space — what they live in**

- **Column space** = all linear combinations of **columns** of A.

  - Each column has m entries (since A is m×n ).
  - So column space is a subspace of **Rm**.

- **Row space** = all linear combinations of **rows** of A

  - Each row has n entries.
  - So row space is a subspace of **Rn**.

So indeed:

```text
Col(A)⊆Rm,
Row(A)⊆Rn.
Col(A)⊆Rm,
Row(A)⊆Rn.
```

Example:If A is 3×4 → columns are in R3 → column space is inside R3.Rows are in R4 → row space is inside R4.

## **2\. Basis for column space**

Method taught:

1.  Reduce A to RREF.
2.  Look at **pivot columns** in RREF.

3.  Take the **corresponding original columns** of A (not RREF columns!).

**Why?** Because RREF preserves linear dependence relations among columns but **not** the column space itself. The actual column vectors in RREF are usually different from A's columns but the pivot positions tell us which of A's columns form a basis for Col(A).

Why? Because RREF preserves linear dependence relations among columns but **not** the column space itself. The actual column vectors in RREF are usually different from A's columns but the pivot positions tell us which of A's columns form a basis for Col(A).

Example: take

$$A=\begin{bmatrix}1&2&3\\4&5&6\\7&8&9\end{bmatrix}.$$

One RREF is

$$\operatorname{RREF}(A)=\begin{bmatrix}1&0&-1\\0&1&2\\0&0&0\end{bmatrix},$$

so the pivot columns are 1 and 2. A basis for $\operatorname{Col}(A)$ is the first and second columns of the original $A$:

$$\left\{\begin{bmatrix}1\\4\\7\end{bmatrix},\ \begin{bmatrix}2\\5\\8\end{bmatrix}\right\} \subset \mathbb{R}^3.$$

## **3\. Possible confusion: dimensions**

- **Rank** = dimension of column space = dimension of row space.
- So even though column space is in Rm and row space in Rn, they have the **same dimension** r.
- r≤m and r≤n.

## **4\. What’s the “issue”**

You might be thinking:If column space is in Rm, why when we write basis vectors they have m components, but when we do problems sometimes we seem to mix up m and n?

That confusion often comes from solving Ax=b where:

- **x** is in Rn (since n columns → n variables).
- **b** is in Rm (since m rows).
- The **nullspace** of A is in Rn (solutions to Ax=0  have n components).

But **column space**  we find it from columns of A, yes, those are m vectors.

Maybe you’re mixing column space with nullspace in some problems? Let’s check:

- To find **basis for column space**: use original A's pivot columns → vectors with m entries.
- To find **basis for nullspace**: solve Ax=0  → special solutions → vectors with n entries.

## **5\. Concrete example to connect**

Let A be 3×5 (m=3,n=5).

- **Basis for Col(A)**: Pivot columns from A → each basis vector has 3 components → lives in R3.
- **Basis for Row(A)**: Nonzero rows of RREF (each has 5 components) → lives in R5.
- **Basis for Null(A)**: Solve Ax=0 → each special solution has 5 components → lives in R5.

So:

```text
Col(A)⊂R3,Row(A)⊂R5,Null(A)⊂R5.
```

Dimension check:dim(Col) = r, dim(Null) = 5-r, dim(Row) = r. Works fine.
