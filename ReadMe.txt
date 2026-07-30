This is a program to solve Challenger puzzles.  A Challenger puzzle has 
4 rows and 4 columns with the totals for each, row, column, and diagonal
given.  There must be at least 4 numbers in the 4x4 matrix which I call cells
with one in each row and column.  There may be more than one 
solution to the puzzle. I exclude puzzles that have all four given cells
on one diagonal because that seem to be the practice in the newspapers where
I often find these puzzles.  However, that will not effect any of the algorithms 
discussed below. I have read that this puzzle was created my Linus Maurer a puzzle 
enthusiast and art classmate of Peanuts creator Charles M. Schulz.  Schulz named
Linus in his Peanuts cartoon strip after his friend Linus Maurer.

Here is a sample puzzle:
                | 17
     -  7  -  - | 20
     -  -  7  - | 21
     4  -  -  - | 23
     -  -  -  6 | 24
    ------------+
    23 18 27 20   28

For most puzzles there will be many solutions so we will need to guess.  
The idea is to prove that we can eliminate all incorrect guesses.  Because
puzzles start with 10 equations and 12 unknowns, the question is can we use
the equations to eliminate all incorrect guesses.  The answer is yes we can
eliminate guesses in about 75% of the puzzles using this method.

The above process is quite time and paper intensive which often leads to errors 
so the next question is there an easier way to solve the puzzles by guessing in 
some intelligent way to reduce the time and any possible errors to get to a 
solution quickly. The answer to this questions is definitely yes.  You can use 
minimal guessing that solves any puzzle about 85% of the time.

So to start a new puzzle you must enter the totals and at least 4 numbers
in the 4x4 matrix before you can proceed. Or the program can have this program
create a puzzle for you.

The first step for the program is the same as any human would use and is 
necessary for any method to solve the puzzle.  We need to create a range of 
values that are legal for every cell.  So for every row, column and diagonal 
determine the min and max values for each cell. For example, suppose a row 
totals 15 and there is a 6 in the row.  The other cells can
add up to 9 so the max a cell can be is 7 (7+1+1+6=15) so the range is 1-7.
If the min and max are the same, the cell must be exactly that value.   
If a cell changes range, all rows, columns, and diagonals that use that cell 
must be checked again.  Once all directions are stable the program will see how 
many solutions there are.  The program has the ability to the above process one
step at a time so you can see what changes or do this repeatedly until completion.
Here is a sample final result:
                    | 17
    7-9  7  2-5 1-4 | 20
    4-7 4-6  7  1-6 | 21
     4  1-3 8-9 7-9 | 23
    5-8 3-4 6-9  6  | 24
    ----------------+
    23  18  27  20    28

All solutions are written to a file named solutions.txt.  In addition the 
solutions.txt file will contain the valid ranges for each cell.

In general most puzzles will have 10 linear equations (one for each direction) 
with 12 unknowns (one for each of the 12 unknown cells). So if we start 
assigning variables to the cells, we will find that we will get into a situation
where a direction will have an equation that looks like 22 = 7 + d + 13-a-b +
-2+a-b+2c-d or 4 = 2c-2b or c = 2+b which we can use to substitute throughout
the equations.  Once we have filled out all the cells with equations there are
many methods we can use to reduce the ranges for the cells.  I am not going 
into them here because the file readme.docx will explain this in detail with 
examples.  This file is quite large because it has pictures of all the possible 
methods used.

Note if we have a range of say 6-8 for a cell it is possible that 7 will 
not create a solution.  You can see that when using the equations and see
a cell with an equation like 12-2a.  There is no value of "a" where 7 could 
be a valid solution.  In the solutions.txt file you will find these cases
written as 6,8 instead of 6-8.

Once this second step is complete we may find that not all min and max values 
for the ranges are valid.  In fact in about 25% of the cases some ranges are 
not correct.  So we can do a 2nd pass on the equations.  The program has an 
option to disable this if you wish.  In this case the program will test any min
or max values by trying it and see if the puzzle will run into a contradiction.
In all my testing this 2nd pass has proven to be 100% effective in creating a
puzzle with correct min and max values.  In fact it must otherwise we get a 
solution which is not possible because we already found all solutions.

I have found that although this method is mathematically complete, it is 
not useful for people because I have found that it is very time consuming 
and prone to error.  So there is another method used that was recommended 
by True_Pace_3860 on Reddit.com.  It uses a method called minimum 
perturbation theory.  The method is to pick a direction with 3 unknowns and
select a value in one of the three cells that does not perturbate the other 
cells in that direction.  The program has tried many different methods of 
selecting the best choice but I have found that the best choice is the minimal 
perturbation on one of the diagonal cells.  The non-diagonal cells produce a 
solution about 52% of the time but the diagonal cells produce a solution about 
68% of the time if you go all the way to reducing all directions to two unknowns.
Not only that but getting the lowest average perturbations works best.

The file perturbations.txt is created whenever the perturbation method is used.
This will give you the information on why the choice was made.

I found that if you do just enough perturbations so that we have as many
unknowns as we have equations, we can increase the ability to solve the puzzle
about 85% of the time.  This means we need only do at most two perturbations.
Now use the equation method to reduce the puzzle where it is obvious what the 
solutions are.  The equations now are much easier to do.  You can disable this
limit of perturbations by turning on Do All Perturbations in the Game menu.

The option to do one perturbation at a time (X) will do one perturbation.  If 
this fails it will restore the puzzle to the state before the guess was done. 
Any further guesses will exclude the previous attempt that failed.

On the other hand the option to do minimal perturbations (Z) will repeat the 
above until it is done or it fails.  If this method fails you will need to 
restart the puzzle and try again.

The program also has the ability to use the first pass of the equations method
then switch to the perturbation method.  This solves the puzzle about 98% of
the time.  Not very useful but it was implemented for completeness.

This program contains many additional features.  For example it can run tests 
by testing the above features.  It normally takes about 4 seconds per 10,000
samples.  You can always save or load puzzles.  In addition, if you make a 
mistake or want to try a different guess you can restart the puzzle from the 
start.

Ed Logg
