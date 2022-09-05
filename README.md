# Automata-Theory
Coding assignments done for AT course at IIIT Hyderabad

## Programming Assignment-1

### Ans 1: 
The images are in the images directory of Q1. They have been further divided into 4 folders corresponding to part number. 1,2,4 have 1 image each while folder 3 has 5 images (as asked in the question).

The code is in the src directory. The code for each part has been further divided into directories named by part number (1,2,3,4). Each directory has the corresponding index.js and index.html file for that part.

### Ans 2:
- After 2 iterations,  there are 2 larger branches, and 4 very small branches. After 3 iterations. There are 2 very large, 4 small, and 8 very small branches. Therefore, after 1 iteration, there would have been only 2 small branches. Hence we have 2 bramch symbols in the production rules.  The length of the main shoot is twice that of the branches, hence the ‘F’ : ‘FF’ rule. All ‘F’ and ‘X’ are treated as a line segment. \

- The angle used is 75 degree to match the figure given in the document. Axiom is ‘-F’ to tilt the lsystem. The ‘-’ and ‘+’ in the production rules is used to form the star like shape. The ‘F’ is treated as a line segment for visualisation. 4 ‘F’s’ in the rule form 4 lines with 2 tilted at an angle (like a triangle). Multiple iterations give us the required shape. \


## Programming Assignment 2

### How to run

``` bash
g++ qx.cpp
./a.out <input file> <output file>
```
Here, `x` can be `{3, 4}`

## Question 3: Minimisation of DFA

- Removal of dead states
- Use the equivalence theorem and separate the states into final and non-final states
- This is followed by iteration and grouping of equivalent states and is done till the two consecutive partitions are identical
- These states obtained in the end represent the **states** of our **minimized DFA**
- **Letters** would be same as that of the input DFA
- Similarly, the **start states** and **end states** are also same as that of the input
- For the transition function, we can look at the following example to uderstand the process well
    - Say the `start_states` are something like `[0, 1, 2], [3,4], [5,6]` and let one of the transitions be `2 -a-> 6`. From this, we can get the new transition of the minimized DFA as `[0,1,2] -a-> [5,6]`
    - The above step is done for all the states to obtain the final transition matrix


## Question 4: Regex -> NFA

- Add the concatenation oprator `.` at the required places
- Convert the given expression to a **postfix** expression for easier processing -- Uses **Shunting Yard Algorithm**
- Use this postfix expression obtained to create NFA using **Thompson's Contruction**
- During this process, we keep on splitting the regex till each edge of our NFA represents only one character -- addition of these different edges is done in accordance with the operator (like union, concatenation etc.)
Footer
