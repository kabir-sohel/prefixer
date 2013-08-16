prefixer
========

infix notation to prefix notation conversion and reduce as much as possible

<<<<=============================================== Project Goals ===================================================>>>>

Given infix notation, convert it to its corresponding prefix notation

Example:
3 becomes 3
1 + 1 becomes (+ 1 1)
2 * 5 + 1 becomes (+ 1 (* 2 5))
2 * ( 5 + 1 ) becomes (* (+ 1 5) 2)
3 * x + ( 9 + y ) / 4 becomes (+ (* 3 x) (/ (+ 9 y) 4))

Input :

The format of the input expression is highly restricted. All values are either single alphabetic characters or positive integers. All operators, including ( and ), are always separated by at least one space from other values  or operators.

You should respect operator precedence, so 3 + 5 * 4 should always be parsed as 23, not 32.

Output:

Your program should be run from the command line as

prefixer FILE_NAME

where FILE_NAME is the name of a file containing an infix expression.

Final step: Reduce all expressions as much as possible before you output them. This behavior should be triggered by a -r flag.
