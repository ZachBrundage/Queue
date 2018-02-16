/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains custom queue data class.
 *
 *    This will contain the class definition of:
 *    queue : similar to std::queue
 * Author
 *    Zach Brundage
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>  // debugging checks
#include <iostream> // error handling output

namespace custom
{

  /************************************************
   * QUEUE
   * A class for the queue container
   ***********************************************/
  template <class T>
    class queue
    {
    public:
      // Constructors
      queue(); // Default
      queue(int capacity)
	throw (const char *);// Non-Default
      queue(const queue & rhs)
	throw (const char *);// Copy
      ~queue() { delete[] data; }//Destructor

      // Operators
      queue & operator = (const queue & rhs)
	throw (const char *);// Assignment

      // Container Interfaces
      int  size() const { return (numPush - numPop); }
      void clear();
      bool empty() const;
      void push(const T &t)throw (const char *);
      void pop();
      T front() const throw (const char *);
      T back() const throw (const char *);

    private:
      // Private Functions
      void resize(int capacity);    // increase the capacity of the queue
      int  iHead() const;// first element in the queue
      int  iTail() const;// last elements in the queue

      //Private Variables
      T * data = NULL;// pointer to T data type
      int numPush;   // tracks how many elements added
      int numPop;                   // tracks how many elements removed
      int numCapacity;// the current capacity of the queue

    };

  // Member Function Definitions

  /********************************************
   * QUEUE :: DEFAULT CONSTRUCTOR
   *******************************************/
  template <class T>
    queue <T> ::queue()
    {
      // Initialize Member Variables
      numPush     = 0;
      numPop      = 0;
      numCapacity = 1;
    }

  /**********************************************
   * QUEUE :: NON-DEFAULT CONSTRUCTOR
   **********************************************/
  template <class T>
    queue <T> ::queue(int capacity)
    throw (const char*)
    {
      // Initialize Member Variables
      numPush     = 0;
      numPop      = 0;
      numCapacity = capacity;
    }

  /*******************************************
   * QUEUE :: COPY CONSTRUCTOR
   *******************************************/
  template <class T>
    queue <T> ::queue(const queue <T> & rhs)
    throw (const char *)
    {
      if (rhs.empty())
	{
	  numPush = 0;
	  numPop  = 0;
	  numCapacity = rhs.numCapacity;
	  return;
	}

      // Initialize
      numPush     = 0;
      numPop      = 0;
      numCapacity = rhs.numCapacity;


      // Allocate
      try
	{
	  data = new T[numCapacity];
	}
      catch (const char*)
	{
	  std::cout << "ERROR: Unable to allocate "
		    << "a new buffer for queue" << std::endl;
	}


      // Copy
      for (int i = rhs.numPop; i < rhs.numPush; i++)
	{
	  data[numPush] = rhs.data[i % numCapacity];
	  numPush++;
	}
    }

  /*******************************************
   * QUEUE :: ASSIGNMENT OPERATOR
   *******************************************/
  template <class T>
    queue <T> & queue <T> :: operator = (const queue <T> & rhs)
    throw (const char *)
    {
      if (rhs.empty())
	{
	  numPush = 0;
	  numPop  = 0;
	  numCapacity = rhs.numCapacity;
	  return *this;
	}

      if (numCapacity < rhs.size())
	resize(rhs.size());

      if (data == NULL)
	{
	  // Allocate
	  try
	    {
	      data = new T[numCapacity];
	    }
	  catch (const char*)
	    {
	      std::cout << "ERROR: Unable to allocate "
			<< "a new buffer for queue" << std::endl;
	    }
	}

      // Copy
      for (int i = rhs.numPop; i < rhs.numPush; i++)
	{
	  data[numPush] = rhs.data[i];
	  numPush++;
	}
      return *this;
    }

  /********************************************
   * QUEUE : CLEAR
   * Reset the pop_push counters
   *******************************************/
  template <class T>
    void queue <T> ::clear()
    {
      numPush = 0;
      numPop  = 0;
    }

  /********************************************
   * QUEUE :: EMPTY
   * Return a boolean value for an empty queue
   *******************************************/
  template <class T>
    bool queue <T> ::empty() const
    {
      if (size() == 0)
	return true;
      else
	return false;
    }

  /********************************************
   * QUEUE : PUSH
   * Add an element to the back of the queue
   *******************************************/
  template <class T>
    void queue <T> ::push(const T &t)
    throw (const char *)
    {
      //cout << "Push Function :" << endl;
      if (size() == numCapacity)
	resize(numCapacity * 2);
      
      if (empty())
	{
	  numPush = 0;
	  numPop = 0;
	  data = new T[numCapacity];
	}

      numPush++;
      data[iTail()] = t;
    }

  /********************************************
   * QUEUE :: POP
   * Remove the first element of the queue
   ********************************************/
  template <class T>
    void queue <T> ::pop()
    {
      if (empty())
	return;
      else
	numPop++;
    }

  /********************************************
   * QUEUE : FRONT
   * Return the front element in the queue
   *******************************************/
  template <class T>
    T queue <T> ::front() const
    throw (const char*)
    {
      if (empty())
	throw "ERROR: attempting to access an element in an empty queue";
      else
	return data[iHead()];
    }

  /********************************************
   * QUEUE : BACK
   * Return the last element in the queue
   *******************************************/
  template <class T>
    T queue <T> ::back() const
    throw (const char*)
    {
      if (empty())
	throw "ERROR: attempting to access an element in an empty queue";
      else
	return data[iTail()];
    }

  /********************************************
   * QUEUE :: RESIZE
   * Increase the size of the capacity
   *******************************************/
  template <class T>
    void queue <T> ::resize(int capacity)
    {
      int oldCapacity = numCapacity;
      numCapacity = capacity;
        
      int arrayCounter = 0;
      T* newData = new T[numCapacity];
      for (int i = numPop; i < numPush; i++)
	newData[arrayCounter++] = data[i % oldCapacity];

      numPop = 0;
      numPush = arrayCounter;
      delete[] data;
      data = newData;
    }

  /********************************************
   * QUEUE :: IHEAD
   * Track the location of the head of the queue
   *******************************************/
  template <class T>
    int queue <T> ::iHead() const
    {
      return numPop % numCapacity;
    }

  /********************************************
   * QUEUE :: ITAIL
   * Track the location of the tail of the queue
   *******************************************/
  template <class T>
    int queue <T> ::iTail() const
    {
      return (numPush - 1) % numCapacity;
    }

}; // namespace custom

#endif // QUEUE_H
