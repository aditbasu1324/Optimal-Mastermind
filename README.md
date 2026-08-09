The goal is to create a strategy to solve the game mastermind.

 ## How Mastermind works? 

Player 1 sets a code, Player 2 has to find the code. On each turn, player 2 guesses a code and player 1 gives player 2 a score to indicate how well they have done. The game ends either when player 2 guesses the correct code, or player 2 runs out of guesses (typically 10).

## Basic Mastermind Algorithm

The Basic mastermind code uses a min-max algorithm. 

First, store the scores generated between all pairs of codes in an NxN grid. 

At any turn, there are a finite number of codes available (candidate codes) that can be the solution. 
 
Then, find the worst case scenario for every code (A). For all candidate codes C, there is a precomputed score from the first step between code A and code C. Find the score that is given by the maximum number of codes for the chosen code A and note down the number of codes that give it. The goal is to pick the best code A (not necessarily a candidate code) that minimizes this number.

After the guess is made, a score is received from Player 1 and only codes that achieves this score from the candidate subset remain in the new candidates subset.

The game ends once there is only one candidate code remaining.

## Scaling Mastermind Algorithm

The previous mastermind algorithm requires the computation of all pairs of codes which is $O(N^{2})$. 

To resolve this issue, the algorithm uses random guessing instead of making optimal strategic guessing through the min-max algorithms. Once the number of candidate codes is sufficiently small (1000), the min-max algorithm is re-implemented as described above.

Currently, random guessing involves picking the code number 1000 (in the list of candidate codes). Then after receiving the score from Player 1, all the codes that achieve this score with code number 1000 are then selected as the new candidate codes. 

The above process is still O(N) so the code does take time to run for large N.



