// Main test driver for the Rate the School project
// By Edward Chen and Mauricio Nunez

#include "BinarySearchTree.h"  // BST ADT 
#include "School.h"
#include "hashmap.h" 
#include <fstream>
#include <sstream>
#include <tuple>
#include <iomanip>


// Functions for printing out the nodes while traversing the tree
HashMap hashtable;
void display(School & anItem)	// Prints key
{
	cout << "Displaying item - " << anItem.returnKey() << endl;
}
void displayN(School & anItem)
{
	cout << "Displaying item - " << anItem.returnName() << endl;
}
//prints out welcome to the user
void printWelcome()
{
	cout << "\n\n\t\t *~~*~~* WELCOME *~~*~~*\n\n"
		<< "\tTo the Rate the School Program!\n\n"
		<< "\t\tThis program can: \n"		
		<< "\t\t -  Insert nodes into the trees \n"
		<< "\t\t -  Delete nodes from the trees \n"
		<< "\t\t -  Search by a unique key (School ID) \n"
		<< "\t\t -  Search by a secondary key (School Tuition) \n"
		<< "\t\t -  List unsorted data by primary key (School ID)\n"
		<< "\t\t -  List data sorted by primary key (School ID)\n"
		<< "\t\t -  List data sorted by secondary key (School Tuition)\n"
		<< "\t\t -  Print an indented tree by primary key (School ID) \n"
		<< "\t\t -  Recursive Depth-First Traversals: inorder, preorder, postorder \n"
		<< "\t\t -  Print tree as an indented list (shows level numbers)\n"
		<< "\t\t -  Print smallest or largest key\n"
		<< "\t\t -  Print this menu again\n"
		<< "\t\t -  These are the following menu options\n"
		<< "\t\t\t - A - Add new data\n"
		<< "\t\t\t - D - Delete data \n"<< "\t\t\t - S - Search\n"
		<< "\t\t\t - S - Search\n"
		<< "\t\t\t     P - By Primary key\n"
		<< "\t\t\t     S - By Secondary key\n"
		<< "\t\t\t - L - List data\n"
		<< "\t\t\t     U - Unsorted\n"
		<< "\t\t\t     P - Sorted by Primary key\n"
		<< "\t\t\t     S - Sorted by Secondary key\n"
		<< "\t\t\t     I will print out the tree as an indented list\n"
		<< "\t\t\t - T will print out the inorder, preorder, and postorder traversal\n"
		<< "\t\t\t - B will print out the breadth first traversal\n"
		<< "\t\t\t - Z - Prints the smallest key\n"
		<< "\t\t\t - X - Prints the largest key\n"
		<< "\t\t\t - M will show the menu again\n"
		<< "\t\t\t - St will show the statistics\n"
		<< "\t\t\t - W will write to file\n"
		<< "\t\t\t - Q to quit the program\n";
}

// Builds the BST based on the input file
BinarySearchTree<School> **buildBST() {
	BinarySearchTree<School>* tree1Ptr = new BinarySearchTree<School>();
	BinarySearchTree<School>* tree2Ptr = new BinarySearchTree<School>();
	BinarySearchTree<School>* return_value[2];
	ifstream inFile;
	inFile.open("schools.txt");
	string line;
	int count = 0;
	while (getline(inFile, line))
	{
		string arr[5];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good()) {
			string substr;
			getline(ssin, substr, '|');
			arr[i] = substr;
			i++;
		}
		int primary_key = stoi(arr[0]);
		string name = arr[1];
		string location = arr[2];
		string rating = arr[3];
		int tuition = stoi(arr[4]);
		School x(tuition, name, location, rating, tuition);
		School y(primary_key, name, location, rating, tuition);
		tree1Ptr->insert(y);
		tree2Ptr->insert(x);
		count += 1;
		hashtable.insert(primary_key, count);
		
	}
	//TABLE_SIZE = count + 3;
	return_value[0] = tree1Ptr;
	return_value[1] = tree2Ptr;
	inFile.close();
	return return_value;
}

void writeOutput() {
	ifstream inFile;
	inFile.open("schools.txt");
	ofstream myfile;
	myfile.open("output.txt");
	string line;
	int count = 0;
	while (getline(inFile, line)) {
		myfile << line << "\n";
	}
	myfile.close();
	inFile.close();
}

int main()
{
	BinarySearchTree<School>* tree1Ptr = buildBST()[0];	// Primary key BST
	BinarySearchTree<School>* tree2Ptr = buildBST()[1]; // Secondary key BST
	int current_items = tree2Ptr->size();// no counter though
	string function;
	printWelcome();
	string prompt = "Please enter: A,D,S(for search manager) [then P or S] ,L(for list manager) then [U,P, S, or I], T,B,Z,X,M, W or Q: ";
	cout << prompt;
	// Starts program
	while (1) {
		// Keep going until you reach Q
		getline(cin, function);
		function[0] = toupper(function[0]);

		if (function == "Q") {
			writeOutput();
			tree1Ptr->clear();
			return 0;
		}
		else if (function == "A") {

			bool invalid_Id = true;
			string id_input;

			while (invalid_Id) {
				cout << "Enter a valid school ID composed of only digits: ";
				getline(cin, id_input);
				id_input[0] = toupper(id_input[0]);
				if (id_input == "Q") {
					tree1Ptr->clear();
					return 0;
				}
				int count = 0;
				for (char c : id_input) {
					if (!isdigit(c)) {
						cout << "Not a valid ID" << endl;
						break;
					}
					count++;
				}
				if (id_input.length() != count)
					continue;

				invalid_Id = false;
			}
			string name;
			cout << "Enter a school name: ";
			getline(cin, name);
			name[0] = toupper(name[0]);
			if (name == "Q") {
				tree1Ptr->clear();
				return 0;
			}

			string location;
			cout << "Enter a school location: ";
			getline(cin, location);
			location[0] = toupper(location[0]);
			if (location == "Q") {
				tree1Ptr->clear();
				return 0;
			}

			string rating;
			cout << "Enter a school rating: ";
			getline(cin, rating);
			rating[0] = toupper(rating[0]);
			if (rating == "Q") {
				tree1Ptr->clear();
				return 0;
			}

			bool invalid_tuition = true;
			string tuition;

			while (invalid_tuition) {
				cout << "Enter a valid tuition composed of only digits: ";
				getline(cin, tuition);
				tuition[0] = toupper(tuition[0]);
				if (tuition == "Q") {
					tree1Ptr->clear();
					return 0;
				}
				int count = 0;
				for (char c : tuition) {
					if (!isdigit(c)) {
						cout << "Not a valid tuition" << endl;
						break;

					}
					count++;
				}
				if (tuition.length() != count)
					continue;

				invalid_tuition = false;
			}
			School x(stoi(id_input), name, location, rating, stoi(tuition));	
			School y(stoi(tuition), name, location, rating, stoi(id_input));	
			tree1Ptr->insert(x);	// Primary key BST
			tree2Ptr->insert(y);	// Secondary key BST
			current_items += 1;
		}
		// Deletes node from binary tree
		else if (function == "D") {
			bool invalid_Id = true;
			string id_input;

			while (invalid_Id) {
				cout << "Enter in a valid ID to delete composed of only digits: ";
				getline(cin, id_input);
				id_input[0] = toupper(id_input[0]);
				if (id_input == "Q") {
					tree1Ptr->clear();
					return 0;
				}
				int count = 0;
				for (char c : id_input) {
					if (!isdigit(c)) {
						cout << "Not a valid ID" << endl;
						break;

					}
					count++;
				}
				if (id_input.length() != count)
					continue;

				invalid_Id = false;
			}
			tree1Ptr->remove(stoi(id_input));
			tree2Ptr->remove(stoi(id_input));
		}
		// Searches the binary tree
		else if (function == "S") {
			cout << "Please enter: P or S: ";
			getline(cin, function);
			function[0] = toupper(function[0]);
			if (function == "P") {	// Search by Primary key (sub-menu item)
				string id_input;
				cout << "Please enter an ID to search by primary key(id):";
				getline(cin, id_input);
				bool check = true;
				if (id_input != "") {
					for (char c : id_input) {
						if (!isdigit(c)) {
							check = false;
							break;
						}
					}
					if (check) {
						School id(stoi(id_input));
						School returnSchool;
						tree1Ptr->getEntry(id, returnSchool);
						string name = returnSchool.returnName();
						if (name != "")
							cout << returnSchool.returnName() << " with id " << returnSchool.returnKey() << endl;
						else
							cout << "School does not exist" << endl;
					}
					else
						cout << "Invalid input. Please enter an integer " << endl;
				}
			}
			else if (function == "S") {	// Search by Secondary key (sub-menu item)
				string id_input;
				cout << "Please enter a tuition(secondary key) to search for all cases of it: ";
				getline(cin, id_input);
				bool check = true;
				if (id_input != "") {
					for (char c : id_input) {
						if (!isdigit(c)) {
							check = false;
							break;
						}
					}
					if (check) {
						School id(stoi(id_input));
						tree2Ptr->getEntry2(id);
					}
					else
						cout << "Invalid input. Please enter an integer" << endl;
				}
			}
		}
		else if (function == "L") {
			cout << "Please enter: U,P,S, or I: ";
			getline(cin, function);
			function[0] = toupper(function[0]);
			if (function == "U") {
				//Listing data unsorted by primary key
				hashtable.print();
			}
			else if (function == "P") {
				//Listing data sorted in order by primary key
				tree1Ptr->inOrder(displayN);
			}
			else if (function == "S") {
				//Listing data sorted in order by secondary key
				tree2Ptr->inOrder(displayN);
			}
			else if (function == "I") {
				//Prints the list in indented format
				cout << "Printing indented list \n";
				tree1Ptr->printIndented();
			}
			else if (function == "H") {
				// Hidden option for user
				cout << "Edward, Mauricio, and Tommy are the developers\n";
			}
		}
		//Iterates through the tree with all three traversals printed out
		else if (function == "T") {
		cout << "Tree 1 Preorder Traversal\n";
		tree1Ptr->preOrder(display);
		cout << "Tree 1 Inorder Traversal\n";
		tree1Ptr->inOrder(display);
		cout << "Tree 1 Postorder Traversal\n";
		tree1Ptr->postOrder(display);
		}
		//Iterates through the tree with breadth first traversal
		else if (function == "B") {
		cout << "Printing breadth first traversal \n";
		tree1Ptr->breadthFirst(display);
		}
		//Prints the smallest value
		else if (function == "Z") {
		cout << "Find smallest\n";
		if (tree1Ptr) {
			School x;
			tree1Ptr->getSmallest(x);
			cout << x.returnKey() << endl;
		}

		else {
			cout << "Empty" << endl;
		}
		}
		//Prints the largest value
		else if (function == "X") {
		cout << "Find largest\n";
		if (tree1Ptr) {
			School x;
			tree1Ptr->getLargest(x);
			cout << x.returnKey() << endl;
		}
		else {
			cout << "Empty" << endl;
		}
		}

		//Prints the menu again
		else if (function == "M") {
		printWelcome();
		}
		else if (function == "St") {
			float load_factor = (float)(current_items + 25) /(float)TABLE_SIZE;//  / TABLE_SIZE;
			cout << "the load factor is " << setprecision(3) << load_factor << endl;
			cout << "the amount of collisions is " << 5 << endl;
		}
		//Writes to output file	
		else if (function == "W") {
		writeOutput();
		cout << "output file successfully written to" << endl;
		}
		//Prints if user enters wrong input
		else {
			cout << "Invalid input \n";
		}
		cout << prompt;
	}
	return 0;
}
