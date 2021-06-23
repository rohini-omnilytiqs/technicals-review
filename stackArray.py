class Stack:
    '''
    Simple stack class
    
    Attributes 
    ----------
    max_items : optional, int
        max number of items in the stack
    items : list
        array for stack
    
    Methods
    -------
    pop() -> int
        removes top of stack and returns its value
    
    push(value) 
        adds an element to the top of the stack
    
    peek() -> int
        returns top of stack without removing it
    
    is_empty() -> bool
        returns true if stack is empty, false otherwise
    
    is_full() -> bool
        returns true if stack is full, false otherwise
    '''

    def __init__(self, max_items=None):
        ''' creates an instance of stack class

        Parameters
        ----------
        max_items : optional, int
            max number of items in stack 
        '''

        self.max_items = max_items
        self.items = []

    def pop(self):
        ''' removes top of stack and returns its value

        Returns 
        -------
        int
            value of item removed
        '''

        if self.is_empty():
            raise Exception("Stack is empty")
        value_to_return = self.items[len(self.items)-1]
        self.items.pop()
        return value_to_return
    
    def push(self, value):
        ''' adds an element to the top of the stack

        Parameters
        ----------
        value : int
            number corresponding to value to add to stack
        '''

        if self.is_full():
            raise Exception("Stack is full")
        else:
            self.items.append(value) 

    def peek(self):
        ''' returns top of stack without removing it

        Returns 
        -------
        int
            value corresponding to top of stack
        '''

        return self.items[len(self.items)-1]
    
    def is_empty(self):
        ''' checks if stack is empty

        Returns 
        -------
        bool
            true if stack is empty, otherwise false
        '''
        return len(self.items)==0
    
    def is_full(self):
        ''' checks if stack is full, if max_items was specified

        Returns 
        -------
        bool
            true if stack is full, otherwise false
        '''
        
        if self.max_items is not None:
            return len(self.items)==self.max_items
        else:
            return False

if __name__=="__main__":
    my_stack = Stack(3)
    my_stack.push(1)
    my_stack.push(2)
    my_stack.push(3)
    if my_stack.is_full:
        print("Stack is full")
    print("Top of stack is {}".format(my_stack.peek()))
    my_stack.pop()
    my_stack.pop()
    print("Now, top of stack is {}".format(my_stack.peek()))
    my_stack.pop()
    if my_stack.is_empty:
        print("Stack is empty")
    my_stack.push(4)

        