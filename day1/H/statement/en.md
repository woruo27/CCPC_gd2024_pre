{{ self.title() }}

{{ s('description') }}

For courses in P university, there are many small classes set up for group discussions. Students can choose which class to join freely. However, there is a limit for every class. So not every student can choose their favorite class.

In this semester, $n$ students take course A, in this course, $m$ small classes are set up, the $i$th of them has capacity $b_i$, which means at most $b_i$ students can choose the class. For student $i$, a list $a_{i,1}\sim a_{i,k_i}$ is given, denote the priority of classes to student $i$. $a_{i,1}$ is the class with the highest priority,  and $a_{i,k_i}$ is the lowest. If some class $j$ is not in the list, then student $i$ won't choose class $j$ in any case.

The students will choose which class to take in the order of $1\sim n$, for any student $i$, he/she will find the class with highest priority(call it $j$) and still haven't exceed the capacity(no more than $b_j-1$ students among $1\sim i-1$ chose $j$) and choose it. If student $i$ can't find such class, then he/she will not choose any course.

Now the lists of priority for every student is given, please rearrange the order of the students, such that the number of students that chose some class is maximized, and find such a rearrangement. 

{{ s('input format') }}

{{ self.input_file() }}

The first line contains a positive integer $T(1\leq T\leq 500)$, the number of testcases.

For each testcase, the first line contains two positive integers $n,m(1\leq n,m\leq 500)$, the number of students and classes.

The next line contains $m$ non-negative integers $b_i(0\leq b_i\leq 500)$, the capacity for each course.

For the following $n$ lines, every line begins with a non-negative integer $k_i(0\leq k_i\leq m)$, followed by $k_i$ pairwise distinct positive integers $a_{i,1}\sim a_{i,k_i}$, the list of priority for student $i$.

{{ s('output format') }}

{{ self.output_file() }}

For each testcase, print two lines, the first line contains a single integer $ans$ denoting the answer. The second line contains $n$ numbers, a permutation of $1\sim n$, denoting the rearrangement. If there are multiple solutions, you can print any.

{{ s('sample', 1) }}

{{ self.sample_text() }}

 {{ self.title_sample_description() }}

For the first testcase, under the given rearrangement, student $2$ will choose $5$, then student $4$ choose $3$, student $5$ choose $1$, student $1$ tries to choose $1,5$, but these classes are already full, so student $1$ will eventually choose $2$, student $3$ tries to choose $3$ but full, so choose $4$ instead. The solution for this testcase is not unique, for example, $\{2,5,4,3,1\}$ is also a possible rearrangement.

For the second testcase, $\{1,2,3,4,5\}$ is **not** a valid rearrangement, if we rearrange as this, then student $1,2,3,4$ will respectively choose $1,2,3,3$, for student $5$, $1,3$ are already full, so no classes can be chosen.