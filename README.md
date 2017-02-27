# elevator

Description of the algorithm:

Initialization: 
1. All elevators are set to 0th floor
2. maxfloor value is hardcoded to 20 (can be changed by modifying a global variable)
3. numberof elevators are hardcoded to 2 (can be changed by modifying a global variable)
4. an array of elevators has been initialized
5. an array of requests has been initialized

class object for depiction of elevator:
1. Each elevator has the following information: 
  a. current floor
  b. goal floor (the most furthest stop it needs to make in the current direction
  c. array of stops (where index i is set to 1 if floor i is a requested stop else 0)
  d. elevator id

Requests:

1. Have constructed a request array sized with the maxnumber of floors initialized to 0.
  The encoding for this array is as follows
  requests[i]=0: floor i has no requests
  requests[i]=1: floor i wants to go down
  requests[i]=2: floor i wants to go up
  requests[i]=3: floor i has both up and down requests
  
Scheduling Algorithm: step:

1. go through all the pending requests in the array and assign stops to elevators based on the following criteria.
  For each request:
    a. determine the electricity + timetowait cost for each elevator given their currentfloor and goalfloor.
    b. choose the elevator with lowest electricity + timetowaitcost
    c. on choosing this elevator, set one of its stops to the requesting floor.
    d. electricity: if requesting floor is between current and goalfloor of elevator then surplus electricity cost is 0.
    if not then the surplus cost is calculated by measuring difference between its goalfloor and requestingfloor
    e. timetowait: if heading in requesting floor's direction, timetowait is difference between requesting floor and currentfloor of that elevator
    if not then timetowait is the time for elevator to reach its goal added with time from goal to requesting floor.
                    
    
2. move each elevator in one step towards its goalstate. if goalstate is achieved, look to reverse direction and find other extreme goal state. if none found then stay there.
  set stops of current floor state to 0 in the array.
 

