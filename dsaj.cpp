#include<iostream>
#include<string>
#include<stdlib.h>
#include<ctype.h>
#include <regex>
using namespace std;
char head='0';
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
					cout<<"\n\nSuggested Contacts:\n";
					temp1=1;
				}
				
				searchSuggestedName(root->left, name, temp1);
				
				regex b("("+name+")(.*)");
				if(regex_match(root->name, b) && root->name!=name)
				{
					cout<<"\nName- "<<root->name;
					cout<<"\nMobile number- "<<root->mNo<<endl;
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
				cout<<"\nResults:\n";
				temp1=1;
			}
			if(root->name==name)
			{
			    cout<<"\nName- "<<root->name;
				cout<<"\nMobile number- "<<root->mNo;
				found2=true;
			}
			else
			{
    			if(checkAlphabeticalOrder(root->name,name))
			    {
			        if(root->right==NULL)
			        {
			            if(found2==false)
			                cout<<"\nNo similar contact found!\n";
			            return;
			        }
				    searchExactName(root->right,name, temp1);
			    }
			    else
			    {
			        if(root->left==NULL)
			        {
			            if(found2==false)
			                cout<<"\nNo similar contact found!\n";
			            return;
			        }
			    	searchExactName(root->left,name, temp1);
			    }
			}


			return;
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
};
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

int main()
{


    contact_info contacts("0","0"),*root=NULL;
    string mNo,name;

		cout<<"\n-------------------------------------\n";
    	cout<<"---Welcome to smart phone directory--\n";
    	cout<<"-------------------------------------\n\n";
        
    while(1){
        int c,s=1;
		
    	cout<<"\nChose feature:";
        cout<<"\n1.Add a contact\n2.Search a contact\n3.Display all contacts\nPress 0 to exit.\n\n";
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
					root=contacts.Insert(root,name,mNo);
					break;
            case 2:
            		//system("cls");
            		cout<<"\nSearch for: ";
            		getline(cin,name);
					contacts.search_contact(root,name);
					break;
            case 3:
					//system("cls");
					contacts.print_inorder(root);
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

