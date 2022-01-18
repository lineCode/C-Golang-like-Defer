# C-Golang-like-Defer
Cursed `defer()` method in C++ achieves similar results as Go's defer keyword.

Unlike `defer` in Go programming, which does partial evaluations in the expression, this C++ implementation evaluates only at time of scope cleanup.

I wouldn't recommend using this in serious projects since it captures everything in scope by reference. The saftey is concerning too. This is simply a toy.

# Run in your browser:
https://godbolt.org/z/nKx4hMG79
