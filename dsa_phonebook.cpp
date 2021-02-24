#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<regex>
#include <ctime>
#include<fstream>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

using namespace std;
char head='0';
string searchResults="";
bool findee=false;
bool found=false;
void capitalize (string &s)
{
    bool cap = true;

    for(unsigned int i = 0; i <= s.length(); i++)
    {
        if (isalpha(s[i]) && cap == true)
        {
            s[i] = toupper(s[i]);
            cap = false;
        }
        else if (isalpha(s[i]) && cap == false)
        {
            s[i] = tolower(s[i]);
        }
        else if (isspace(s[i]))
        {  
            cap = true;
        }
    }
}
class call_logs
{
	string name;
	string time,eTime;
	call_logs* link;
	public:
		call_logs* InsertLog(call_logs** top,string name,string timee,string etime)
		{
			call_logs* temp=new call_logs();
			temp->name=name;
			
			temp->time=timee;
			temp->eTime=etime;
			if(*top==NULL)
			{
				*top=temp;
				(*top)->link=NULL;
			}
			else
			{
				temp->link=*top;
				*top=temp;				
			}
		}
		void DisplayLog(call_logs* top)
		{
			if(top==NULL)
			{
				cout<<"No logs";
			}
			else
			{
				call_logs* temp=top;
				while(temp!=NULL)
				{
					cout<<"\nName- "<<temp->name<<"\n";
					cout<<"\nTime of calling- "<<temp->time;
					cout<<"\nCall ended- "<<temp->eTime<<"\n\n\n";
					temp=temp->link;
				}
			}
		}	
};
class contact_info
{
	string name;
	string mNo;
	contact_info *left,*right;

	public:
		contact_info* Insert(contact_info* root,string name,string mNo)
		{
			if(!root)
			{
				return new contact_info(name,mNo);
			}
			if(checkAlphabeticalOrder(root->name,name))
			{
				root->right=Insert(root->right,name,mNo);
			}
			else
			{
				root->left=Insert(root->left,name,mNo);
			}
			return root;

		}
		contact_info(string newName,string newMno)
		{
			name=newName;
			mNo=newMno;
			left=NULL;
			right=NULL;
		}
		void print_inorder(contact_info* root)
		{
			if(!root)
			{
				return;
			}
			else
			{
				print_inorder(root->left);
				if(::head=='0')
				{
					::head=root->name[0];
					cout<<"\n-------------------------------";
					cout<<"\n"<<head;
					cout<<"\n-------------------------------";

				}
				else if(::head!=root->name[0])
				{
					::head=root->name[0];
					cout<<"\n-------------------------------";
					cout<<"\n"<<head;
					cout<<"\n-------------------------------";

				}

				cout<<"\nName- "<<root->name;
				cout<<"\nMobile no-"<<root->mNo<<"\n";
				print_inorder(root->right);
			}
		}

		void search_contact(contact_info* root,string name)
		{
			int temp1=0;
		    searchExactName(root, name, temp1);
		    searchSuggestedName(root, name, temp1);
			
		}

		void searchSuggestedName(contact_info* root, string name, int temp1)
		{
			if(!root)
			{
				return;
			}
			else
			{
				if(temp1==0){
					if(!findee)
					{
						cout<<"\n\nSuggested Contacts:\n";
						
					}
					temp1=1;
				}
				
				searchSuggestedName(root->left, name, temp1);
				
				regex b("("+name+")(.*)");
				if(regex_match(root->name, b) && root->name!=name)
				{
					if(!findee)
					{
					    cout<<"\nName- "<<root->name;
						cout<<"\nMobile number- "<<root->mNo<<endl;
						
					}
					else
					{
						if(searchResults=="")
						{
							searchResults.append(root->name);
						}
						else
						{
							string temp="-"+root->name;
							searchResults.append(temp);
						}
						
					}
					::found=true;
				
				}
				
				searchSuggestedName(root->right, name, temp1);
			}
		}
		
		void searchExactName(contact_info* root,string name, int temp1){
		    if(!root)
			{
				return;
			}
			bool found2=false;
			if(temp1==0){
				if(!findee)
				{
					cout<<"\nResults:\n";
					
				}
				temp1=1;
			}
			if(root->name==name)
			{
				if(!findee)
				{
				    cout<<"\nName- "<<root->name;
					cout<<"\nMobile number- "<<root->mNo;
					
				}
				found2=true;
				if(findee)
				{
					
					searchResults.append(root->name);
				}
				found2=true;
			}
			else
			{
    			if(checkAlphabeticalOrder(root->name,name))
			    {
			        if(root->right==NULL)
			        {
			            if(found2==false&&!findee)
			                cout<<"\nNo similar contact found!\n";
			            return;
			        }
				    searchExactName(root->right,name, temp1);
			    }
			    else
			    {
			        if(root->left==NULL)
			        {
			            if(found2==false&&!findee)
			                cout<<"\nNo similar contact found!\n";
			            return;
			        }
			    	searchExactName(root->left,name, temp1);
			    }
			}


			return;
		}
		
		bool checkduplicate(contact_info* root,string name){
		    if(!root)
			{
				return false;
			}
			if(root->name==name)
			{
				return true;
			}
			else
			{
    			if(checkAlphabeticalOrder(root->name,name))
			    {
				    return checkduplicate(root->right,name);
			    }
			    else
			    {
			    	return checkduplicate(root->left,name);
			    }
			}
			return false;
		}
		
		bool checkAlphabeticalOrder(string name,string name1)
		{
			int sizeName=name.size();
			int sizeName1=name.size();
			int count=0;
			if(sizeName<=sizeName1)
			{
				while(count<sizeName)
				{
					if((int)name[count]<(int)name1[count])
					{
						return true;
					}
					else if((int)name[count]>(int)name1[count])
					{
						return false;
					}
					count++;
				}
			}
			else
			{
				while(count<sizeName1)
				{
					if((int)name[count]<(int)name1[count])
					{
						return true;
					}
					else if((int)name[count]>(int)name1[count])
					{
						return false;
					}
					count++;

				}
			}
			if(sizeName>sizeName1)
			{
				return true;
			}
			else
			{
				return false;
			}

		}
		contact_info* minValueNode(contact_info* node) 
		{ 
		    contact_info* current = node; 
		  
		    while (current && current->left != NULL) 
		        current = current->left; 
		  
		    return current; 
		} 
		
		contact_info* deleteNode(contact_info* root, string name) 
		{ 
		    if (root == NULL) return root; 
		  
		    if(root->name==name)
		    { 
		        if (root->left == NULL) 
		        { 
		            contact_info* temp = root->right; 
		            free(root); 
		            return temp; 
		        } 
		        else if (root->right == NULL) 
		        { 
		            contact_info* temp = root->left; 
		            free(root); 
		            return temp; 
		        } 
		  
		        contact_info* temp = minValueNode(root->right); 
		  
		        root->name = temp->name; 
		  
		        root->right = deleteNode(root->right, temp->name); 
		    } 

		    if (!checkAlphabeticalOrder(root->name,name)) 
		        root->left = deleteNode(root->left, name); 
		  
		    else if (checkAlphabeticalOrder(root->name,name)) 
		        root->right = deleteNode(root->right, name); 
		  
		    return root; 
		} 
		
};
string returnTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
	string str(buffer);
	return str;
}
bool checkValidName(string name)
{
	int size=name.size();
	int flag=0;
	for(int i=0;i<size;i++)
	{
		if(isdigit(name[i]))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		return false;
	}
	else
	{
		return true;
	}

}
bool checkValidMobileNo(string mNo)
{
	int size=mNo.size();
	if(size!=10)
	{
		return false;
	}
	else
	{
		int flag=0;
		for(int i=0;i<size;i++)
		{
			if(isalpha(mNo[i]))
			{

				flag=1;
				break;
			}
			if(mNo[i]==' ')
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
string getchoice()
{
	string s = ::searchResults;
	string s1=s;
	string delimiter = "-";
	int count=0;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
	    token = s.substr(0, pos);
	    count++;
	    s.erase(0, pos + delimiter.length());
	}
	count++;
	string namee[count];
	int i=0;
	while ((pos = s1.find(delimiter)) != string::npos) {
	    namee[i] = s1.substr(0, pos);
	    i++;
	    s1.erase(0, pos + delimiter.length());
	}
	namee[i]=s1;
	for(i=0;i<count;i++)
	{
		cout<<i+1<<" "<<namee[i]<<endl;
	}
	string choice;
	cout<<"Enter your choice-";
	getline(cin,choice);
	for(i=0;i<count;i++)
	{
		string no=to_string((i+1));
		string temp=""+no;
		if(choice==temp)
		{
			return namee[i];
		}
	}
	
	
}
int main()
{
	contact_info contacts("0","0"),*root=NULL;
	call_logs calls,*top=NULL;
	//check for duplicacy in the names harsh
    string timee,mNo,name,result,etime;
    

		cout<<"\n-------------------------------------\n";
    	cout<<"---Welcome to smart phone directory--\n";
    	cout<<"-------------------------------------\n\n";
        
    while(1){
        int c,s=1;
		
    	cout<<"\nChoose feature:";
        cout<<"\n1.Add a contact\n2.Search a contact\n3.Display all contacts\n4.Delete a contact\n5.Call Someone\n6.Display Log\n7.Update Contact\nPress 0 to exit.\n\n";
        cout<<"Your choice: ";
        cin>>c;
        system("cls");
        cout<<"\n-------------------------------------\n";
    	cout<<"---Welcome to smart phone directory--\n";
    	cout<<"-------------------------------------\n\n";
        
        cin.ignore(100,'\n');
        switch(c){
            case 1:
            		//system("cls");
            		cout<<"\nEnter your name: ";

					getline(cin,name);
            		if(!checkValidName(name))
            		{
            			cout<<"\nEnter a Valid Name!";
            			break;
					}
            		cout<<"\nEnter your mobile number: ";
            		getline(cin,mNo);

            		if(!checkValidMobileNo(mNo))
            		{
            			cout<<"\nEnter a Valid Mobile number!";
            			break;
					}
					capitalize(name);
				    if(!contacts.checkduplicate(root,name))
					{
					    root=contacts.Insert(root,name,mNo);
					}
					else
					{
					    cout<<"The contact name already exists.";
					}
					break;
            case 2:
            		//system("cls");
            		cout<<"\nSearch for: ";
            		getline(cin,name);
					::found=false;
					capitalize(name);
					contacts.search_contact(root,name);
					if(!::found)
					{
						cout<<"\nNo suggestions !";
					}
					break;
            case 3:
					//system("cls");
					contacts.print_inorder(root);
					::head='0';
					break;
			case 4:
					
					cout<<"Delete for: ";
					getline(cin,name);
					capitalize(name);
					::findee=true;
					contacts.search_contact(root,name);
					::findee=false;
					result=getchoice();
					
					if(searchResults=="")
					{
						cout<<endl<<"No matching pattern found";
					}
					else
					{
						root=contacts.deleteNode(root,result);	
						cout<<endl<<"Deleted";
					}
					::searchResults="";
					break;
			case 5:
					
					cout<<"Call: ";
					
					getline(cin,name);
					capitalize(name);
					::findee=true;
					contacts.search_contact(root,name);
					::findee=false;
					result=getchoice();
					
					if(searchResults=="")
					{
						cout<<endl<<"No matching pattern found";
					}
					else
					{
						timee=returnTime();
							
						cout<<"\nCalling";
						sleep(1.5);
						cout<<".";
						sleep(1.5);
						cout<<".";
						sleep(1.5);
						cout<<".";
						sleep(1.5);
						cout<<"\nConnected!";
						cout<<"\nPress enter to disconnect.";
						cin.ignore();
						cout<<endl<<"Call successfully completed.";
						etime=returnTime();
						calls.InsertLog(&top,result,timee,etime);
					}
					::searchResults="";
					break;
			case 6:
					calls.DisplayLog(top);
					break;
			case 7:
					cout<<"Update for: ";
					getline(cin,name);
					capitalize(name);
					::findee=true;
					contacts.search_contact(root,name);
					::findee=false;
					result=getchoice();
					
					if(searchResults=="")
					{
						cout<<endl<<"No matching pattern found";
					}
					else
					{
						string newname,newno;
						cout<<"Enter the new name: ";
						getline(cin,newname);
						cout<<"Enter the new mobile number: ";
						getline(cin,newno);
						if(!checkValidMobileNo(newno))
	            		{
	            			cout<<"\nEnter a Valid Mobile number!";
	            			break;
						}
						if(contacts.checkduplicate(root,name))
						{
						    cout<<"The contact name already exists.";
						    break;
						}
						root=contacts.deleteNode(root,result);
						root=contacts.Insert(root,newname,newno);
						
						cout<<endl<<"Contact updated!";
					}
					::searchResults="";
					break;
            case 0:
					s=0;
					cout<<"\nExited";
					break;
        }
        if(s==0)
        break;
        cout<<"\n\n===============================================\n";
    }
	return 0;
}
