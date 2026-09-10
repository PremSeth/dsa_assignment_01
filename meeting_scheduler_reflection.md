I expect the double pass algorithm to grow at a growth rate of O(n^2) and the single sorted pass to grow at O(nlogn). 

The double pass uses a double for loop, meaning for each item in the list it checks every item in the list again, since the list is n items long, it is O(n^2). 

For the sorted solution we sort once at the start which is nlogn, but we only pass through once which is O(n) but O(n) is less than O(nlogn) and so the overall growth rate is O(nlogn)