/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */
using std::cout;
using std::endl;
namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
	if(s.size()==1)
		return s.top();
	T summation = 0;
	T valueNow = s.top();
	
	s.pop();
	summation = valueNow + sum(s); 
	s.push(valueNow);
	
	return summation;
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> s;
    while(!input.empty()){
      char temp = input.front();
      input.pop();
      //input.push(temp);
      if(temp=='['){
        s.push(temp);
      }
      else if(temp==']'){
        if(s.empty()) return false;
        else s.pop();
      }
    }
    if(s.empty()) return true;
    else return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
	queue<T> q2;
	int numNow = 1;//number now to determine whether to reverse
    // Your code here
	while(!q.empty()){
		if(numNow%2!=0){
			int cnt = 0;//# in the subsequence
			
			while( cnt++ < numNow && !q.empty()){
				q2.push(q.front());
				q.pop();
			}
			++numNow;
		}
		else {
			int cnt = 0;//# in the subsequence
			while( cnt++ < numNow && !q.empty()){
				s.push(q.front());
				q.pop();
			}
			while(!s.empty()){
				q2.push(s.top());
				s.pop();				
			}
			++numNow;
		}
	}
	q = q2;
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T temp1;

    // Your code here
    if (!s.empty()){
      temp1 = s.top();// retrive the first element of stack
	  // divide it into smaller subproblem
	  // i.e.the stack except the first element
	  s.pop();
	  bool subproblem = verifySame(s,q);// must be done first!
	  // the last element will emerge exactly when the stack has exactly one element
	  // then the last element of stack can be compared with the first element of the queue
	  // After then, just move the first element of queue to the back 
	  // and compare the second element of queue with the second element of the stack(which is stored in temp1)
      retval = subproblem && (q.front()==temp1); // subproblem must preceed the comparison!
	  q.push(q.front());// move the first element to the back of the queue	
      q.pop();			// so that the comparison between q.front() and temp1 will be correctt.
	  //recover the changes of popping out many elements of the stack 
	  s.push(temp1);
      
    }
    return retval;

}
}
