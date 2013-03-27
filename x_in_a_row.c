
int x_in_a_row(int array[], int size, int length_to_win) {
 
  /* Statement to stop recursion. If there are less numbers to check
     than the required to win, then there is no match
     If length_to_win is 0 then no need to check. Size cannot be negative*/
  if (size < length_to_win || length_to_win == 0 || size <= 0) {
    return -1;
  }
  
  // i is the loop variable, last is the last element in array, and match is bool
  int i, last, match;
  last = size-1;
  match = 1;
 
  // Negative 1 is empty. So no point in checking for other matching empty spots
  if (array[last] != -1) {
    
    /* starts at last array element. Then checks if it is a match to the 
    * others preceding it.*/
    for (i = last; i > (last -(length_to_win-1)) && match; i--) {
      if (array[i] != array[i-1]) {
	match = 0;
      }
    }
  }
  
  // If there is a match, return the value
  if (match == 1 && array[last] != -1 ){
    return array[last];
    
  // If not match, recursivily call function again with trailing element gone
  } else {
    return x_in_a_row(array, size-1,length_to_win);
  }
}