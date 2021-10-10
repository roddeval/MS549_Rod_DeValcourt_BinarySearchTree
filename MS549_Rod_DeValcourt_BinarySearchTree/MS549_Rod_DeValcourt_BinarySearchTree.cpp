// MS549_Rod_DeValcourt_BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // std::cout << "Hello World!\n";


    int numbers[100] = { 195, 781, 611, 382, 967, 769, 567, 960, 13, 761, 563, 956, 361, 849, 747, 352, 190, 744, 546, 742, 937, 134, 538, 140, 136, 922, 920, 350, 325, 915, 519, 472, 710, 709, 905, 985, 703, 897, 304, 499, 743, 101, 691, 886, 24, 96, 735, 882, 93, 289, 91, 286, 876, 316, 489, 478, 683, 204, 275, 273, 907, 879, 663, 38, 598, 658, 854, 652, 650, 451, 646, 645, 37, 838, 623, 35, 258, 237, 629, 628, 429, 821, 426, 225, 618, 221, 23, 219, 21, 414, 412, 871, 804, 604, 799, 444, 7, 202, 123, 788 };

    // tree(0) -> tree(int debug) -> 0 = false, 1 = true
    Tree tree(0);
    int y;

    cout << "numbers array: ";

    for (int x = 0; x < 100; x++)
    {
        y = numbers[x];
        cout << y << " ";
        tree.Add(y);
    }
    cout << endl;

    const char* p = ".\\";
    const char* f = "output.csv";
    tree.OutputTreeToCSVFile(p, f, 0);
    
    const char* p2 = ".\\";
    const char* f2 = "output.txt";
    tree.OutputTreeToFile(p2, f2, 0);

    cout << "In Order Traverse" << endl;
    tree.InorderTraverse(0);
    cout << "Pre Order Traverse" << endl;
    tree.PreorderTraverse(0);
    cout << "Post Order Traverse" << endl;
    tree.PostorderTraverse(0);

    y = tree.Minimum();
    cout << "Tree Minimum = " << y << endl;
    y = tree.Maximum();
    cout << "Tree Maximum = " << y << endl;



    int numbers2[5] = { 3,1,5,2,4 };
    Tree tree2(1);
    Tree tree3(0);
    Tree tree4(0);
    for (int x = 0; x < 5; x++)
    {
        tree2.Add(numbers2[x]);
        tree3.Add(numbers2[x]);
        tree4.Add(numbers2[x]);
    }

    cout << "Post Order Traverse BEFORE" << endl;
    tree2.OutputHorizontalTree();
    // remove node (no nodes)
    cout << "Removing 2" << endl;
    tree2.Remove(2);
    cout << "Post Order Traverse AFTER remove node (node has no nodes)" << endl;
    tree2.OutputHorizontalTree();

    // remove node (1 child)
    cout << "Post Order Traverse BEFORE" << endl;
    tree3.OutputHorizontalTree();
    cout << "Removing 5" << endl;
    tree3.Remove(5);
    cout << "Post Order Traverse AFTER remove node (node has 1 nodes)" << endl;
    tree3.OutputHorizontalTree();

    // remove node (2 childs)
    cout << "Post Order Traverse BEFORE" << endl;
    tree4.OutputHorizontalTree();
    cout << "Removing 3" << endl;
    tree4.Remove(3);
    cout << "Post Order Traverse AFTER remove node (node has 1 nodes)" << endl;
    tree4.OutputHorizontalTree();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
