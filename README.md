# grader
Multi-threaded assignment for calculating statistics on student grades

# 1. Goal
In  this  project,  we  implement  a  small  program,  which run  multiple  threads. As  we have studied  in  the  chapter 4,  we  will  create  a  child thread,  which willexecute  a  given  task. Through this project, we will learn how to handlemultiple threadsand how to share data in-between.

# 2. Introduction

## A. Statistical analysis of students grades
Write a multithreaded program that conducts various statistical analysesof students. This program will read a text file with students’grades and will then create four threads, each which will calculate statistical values. The fivestatistical functions are following: average, minimum, maximum,median, and the number of students who pass(meaning their grade is greater than the average). 

## B. Multithreading
All these information representing the average, minimum, maximum, median, and the number of students who pass will be stored globally. Therefore, the information can be shared between threads.  For  instance,  the  average  will  be  used  to  evaluate  whether  a  student  passes  or  not. Once all the information is set, the parent thread will output it once all the child threads have exited following fork-join strategy.

# Requirements

## A. Language
The program should be implemented in one of the following languages - C, C++, C#, and Java. However, students who use C will get 1 bonus point, which is 1% out of the total grade.

## B. Executing the program
The program begins when we enter _*"grader"*_ without any parameters. The program will load a text file called _*"grades.txt."*_ See an example below.

```
user_account> grader
Read grades: 88 82 85 91 69 77 79 90 95
Average is 84
Minimum is 69
Maximum is 95
Median is 85
Number of Students Who Pass: 5
```

## C. Input file - grades.txt
The program MUST load the text file named "grades.txt," which contains students' grade. The format of the grades is following:

88,82,85,91,69,77,79,90,95

Separator is a comma, and the maximum number of grades is 40. For grading, instructor will use his own text file formatted in the same style. Therefore, the program MUST follow this format. _Program which has a different file name or different format (e.g., using a space as a separator) will be taken off penalty points._

## D. Creating child threads for each function
For each function, the program should create a child thread, which will calculate average, minimum, maximum, median, or number of students who pass. During the calculations through child threads, the parent thread should wait and then will continue after all the child threads complete. _The output should be displayed by the parent thread, and any program which does not follow this rule will be taken off penalty points._

## E. Readability of source code
The source code should be easy to read with good indentation and proper amount of comments.


