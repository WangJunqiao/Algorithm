// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given an int y.
We are looking for any int[] x that satisfies the following constraints:

x has exactly three elements
( x[0] * x[1] ) + x[2] = y
Each x[i] must be between -1000 and 1000, inclusive.
No x[i] can be equal to 0 or 1.

Find and return one such x.

If there are multiple valid solutions, you may return any of them.
You may assume that for our constraints on y (specified below) at least one valid x always exists.

DEFINITION
Class:AddMultiply
Method:makeExpression
Parameters:int
Returns:int[]
Method signature:int[] makeExpression(int y)


CONSTRAINTS
-y will be between 0 and 500, inclusive.


EXAMPLES

0)
6

Returns: {2, 2, 2 }

2*2 + 2 = 6

Note that this is one of many possible solutions. Another solution is:

3*3 + (-3) = 6


1)
11

Returns: {2, 3, 5 }



2)
0

Returns: {7, 10, -70 }

Note that 0 and 1 are not allowed, thus a result like 0 * 0 + 0 would be incorrect.

3)
500

Returns: {-400, -3, -700 }

Some or all of the returned numbers may be negative.

4)
2

Returns: {2, 2, -2 }



5)
5

Returns: {5, 2, -5 }



// END CUT HERE
import java.util.*;
public class AddMultiply {
	public int[] makeExpression(int y) {
		
	}
	public static void main(String[] args) {
		AddMultiply temp = new AddMultiply();
		System.out.println(temp.makeExpression(int y));
	}
}
