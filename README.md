# Solver for SLE over finite field
We work only with finite fields with prime orders $\mathcal{F}_p$.
This kind of SLE probably look like this:

$$ A \vec{x} = \vec{b} $$,

where
$ 
A = 
\begin{pmatrix}
  a_{1,1} & a_{1,2} & \cdots & a_{1,n} \\
  a_{2,1} & a_{2,2} & \cdots & a_{2,n} \\
  \vdots  & \vdots  & \ddots & \vdots  \\
  a_{n,1} & a_{n,2} & \cdots & a_{n,n} 
\end{pmatrix} $ - matrix with size of $ n \times n$,

$ a_{i, j}, x_i, b_i \in \mathcal{F}_p. $

## Gauss' method of solving

This program is standart implementation of Gauss' method with respect to the fact that every coefficient lies inside $ \mathcal{F}_p $.

## Usage

```
git clone https://github.com/HatefulT/gauss-over-finite-field.git
make run
```
