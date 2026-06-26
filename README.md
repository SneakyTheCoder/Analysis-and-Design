Analysis of the Data Structures

**Vector**
	A vector has a very simple implementation and would be the most user friendly of the three options. A vector would also utilize the least memory on the system. Some disadvantages would be that the linear search is much slower and would require a sacrifice in speed. The prerequisite validation is costly as well, sitting at 0(n^2). A vector is also not naturally sorted and would require sorting before printing.
  
**Hash Table**
	A hash table would have the fastest search metrics of the three options. Hash tables would also have a much quicker insertion sitting at 0(1). Some disadvantages to a hash table in this project is that it is not naturally assorted like a vector and would require sorting to be added. This method would also require another sorting method for option 2. A hash table would also require collision handling for storage.
  
**Binary Search Tree**
	A binary search tree is naturally sorted and would not require any additional steps to sort the order of contents within. A BST also has very fast searching as well as a fast course list print function. Some disadvantages to a BST would be that if the tree becomes unbalanced the big o can degrade to 0(n). Binary search trees also have a much more complicated setup. 

**Recommendation**
For this project I would recommend that a binary search tree is used to store the information. A BST is already sorted and would not require any additional steps to do so. Printing the entire course list only would require an in-order traversal with a cost of 0(n), while vectors and hash tables would require sorting first with a cost of 0(n log n). The search function in a BST is also much faster and only has a cost of 0(log n) on average. Although hash tables also have a fast search function, they would perform worse in other aspects due to needing sorting. 

**printCourseList Function**
```
void BinarySearchTree::PrintCourseList() {
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);

        cout << node->course.courseNumber
            << ", "
            << node->course.courseTitle
            << endl;

        inOrder(node->right);
    }
}
```

What was the problem you were solving in the projects for this course? <br>  

How did you approach the problem? Consider why data structures are important to understand.
How did you overcome any roadblocks you encountered while going through the activities or project?
How has your work on this project expanded your approach to designing software and developing programs?
How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

