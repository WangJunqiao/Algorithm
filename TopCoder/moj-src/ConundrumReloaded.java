// BEGIN CUT HERE
// PROBLEM STATEMENT
// Once upon a time, N people sat around a circle. They were numbered 0 through N-1 in counter-clockwise order. Each person was either a honest person or a liar. A honest person always tells the truth, a liar always lies. You asked some of them (possibly all or none) whether the person sitting to the right of them is a liar. You are given their answers in a String answers with N characters. For each i, character i of answers is one of the following:


'L' if person i said that person (i+1) is a liar,
'H' if person i said that person (i+1) is a honest person,
'?' if you didn't ask person i.

(Above, (i+1) is considered modulo N. That is, person N-1 is talking about person 0.)

You are given the String answers. If there is at least one possible combination of honest people and liars that is consistent with answers, return the smallest possible number of liars. Else return -1.

DEFINITION
Class:ConundrumReloaded
Method:minimumLiars
Parameters:String
Returns:int
Method signature:int minimumLiars(String answers)


CONSTRAINTS
-answers will contain between 2 and 50 characters, inclusive.
-Each character in answers will be 'L', 'H' or '?'.


EXAMPLES

0)
"LLH"

Returns: 1

According to the input:

Person 0 says that person 1 is a liar.
Person 1 says that person 2 is a liar.
Person 2 says that person 0 is a honest person.

Clearly, they cannot all be honest, so there is at least one liar. It is possible that person 1 is liar and the other two are honest. Hence, the smallest possible number of liars is one.

(Note that it is also possible that person 1 is honest and the other two are liars.)

1)
"?????"

Returns: 0

Nobody told us anything. It is possible that everybody is honest.

2)
"LHLH?"

Returns: 2

If person #1 and person #2 are liars, then the answers would be "LHLHH". This is consistent with the answers we received.

3)
"??LLLLLL??"

Returns: 3



4)
"LLL"

Returns: -1

Each of the 8 possible combinations of (liar / honest person) will lead to a contradiction.

// END CUT HERE
import java.util.*;
public class ConundrumReloaded {
	public int minimumLiars(String answers) {
		
	}
	public static void main(String[] args) {
		ConundrumReloaded temp = new ConundrumReloaded();
		System.out.println(temp.minimumLiars(String answers));
	}
}
