//Program by Christina Ochsner
//PS#: 1166214
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <cctype>
#include <string>
#include <iomanip>
#include <bits/stdc++.h> 

using namespace std;

//./o input=input11.txt output=output11.txt sort=sort11.txt
//./o input=input12.txt output=output12.txt sort=sort12.txt
//./o input=input13.txt output=output13.txt sort=sort13.txt
//./o input=input14.txt output=output14.txt sort=sort14.txt
//./o input=input15.txt output=output15.txt sort=sort15.txt
//./o input=input16.txt output=output16.txt sort=sort16.txt
//./o input=input23.txt output=output23.txt sort=sort23.txt
//./o input=input26.txt output=output26.txt sort=sort26.txt
struct Node
{
	int id;
	char* first;
	char* last;
	char *dob;
	double gpa;
	bool donePrev;
	bool doneNext;
	struct Node *next;
};
void deletes(struct Node **head, int key)
{
	struct Node* temp = *head;
	struct Node* prev = 0;

	if (temp != NULL && temp->id == key)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while (temp != NULL && temp->id != key)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;

	prev->next = temp->next;

	free(temp);
}
void add(struct Node** head, int id, char* first, char* last, char dob[], double gpa)
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	struct Node *lastNode = *head;  
	struct Node *current= *head;

	node->id = id;
	node->first = first;
	node->last = last;
	node->dob = dob;
	node->gpa = gpa;

	node->next = NULL;

	if (*head == NULL)
	{
		*head = node;
		return;
	}

	while (current != NULL)
	{
		if (current->id == node->id)
		{
			current->id = node->id;
			current->first = node->first;
			current->last = node->last;
			current->dob = node->dob;
			current->gpa = node->gpa;
			return;
		}
		current = current->next;
	}
	while (lastNode->next != NULL)
	{

		lastNode = lastNode->next;
	}

	lastNode->next = node;
	return;
}
bool compareString(char* s, char* s2, struct Node* node, struct Node* cu, bool &test, bool insert)
{
	char news[25];
	char news2[25];
	bool underscore = false;
	bool underscore2 = false;
	int i = 0;
	while (s[i] != '\0')
	{
		news[i] = tolower(s[i]);
		if (s[i] == '_')
		{
			underscore = true;
		}
		i++;
	}
	news[i] = '\0';
	i = 0;
	while (s2[i] != '\0')
	{
		news2[i] = tolower(s2[i]);
		if (s2[i] == '_')
		{
			underscore2 = true;
		}
		i++;
	}
	news2[i] = '\0';
	char *news3 = news;
	if (underscore)
	{
		news3 = strtok(news, "_");
		int l = 0;
		char *chArr[40];
		while (news3 != NULL)
		{
			chArr[l] = news3;
			news3 = strtok(NULL, "_");
			l++;
		}
		int m = 0;
		while (m + 1 < l)
		{
			news3 = strcat(chArr[m], chArr[m + 1]);
			m++;
		}
	}
	char *news4 = news2;
	if (underscore2)
	{
		news4 = strtok(news2, "_");
		int l = 0;
		char *chArr[40];
		while (news4 != NULL)
		{
			chArr[l] = news4;
			news4 = strtok(NULL, "_");
			l++;
		}
		int m = 0;
		while (m + 1 < l)
		{
			news4 = strcat(chArr[m], chArr[m + 1]);
			m++;
		}
	}
	bool equals = false;
	bool str = false;
	int length;
	if (strlen(news3) > strlen(news4))
	{
		length = strlen(news4);
		str = true;
	}
	else if (strlen(news3) < strlen(news4))
	{
		length = strlen(news3);
	}
	else
	{
		length = strlen(news3);
		equals = true;
	}
	if (strncmp(news3, news4, length) == 0)
	{
		if (equals)
		{
			test = false;
			if(insert)
			{
				cu->doneNext = false;
				node->doneNext = false;
			}
			return false;
		}
		else
		{
			test = true;
			if (str)
			{
				return false;

			}
			else
			{
				return true;
			}
		}
	}
	else if (strncmp(news3, news4, length) > 0)
	{
		test = true;
		return false;
	}
	else if (strncmp(news3, news4, length) < 0)
	{
		test=true;
		return true;
	}
}
template <class T>
T compareNum(T num1, T num2,struct Node* node, struct Node* cu, bool &test, bool insert)
{
	if (num1 < num2)
	{
		test = true;
		return true;
	}
	else if (num1 == num2)
	{
		test = false;
		if(insert)
		{
			cu->doneNext = false;
			node->doneNext = false;
		}
		return false;
	}
	else
	{
		test = true;
		return false;
	}
}
void bubbleSort(struct Node *head, int h, char t[][25],bool &test, int last)
{
	int swapped;
	struct Node *ptr1;
	bool compare;
	struct Node *lptr = NULL;
	bool insert=false;

	if (head == NULL)
	{ 
		return;
	}

	do
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			int count;
				if(h>last)
				{
					count=0;
				}
				else
				{
					count=h+1;
				}
					
					bool equal=true;
					while(count<=last)
					{
						switch (t[count][0])
						{
							
							case 'i':
							{
								compare = compareNum(ptr1->next->id, ptr1->id, ptr1, ptr1->next, test, insert);
								break;
							}
							case 'f':
							{
								string t = ptr1->next->first;
								string t2 = ptr1->first;

								compare = compareString(ptr1->next->first, ptr1->first, ptr1, ptr1->next, test, insert);

								strcpy(ptr1->next->first, t.c_str());
								strcpy(ptr1->first, t2.c_str());

								break;
							}
							case 'l':
							{
								string t = ptr1->next->last;
								string t2 = ptr1->last;

								compare = compareString(ptr1->next->last, ptr1->last, ptr1, ptr1->next, test, insert);

								strcpy(ptr1->next->last, t.c_str());
								strcpy(ptr1->last, t2.c_str());

								break;
							}
							case 'D':
							{
								compare = compareString(ptr1->next->dob, ptr1->dob, ptr1, ptr1->next, test, insert);
								break;
							}
							case 'G':
							{
								compare = compareNum(ptr1->next->gpa, ptr1->gpa, ptr1, ptr1->next, test, insert);
								break;
							}
						}
						if(!test)
						{
							cout<<ptr1->first<<endl; 
							cout<<ptr1->next->first<<endl;
							equal=true;
							count++;
						}
						if(test)
						{
							equal=false;
							break;
						}
						
					}
					switch (t[h][0])
					{
						case 'i':
						{
							compare = compareNum(ptr1->next->id, ptr1->id, ptr1, ptr1->next, test, insert);
							break;
						}
						case 'f':
						{
							string t = ptr1->next->first;
							string t2 = ptr1->first;

							compare = compareString(ptr1->next->first, ptr1->first, ptr1, ptr1->next, test, insert);

							strcpy(ptr1->next->first, t.c_str());
							strcpy(ptr1->first, t2.c_str());

							break;
						}
						case 'l':
						{
							string t = ptr1->next->last;
							string t2 = ptr1->last;

							compare = compareString(ptr1->next->last, ptr1->last, ptr1, ptr1->next, test, insert);

							strcpy(ptr1->next->last, t.c_str());
							strcpy(ptr1->last, t2.c_str());

							break;
						}
						case 'D':
						{
							compare = compareString(ptr1->next->dob, ptr1->dob, ptr1, ptr1->next, test, insert);
							break;
						}
						case 'G':
						{
							compare = compareNum(ptr1->next->gpa, ptr1->gpa, ptr1, ptr1->next, test, insert);
							break;
						}
					}
					
					if (compare&&equal)
					{
						int tempID = ptr1->id;
						char* tempF = ptr1->first;
						char* tempL = ptr1->last;
						char *tempD = ptr1->dob;
						double tempG = ptr1->gpa;
						bool tempDone = ptr1->doneNext;
						bool tempDone2 = ptr1->donePrev;
						ptr1->id = ptr1->next->id;
						ptr1->first = ptr1->next->first;
						ptr1->last = ptr1->next->last;
						ptr1->dob = ptr1->next->dob;
						ptr1->gpa = ptr1->next->gpa;
						ptr1->doneNext = ptr1->next->doneNext;
						ptr1->donePrev = ptr1->next->donePrev;
						ptr1->next->id = tempID;
						ptr1->next->first = tempF;
						ptr1->next->last = tempL;
						ptr1->next->dob = tempD;
						ptr1->next->gpa = tempG;
						ptr1->next->doneNext = tempDone;
						ptr1->next->donePrev = tempDone2;
						swapped = 1;
					}
				
			
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	struct Node *ptr2 = head;
	while (ptr2 != NULL)
	{
		ptr2->donePrev = ptr2->doneNext;
		ptr2 = ptr2->next;
	}
}
void insert(struct Node** head, struct Node* node, char t[][25], int h, bool &test)
{
	struct Node* current;
	bool compare=false;
	bool insert=true;
	
	if (*head == NULL)
	{
		compare = true;
	}
	else
	{
		switch (t[h][0])
		{

			case 'i':
			{
				compare = !(compareNum((*head)->id,node->id,*head, node, test, insert));
				break;
			}
			case 'f':
			{
				compare = !(compareString((*head)->first,node->first, *head, node, test, insert));
				break;
			}
			case 'l':
			{
				compare = !(compareString((*head)->last,node->last, *head, node, test, insert));
				break;
			}
			case 'D':
			{
				compare = !(compareString((*head)->dob,node->dob, *head, node, test, insert));
				break;
			}
			case 'G':
			{
				compare = !(compareNum((*head)->gpa,node->gpa, *head, node, test, insert));
				break;
			}
			default:
			{
				cout << "Invalid sort option" << endl;
				break;
			}
		}
	
	}
	if (compare)
	{
		node->next = *head;
		*head = node;
	}
	else
	{
		current = *head;
		do
		{
			if (compare)
			{
				current = current->next;
			}
			if (current->next != NULL)
			{
				switch (t[h][0])
				{
					case 'i':
					{
						compare=compareNum(current->next->id,node->id, node, current, test, insert);
						break;
					}
					case 'f':
					{
						string t = current->next->first;
						string t2 = node->first;
	
						compare=compareString(current->next->first, node->first, node, current, test, insert);
						
						strcpy(current->next->first, t.c_str());
						strcpy(node->first, t2.c_str());

						break;
					}
					case 'l':
					{
						string t= current->next->last;
						string t2 = node->last;

						compare=compareString(current->next->last, node->last, node, current->next, test, insert);
						
						strcpy(current->next->last, t.c_str());
						strcpy(node->last, t2.c_str());

						break;
					}
					case 'D':
					{
						compare=compareString(current->next->dob,node->dob, node, current->next, test, insert);
						break;
					}
					case 'G':
					{				
						compare=compareNum(current->next->gpa, node->gpa, node, current, test, insert);
						break;
					}
				}
			}
			else
			{
				compare = false;
			}
		} 
		while (compare);
		

		node->next = current->next;
		current->next = node;
	}
	struct Node *ptr2 = *head;
	while (ptr2 != NULL)
	{
		ptr2->donePrev = ptr2->doneNext;
		ptr2 = ptr2->next;
	}

}
void print(struct Node *node, ofstream& file3)
{
	while (node != NULL)
	{
		//cout << "{id:" << setfill('0') << setw(7)<< node->id << ",first:" << node->first << ",last:" << node->last << ",DOB:" << node->dob << ",GPA:" << fixed << setprecision(1) << node->gpa << "}" << endl;
		file3 << "{id:" << setfill('0') << setw(7)<<node->id << ",first:" << node->first << ",last:" << node->last << ",DOB:" << node->dob << ",GPA:" << fixed << setprecision(1) << node->gpa << "}" << endl;
		node = node->next;
	}
}
void sort(struct Node** head, char t[][25], int h)
{
	struct Node *sorted = NULL;
	struct Node *current = *head;
	bool test=true;
	int last = h+1;
	t[last][0] = 'i';
	
	if (h >= 0)
	{
		while (current != NULL)
		{
			current->doneNext=true;
			struct Node *next = current->next;
			insert(&sorted, current, t, h, test);
			current = next;
		}
		*head = sorted;
		h--;
		cout<<endl;
		while (h >= 0)
		{
			bubbleSort(*head, h, t, test, last-1);
			cout<<endl;
			h--;
		}
		bubbleSort(*head, last, t, test, last-1);
	}
	else
	{
		while (current != NULL)
		{
			struct Node *next = current->next;
			insert(&sorted, current, t, last, test);
			current = next;
		}
		*head = sorted;
	}
	
}

int main(int argc, char *argv[])
{	
	//Declare and/or initialize variables to be used in program.
	char input[25];
	char sortBy[25];
	char output[25];
	char type;
	int i=0;
	int y=1;
	int o;
	string str;
	
	//Parse command line to retrieve and store file names.
	
	while(argv[y][i]!='\0')
	{
		switch(argv[y][i])
		{
			case '=':
				i++;
				o=0;
				while(argv[y][i]!='\0'&&argv[y][i]!=';'&&argv[y][i]!=' ')
				{
					switch(type)
					{
						case 'i':
						input[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							input[o+1]='\0';
						}
						break;
						
						case 's':
						sortBy[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							sortBy[o+1]='\0';
						}
						break;
						
						case 'o':
						output[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							output[o+1]='\0';
						}
						break;
					}
					o++;
					i++;
				}
				if(argv[y][i]=='\0'&&argc>2&&y<3)
				{
						i=0;
						y++;
				}
			break;
			
			case 'i':
				type='i';
				i++;
			break;
			
			case 's':
				type='s';
				i++;
			break;
			
			case 'o':
				if(argv[y][i+1]=='u')
				{
					type='o';
				}
				i++;
			break;
			
			default:
				i++;
			break;
		}

	}
	//Declare and open input/output files
	ifstream file;
	ifstream file2;
	ofstream file3;

	file.open(input);
	file2.open(sortBy);
	file3.open (output);
	

	char entries[2000][100];
	int u=0;
	int v=0;
	int id;		
	char* first;
	char* last;
	double gpa;
	char *dob;
	struct Node* head = NULL;
	if (file.is_open()&&file2.is_open())
 	{
		while(getline(file, str))
		{
			bool i=false;
			bool f=false;
			bool l=false;
			bool d=false;
			bool g=false;
			
			istringstream ss(str);

			if (str[0]=='d')
			{
				char* deleteStr=new char[25];
				ss>> deleteStr;
				if (strncmp(deleteStr, "delete", 10) != 0)
				{
					cout << "Invalid command" << endl;
					return 0;
				}
				ss >> id;
				deletes(&head, id);
			}
			while(ss>>entries[u][v])
			{
				switch(entries[u][v])
				{
					case ':':
					{
						stringstream converter;
						u++;
						v=0;
						ss>>entries[u][v];
						
						
						while(entries[u][v]!=','&&entries[u][v]!='}')
						{
							v++;
							ss>>entries[u][v];
						}
						entries[u][v]='\0';
						if(!i)
						{
							converter<<entries[u];
							converter>>id;
							i=true;
						}
						else if(!f)
						{
							first=entries[u];
							f=true;
						}
						else if(!l)
						{
							last=entries[u];
							l=true;
						}
						else if(!d)
						{
							dob = entries[u];
							d=true;
						}
						else if(!g)
						{
							converter<<entries[u];
							converter>>gpa;
							g=true;
						}
						if(g&&i&&d&&l&&f)
						{
							add(&head,id, first, last, dob, gpa);
						}
						u++;
						v=0;
					}
					break;
					default:
					v++;
					break;
				}
			}
			
		}
		file.close();
	}
	char t[2000][25];
	int h = 0;
	while (file2 >> t[h])
	{
		h++;
	}
	sort(&head, t, h - 1);
	print(head,file3);

	file2.close();
	file3.close();
	//system("pause");
	return 0;
}