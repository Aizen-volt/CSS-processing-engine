# Data Structures and Algorithms project
## CSS processing engine
The goal of the task is to write a simple CSS processing engine. The program
loads CSS sections interspersed with command sections from standard input. CSS sections should be
be parsed and placed in appropriate structures, command sections must be parsed and executed
writing the results to the standard output (after ==).
## List of commands
- ???? – beginning of the command section;
- **** - resume reading CSS;
- ? – write the number of CSS sections;
- i,S,? – print the number of selectors for section no. i (numbers start with 1), if there is no such block
skip;
- i,A,? - write the number of attributes for section no. and, if there is no such block or section, skip it;
- i,S,j – print the j-th selector for the i-th block (section and attribute numbers start with 1) if not
has a skip section or selector;
- i,A,n – print the value of the attribute named n for the i-th section, if there is none, skip it;
- n,A,? – print the total (for all blocks) number of occurrences of the attribute named n. (Within
of a single block, duplicates should be removed at the loading stage). 0 is possible;
- z,S,? – print the total (for all blocks) number of occurrences of the selector z. Possible is 0;
- z,E,n – print the value of the attribute named n for the selector z, in the case of multiple occurrences of the selector z
we take the last one. If not, skip;
- i,D,* - delete the entire section no. i (i.e. separators+attributes), after correct execution write deleted;
- i,D,n – remove the attribute named n from the i-th section, if the operation results in an empty section, it should
be also deleted (along with selectors if applicable), after correct execution, print deleted.
## Implementation notes:
Selectors and attributes should be stored as lists.
Individual CSS sections should be stored in a doubly-linked list (to effectively
execute the command E – the last occurrence of the attribute). To make better use of memory, the list should
include an array of T=8 structures representing a block (where T is an adjustable constant) and a counter of currently occupied structures (due to possible deletion of elements).
It is worth using counters to speed up operations parameterized with a cell number, i.e. i.
When allocating a new node, an array of T Elements is created. When adding elements, depending on
how much free space there is in a list node, it should be used before new nodes are allocated.
When deleting elements, if an empty table remains, the node should be deleted. There's no need to
move elements between nodes, connect nodes, etc.
## Example
### Input
#breadcrumb  
{  
width: 80%;  
font-size: 9pt;  
}  
h1, body {  
min-width: 780px;  
margin: 0;  
padding: 0;  
font-family: "Trebuchet MS", "Lucida Grande", Arial;  
font-size: 85%;  
color: #666666;  
}  
h1, h2, h3, h4, h5, h6 {color: #0066CB;}  
????  
?  
1,S,?  
1,S,1  
1,A,?  
2,A,font-family  
h1,S,?  
color,A,?  
h1,E,color  
1,A,padding  
1,D,*  
?  
2,D,color  
?  
**** <br />
h1, h2, h3, h4, h5, h6 {color: #0066FF;}  
????  
?  
### Output:  
? == 3  
1,S,? == 1  
1,S,1 == #breadcrumb  
1,A,? == 2  
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial  
h1,S,? == 2  
color,A,? == 2  
h1,E,color == #0066CB  
1,D,* == deleted  
? == 2  
2,D, color == deleted  
? == 1  
? == 2  
