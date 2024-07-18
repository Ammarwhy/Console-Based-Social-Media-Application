#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "header.h"
#include <Windows.h>

using namespace std;


//=================================================COLOUR================================================================\\

//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

//=========================================== STRING HELPER CLASS ==========================================================\\


int StringHelper::Compare(vector<User*> users, string str, int totalUsers)
{
	for (int i = 0; i < totalUsers; i++)
	{
		if (str == users[i]->getID())
		{
			return i;
		}
	}
	return -1;
}

int StringHelper::Compare(vector<Page*> users, string str, int totalUsers)
{
	for (int i = 0; i < totalUsers; i++)
	{
		if (str == users[i]->getID())
		{
			return i;
		}
	}
	return -1;
}

int StringHelper::Compare(vector<Post*> posts, string str, int totalPosts)
{
	for (int i = 0; i < totalPosts; i++)
	{
		if (str == posts[i]->getPostIDd())
		{
			return i;
		}
	}
	return -1;
}
//=============================================== DATE CLASS ======================================================\\

Date::Date()
{
	currentDate = 0;
	currentMonth = 0;
	currentYear = 0;
	date = 0;
	month = 0;
	year = 0;
}

Date:: ~Date()
{
	//cout << "Destructor for Date() called\n";
}
void Date::setDate(int d)
{
	date = d;
}

void Date::setMonth(int m)
{
	month = m;
}

void Date::setYear(int y)
{
	year = y;
}

int Date::getDate()
{
	return date;
}

int Date::getMonth()
{
	return month;
}

int Date::getYear()
{
	return year;
}
//============================================== USER CLASS =======================================================\\


User::User()
{
	//cout << "Constructor for Users() called\n";

	id = " ";
	fname = " ";
	lname = " ";
	friendCount = 0;
}

User::~User()
{
	//cout << "Destructor for Users called\n\n";
}

void User::loadFromUser(ifstream& file)
{
	file >> id;
	file >> fname;
	file >> lname;
}


void User::addFriendID(string n)
{
	friendsID.push_back(n);
}

void User::addFriend(User* users)
{
	friends.push_back(users);
}

void User::addPageID(string n)
{
	pagesID.push_back(n);
}

void User::addPage(Page* pages)
{
	likedPages.push_back(pages);
}

void User::addLikedPosts(Post* posts)
{
	likedPosts.push_back(posts);
}

void User::addSharedPosts(Post* posts)
{
	sharedPosts.push_back(posts);
}

void User::addComments(Comments* c)
{
	comment.push_back(c);
}
string User::getFname()
{
	return fname;
}

string User::getLname()
{
	return lname;
}

string User::getID()
{
	return id;
}

vector<string> User::getFriendID()
{
	return friendsID;
}

vector<User*> User::getFriends()
{
	return friends;
}

vector<string> User::getPageID()
{
	return pagesID;
}

vector<Page*> User::getPage()
{
	return likedPages;
}

vector<Post*> User::getLikedPost()
{
	return likedPosts;
}

vector<Post*> User::getSharedPost()
{
	return sharedPosts;
}

void User::addPassword(string str)
{
	password = str;
}

string User::getPassword()
{
	return password;
}
//================================================ FACEBOOK CLASS =====================================================\\


Facebook::Facebook()
{
	//cout << "Constructor for Facebook() called\n\n";
	totalUsers = 0;

	users.reserve(100);
	pages.reserve(100);
	posts.reserve(100);
	comments.reserve(100);
	activ.reserve(100);
}

Facebook::~Facebook()
{
	//cout << "Destructor called for Facebook()\n\n";
	for (int i = 0; i < totalUsers; i++)
	{
		delete users[i];
	}
	users.clear();

	for (int i = 0; i < totalPages; i++)
	{
		delete pages[i];
	}
	pages.clear();

	for (int i = 0; i < totalPosts; i++)
	{
		delete posts[i];
	}
	posts.clear();

	for (int i = 0; i < totalComments; i++)
	{
		delete comments[i];
	}
	comments.clear();

	for (int i = 0; i < totalActivities; i++)
	{
		delete activ[i];
	}
	activ.clear();
}
void Facebook::load()
{
	ifstream file;


	//FOR USERS
	file.open("users.txt");

	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}

	file >> totalUsers;
	users.resize(totalUsers);

	for (int i = 0; i < totalUsers; i++)
	{
		users[i] = new User;
		users[i]->loadFromUser(file);
	}

	file.close();

}

void Facebook::loadPassword()
{
	ifstream file;
	file.open("Passwords.txt");
	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}
	string str;
	for (int i = 0; i < totalUsers; i++)
	{
		file >> str;
		users[i]->addPassword(str);
	}
}

	//FOR FRIENDS AND LIKED PAGES
void Facebook::loadPages()
{
	ifstream file;
	file.open("Pages.txt");
	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}

	file >> totalPages;
	pages.resize(totalPages);

	for (int i = 0; i < totalPages; i++)
	{
		pages[i] = new Page;
		pages[i]->loadFromPages(file);
	}
	file.close();

	file.open("friends.txt");

	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}

	string str;
	StringHelper s;
	for (int i = 0; i < totalUsers; i++)
	{
		file >> str;
		int indexUser = s.Compare(users, str, totalUsers);

		file >> str;
		int add;
		while (str != "-1")
		{
			//new code
			add = s.Compare(users, str, totalUsers);
			users[indexUser]->addFriend(users[add]);
			file >> str;
		}

		file >> str;
		while (str != "-1")
		{
			add = s.Compare(pages, str, totalPages);
			users[indexUser]->addPage(pages[add]);
			file >> str;
		}
	}

	file.close();
}

void Facebook::loadComments()
{
	ifstream file;
	string str;
	StringHelper s;
	file.open("Comments.txt");

	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}
	file >> totalComments;
	comments.resize(totalComments);

	for (int i = 0; i < totalComments; i++)
	{
		comments[i] = new Comments;
		comments[i]->loadFromComments(file);

		file >> str;
		int indexPost = s.Compare(posts, str, totalPages);
		comments[i]->addPosts(posts[indexPost]);
		posts[indexPost]->addComment(comments[i]);

		file >> str;
		comments[i]->setCommentBy(str);
		int indexUser = s.Compare(users, str, totalUsers);
		if (indexUser == -1)
		{
			indexUser = s.Compare(pages, str, totalPages);
			comments[i]->addPage(pages[indexUser]);
		}
		comments[i]->addUser(users[indexUser]);
		users[indexUser]->addComments(comments[i]);
		string t;
		getline(file, t);
		comments[i]->setComment(t);
	}
}

void Facebook::loadPosts()
{
	//FOR POSTS
	ifstream file;
	string str;
	StringHelper s;
	file.open("Posts.txt");

	if (!file.is_open())
	{
		cout << "ERRRR! Error 404, file not found >:[ \n\n";
	}
	
	file >> totalPosts;
	posts.resize(totalPosts);
	for (int i = 0; i < totalPosts; i++)
	{
		posts[i] = new Post;
		posts[i]->loadFromPosts(file);
		
		file >> str;
		posts[i]->setPostBy(str);

		while (str != "-1")
		{
			int indexUser = s.Compare(users, str, totalUsers);
			if (indexUser == -1)
			{
				indexUser = s.Compare(pages, str, totalPages);
				pages[indexUser]->addSharedPost(posts[i]);
				posts[i]->addSharedBy(pages[indexUser]);
			}
			else
			{
				users[indexUser]->addSharedPosts(posts[i]);
				posts[i]->addSharedBy(users[indexUser]);
			}
			file >> str;
		}
		file >> str;
		while (str != "-1")
		{
			int indexUser = s.Compare(users, str, totalUsers);
			if (indexUser == -1)
			{
				indexUser = s.Compare(pages, str, totalPages);
				pages[indexUser]->addLikedPost(posts[i]);
				posts[i]->addlikedby(pages[indexUser]);
			}

			else 
			{
				users[indexUser]->addLikedPosts(posts[i]);
				posts[i]->addlikedby(users[indexUser]);
			}
			file >> str;
		}
	}
	file.close();
}

void Facebook::loadActivity()
{
	ifstream file;
	string str;
	StringHelper s;
	
	file.open("Activity.txt");

	if (!file.is_open())
	{
		cout<< "ERRRR! Error 404, file not found >:[ \n\n";
	}

	file >> totalActivities;
	activ.resize(totalActivities);

	for (int i = 0; i < totalActivities; i++)
	{
		activ[i] = new Activity;
		
		file >> str;
		int indexPost = s.Compare(posts,str,totalPosts);
		activ[i]->addPostPtr(posts[indexPost]);
		activ[i]->loadFromActivity(file,str);
		posts[indexPost]->setActivity(activ[i]->getActivity());
	}
}
int Facebook::getTotalUsers()
{
	return totalUsers;
}

void Facebook::viewUserTimeline(User* user)
{
	cout << "Viewing User time line: \n\n";

	vector<Post*> sh = user->getSharedPost();
	if (sh.size() == 0)
	{
		cout << "No post found\n";
	}
	else {
	cout << user->getID() << " " << user->getFname() << " " << user->getLname() << " posted: \n\n";
	for (int i = 0; i < sh.size(); i++)
	{
		if (sh[i]->getActiviti() != 0)
		{
			cout << user->getFname() << " " << user->getLname() << " is ";
			if (sh[i]->getActiviti() == 1)
			{
				cout << "feeling \n";
			}

			else if (sh[i]->getActiviti() == 2)
			{
				cout << "thinking about \n";
			}

			else if (sh[i]->getActiviti() == 3)
			{
				cout << "Making \n";
			}

			else if (sh[i]->getActiviti() == 4)
			{
				cout << "celebrating \n";
			}
			cout << "\t" << '"' << sh[i]->getText() << '"' << "(" << sh[i]->getDate() << "/" << sh[i]->getMonth() << "/" << sh[i]->getYear() << ")" << endl << endl;

		}
		else
		{
			cout << "\t" << '"' << sh[i]->getText() << '"' << "(" << sh[i]->getDate() << "/" << sh[i]->getMonth() << "/" << sh[i]->getYear() << ")" << endl << endl;
		}
	}
	}
}

void Facebook::ViewPage()
{
	string str;
	StringHelper s;
	cout << "Enter Page ID (p1-p12): ";
	cin >> str;
	int indexPage = s.Compare(pages, str, totalPages);
	while (indexPage == -1)
	{
		cout << "===============================\n";
		cout << "Page not found\n";
		cout << "Enter Page ID again: ";
		cin >> str;
		indexPage = s.Compare(pages, str, totalPages);
	}
	vector<Post*> post = pages[indexPage]->getSharedPosts();
	cout << endl;
	cout << "===============================\n";
	cout << "Showing Posts for " << '"' << pages[indexPage]->getTitle() << '"' << endl << endl;
	for (int i = 0; i < post.size(); i++)
	{
		cout << post[i]->getPostIDd()<< "\n \tposted on ("<<post[i]->getDate()<<"/"<<post[i]->getMonth()<<"/"<<post[i]->getYear()<<")\n";
		cout << pages[indexPage]->getTitle() << " posted: \n\t";
		if (post[i]->getActiviti() != 0)
		{
			cout << pages[indexPage]->getTitle() << "is ";
			if (post[i]->getActiviti() == 1)
			{
				cout << "feeling \n";
			}

			else if (post[i]->getActiviti() == 2)
			{
				cout << "thinking about \n";
			}

			else if (post[i]->getActiviti() == 3)
			{
				cout << "Making \n";
			}

			else if (post[i]->getActiviti() == 4)
			{
				cout << "celebrating \n";
			}
			cout << "\t\t" << '"' << post[i]->getText() << '"' << endl << endl;
		}
		else 
		{
			cout << '"' << post[i]->getText() << '"' << endl << endl;
		}
	}
}

void Facebook::timeLineDisplay(int userIndex, User* user)
{
	vector<Page*> pg = users[userIndex]->getPage();
	vector<User*> us = users[userIndex]->getFriends();
	vector<Comments*> cm;
	vector<Post*> ps;
	StringHelper s;
	string str,commentBy;

	for (int i = 0; i < us.size(); i++)
	{
		if (us.size() > i)
		{
			ps = us[i]->getSharedPost();

			for (int j = 0; j < ps.size(); j++)
			{
				if ((currentDate - ps[j]->getDate() == 0 || currentDate - ps[j]->getDate() == 1) && (currentYear - ps[j]->getYear() == 0) && (currentMonth - ps[j]->getMonth() == 0))
				{
					//cout << "-----------------------------------------------\n\n";
					cout << ps[j]->getPostIDd() << " \n\tposted on (" << ps[j]->getDate() << "/" << ps[j]->getMonth() << "/" << ps[j]->getYear() << ")" << endl << endl;
					cm = ps[j]->getComments();
					str = ps[j]->getPostBy();

					int indexPage = s.Compare(users, str, totalUsers);
					cout << users[indexPage]->getFname() << " " << users[indexPage]->getLname() << " ";

					if (ps[j]->getActiviti() != 0)
					{
						cout << "is ";
						if (ps[j]->getActiviti() == 1)
						{
							cout << "feeling \n";
						}

						else if (ps[j]->getActiviti() == 2)
						{
							cout << "thinking about \n";
						}

						else if (ps[j]->getActiviti() == 3)
						{
							cout << "Making \n";
						}

						else if (ps[j]->getActiviti() == 4)
						{
							cout << "celebrating \n";
						}
						cout << "\t" << '"'<<ps[j]->getText() <<'"'<< endl << endl;
						postFunctionality(cm,ps[j],user);
						//viewComments(cm);
					}

					else
					{
						cout << "posted: \n\n";
						cout << "\t" << '"' << ps[j]->getText() << '"' << endl << endl;
						postFunctionality(cm,ps[j],user);
						//viewComments(cm);
					}
					cout << endl;
				}
			}
		}

		if (pg.size() > i)
		{
			ps = pg[i]->getSharedPosts();
			for (int j = 0; j < ps.size(); j++)
			{
				if ((currentDate - ps[j]->getDate() == 0 || currentDate - ps[j]->getDate() == 1) && (currentYear - ps[j]->getYear() == 0) && (currentMonth - ps[j]->getMonth() == 0))
				{
					//cout << "-----------------------------------------------\n\n";
					cout << ps[j]->getPostIDd() << " \n\tposted on (" << ps[j]->getDate() << "/" << ps[j]->getMonth() << "/" << ps[j]->getYear() << ")" << endl<<endl;
					str = ps[j]->getPostBy();
					cm = ps[j]->getComments();
					int indexPage = s.Compare(pages, str, totalPages);
					cout << pages[indexPage]->getTitle() << " ";

					if (ps[j]->getActiviti() != 0)
					{
						cout << "is ";
						if (ps[j]->getActiviti() == 1)
						{
							cout << "feeling \n";
						}

						else if (ps[j]->getActiviti() == 2)
						{
							cout << "thinking about \n";
						}

						else if (ps[j]->getActiviti() == 3)
						{
							cout << "Making \n";
						}

						else if (ps[j]->getActiviti() == 4)
						{
							cout << "celebrating \n";
						}
						cout << ps[j]->getText() << endl;
						postFunctionality(cm,ps[j],user);
						//viewComments(cm);
					}

					else
					{
						cout << "posted: \n\n";
						cout << "\t" << ps[j]->getText() << endl<<endl;
						postFunctionality(cm,ps[j],user);
						//viewComments(cm);
					}
				}
			}
		}
	}
	cout << "-----------------------------------------------\n\n";
}

void Facebook::viewFriends(int userIndex)
{
	vector<User*> fr = users[userIndex]->getFriends();
	//cout << "===============================\n";
	//cout << "\nVIEWING FRIENDS \n\n";
	for (int i = 0; i < fr.size(); i++)
	{
		cout << fr[i]->getID() << "- " << fr[i]->getFname() << " " << fr[i]->getLname() << endl << endl;
	}
	//cout << "===============================\n\n";
}

void Facebook::viewLikedPages(int userIndex)
{
	vector<Page*> pg = users[userIndex]->getPage();

	//cout << "===============================\n";
	//cout << "VIEWING PAGES \n\n";
	for (int i = 0; i < pg.size(); i++)
	{
		cout << pg[i]->getID() << "- " << pg[i]->getTitle() << endl << endl;
	}
	//cout << "===============================\n\n";
}

void Facebook::viewLikedBy(Post*& ps)
{
	vector<User*> liked=ps->getLikedBy();
	cout << "Post liked by: \n\n";
	for (int i = 0; i < liked.size(); i++)
	{
		cout << liked[i]->getID() << " " << liked[i]->getFname() << " " << liked[i]->getLname() << endl << endl;
	}
}

void Facebook::viewComments(vector<Comments*> cm)
{
	StringHelper s;
	cout << "\nViewing Comments: \n\n";
	for (int i = 0; i < cm.size(); i++)
	{
		commentBy = cm[i]->getCommentBy();//user id return
		int indexUser = s.Compare(users, commentBy, totalUsers);
		if (indexUser == -1)
		{
			indexUser = s.Compare(pages, commentBy, totalPages);
			cout << pages[indexUser]->getTitle() << " commented: " << '"' << cm[i]->getText() << '"' << endl << endl;
			for (int i = 0; i < cm.size(); i++)
			{
				commentBy = cm[i]->getCommentBy();//user id return
				int indexUser = s.Compare(users, commentBy, totalUsers);
				if (indexUser == -1)
				{
					indexUser = s.Compare(pages, commentBy, totalPages);
					cout << pages[indexUser]->getTitle() << " commented: " << '"' << cm[i]->getText() << '"' << endl << endl;
				}
				cout << users[indexUser]->getFname() << " " << users[indexUser]->getLname() << " commented: " << cm[i]->getText() << endl << endl;
			}
		}
		cout << users[indexUser]->getFname() << " " << users[indexUser]->getLname() << " commented: " << '"' << cm[i]->getText() << '"' << endl << endl;
	}
}

void Facebook::postFunctionality(vector<Comments*>& cm, Post* ps, User* user)
{
	cout << "===============================\n";
	cout << "1. Add a Comment\n";
	cout << "2. Like Post\n";
	cout << "3. View Comments\n";
	cout << "4. View Likes\n";
	cout << "5. Exit\n";
	cout << "===============================\n";
	int choice;
	cout << "Choice: ";
	cin >> choice;
	cout << "===============================\n";

	while (choice) {
		if (choice == 1)
		{
			addAComment(ps, user, cm);
			cout << "===============================\n";
			cout << "1. Add a Comment\n";
			cout << "2. Like Post\n";
			cout << "3. View Comments\n";
			cout << "4. View Likes\n";
			cout << "5. Exit\n";
			cout << "===============================\n";
			cout << "Choice: ";
			cin >> choice;
			cout << "===============================\n";
		}

		else if (choice == 2)
		{
			addLikes(ps, user);
			cout << "===============================\n";
			cout << "1. Add a Comment\n";
			cout << "2. Like Post\n";
			cout << "3. View Comments\n";
			cout << "4. View Likes\n";
			cout << "5. Exit\n";
			cout << "===============================\n";
			cout << "Choice: ";
			cin >> choice;
			cout << "===============================\n";
		}

		else if (choice == 3)
		{
			viewComments(cm);
			cout << "===============================\n";
			cout << "1. Add a Comment\n";
			cout << "2. Like Post\n";
			cout << "3. View Comments\n";
			cout << "4. View Likes\n";
			cout << "5. Exit\n";
			cout << "===============================\n";;
			cout << "Choice: ";
			cin >> choice;
			cout << "===============================\n";
		}

		else if (choice == 4)
		{

			viewLikedBy(ps);
			cout << "===============================\n";
			cout << "1. Add a Comment\n";
			cout << "2. Like Post\n";
			cout << "3. View Comments\n";
			cout << "4. View Likes\n";
			cout << "5. Exit\n";
			cout << "===============================\n";
			cout << "Choice: ";
			cin >> choice;
			cout << "===============================\n";
		}

		else if (choice == 5)
		{
			//cout << "Exited Commands successfully\n\n";
			break;
		}

		else
		{
			cout << "Invalid Command!!!!\n";
			cout << "===============================\n";
			cout << "1. Add a Comment\n";
			cout << "2. Like Post\n";
			cout << "3. View Comments\n";
			cout << "4. View Likes\n";
			cout << "5. Exit\n";
			cout << "===============================\n";

			cout << "Choose again: ";
			cin >> choice;
		}
	}
}

void Facebook::addAComment(Post* ps, User* us,vector<Comments*>& cm)
{
	string str, ID;
	StringHelper s;
	ID = ps->getPostIDd();
	cout << "\tEnter a comment: ";
	cin.ignore();
	getline(cin,str);
	vector<Comments*> ptr = ps->getComments();
	cm.resize(cm.size() + 1);
	for (int i = cm.size()-1; i < cm.size(); i++)
	{
		cm[i] = new Comments;
		cm[i]->setComment(str);
		int indexPost = s.Compare(posts, ID, totalPosts);
		cm[i]->addPosts(posts[indexPost]);
		cm[i]->setCommentBy(us->getID());
		int indexUser = s.Compare(users, us->getID(), totalUsers);
		cm[i]->addUser(users[indexUser]);
		posts[indexPost]->addComment(cm[i]);
	}
	cout << "\tComment added Successfully!!\n\n";
}

void Facebook::addLikes(Post* ps, User* us)
{
	bool found = false;
	vector<User*> liked = ps->getLikedBy();
	for (int i = 0; i < liked.size(); i++)
	{
		if (us->getID() == liked[i]->getID())
		{
			found = true;
		}
	}
	if (found)
	{
		cout << "\tYou have already liked the post!\n\n";
	}
	else
	{
		ps->addlikedby(us);
		us->addLikedPosts(ps);
		cout << "\tPost liked successfully!\n\n";
	}
}
void Facebook::Functionality()
{
	currentDate = 18;
	currentMonth = 4;
	currentYear = 2024;
	int choice2;
	string choice,pass;
	StringHelper s;
	cout << "===============================\n";
	cout << "WELCOME TO FACEBOOK\n";
	cout << "===============================\n";

	cout << "Choose a User to log in to (u1-u20): ";
	cin >> choice;
	int indexUser1 = s.Compare(users, choice, totalUsers);
	while (indexUser1 == -1)
	{
		cout << "Incorrect ID!!\n";
		cout << "Choose a User to log in to (u1-u20): ";
		cin >> choice;
		indexUser1 = s.Compare(users, choice, totalUsers);
	}
	int indexUser = s.Compare(users, choice, totalUsers);

	cout << endl;
	cout << "Logging in to " << users[indexUser]->getID() << " " << users[indexUser]->getFname() << " " << users[indexUser]->getLname() << "\n";
	cout << endl;
	cout << "===============================\n";
	cout << "Enter Password: ";
	cin >> pass;
	//cout << "===============================\n";
	int i=0;
	while (pass != users[indexUser]->getPassword())
	{
		//cout << "===============================\n";
		cout << "ERRR! Incorrect password, please try again: ";
		cin >> pass;
		//cout << "===============================\n";
		if (i == 4)
		{
			cout << "===============================\n";
			cout << "\nYou have been locked out of your account for entering the incorrect password " << i + 1 << " times.\n\n";
			cout << "===============================\n";
			cout << "GOODBYE!!!!!!!!!!!!!!\n";
			cout << "===============================\n";
			break;
		}
		i++;
	}
	
	if (pass == users[indexUser]->getPassword())
	{
		cout << "===============================\n";
		cout << "\nLog in to " << users[indexUser]->getID() << " " << users[indexUser]->getFname() << " " << users[indexUser]->getLname() << " successful!\n\n";
		cout << "===============================\n";
		//cout << "	FUNCTIONALITY\n\n";
		cout << "1. Show Home Page\n\n";
		cout << "2. Show Friend list\n\n";
		cout << "3. Show Liked Pages\n\n";
		cout << "4. Show Page Timeline\n\n";
		cout << "5. Show User Timeline\n\n";
		cout << "6. Log out\n";
		cout << "===============================\n";
		cout << "Choice: ";
		cin >> choice2;
		cout << "===============================\n";
		//cout << endl;
		while (choice2)
		{
			if (choice2 == 1)
			{
				cout << "--------------------------------HOME PAGE--------------------------------\n\n";
				timeLineDisplay(indexUser, users[indexUser]);
				cout << "-------------------------------------------------------------------------\n\n";
				cout << "===============================\n";
				//cout << "	FUNCTIONALITY\n\n";
				cout << "1. Show Home Page\n\n";
				cout << "2. Show Friend list\n\n";
				cout << "3. Show Liked Pages\n\n";
				cout << "4. Show Page Timeline\n\n";
				cout << "5. Show User Timeline\n\n";
				cout << "6. Log out\n";
				cout << "===============================\n";
				cout << "Choice: ";
				cin >> choice2;
				//cout << endl;
			}

			else if (choice2 == 2)
			{
				cout << "--------------------------------FRIEND LIST--------------------------------\n\n";
				viewFriends(indexUser);
				cout << "---------------------------------------------------------------------------\n\n";
				cout << endl;
				cout << "===============================\n";
				//cout << "	FUNCTIONALITY\n\n";
				cout << "1. Show Home Page\n\n";
				cout << "2. Show Friend list\n\n";
				cout << "3. Show Liked Pages\n\n";
				cout << "4. Show Page Timeline\n\n";
				cout << "5. Show User Timeline\n\n";
				cout << "6. Log out\n";
				cout << "===============================\n";
				cout << "Choice: ";
				cin >> choice2;
				//cout << endl;
			}

			else if (choice2 == 3)
			{
				cout << "--------------------------------LIKED PAGES--------------------------------\n\n";
				viewLikedPages(indexUser);
				cout << "---------------------------------------------------------------------------\n\n";
				cout << "===============================\n";
				//cout << "	FUNCTIONALITY\n\n";
				cout << "1. Show Home Page\n\n";
				cout << "2. Show Friend list\n\n";
				cout << "3. Show Liked Pages\n\n";
				cout << "4. Show Page Timeline\n\n";
				cout << "5. Show User Timeline\n\n";
				cout << "6. Log out\n";
				cout << "===============================\n";
				cout << "Choice: ";
				cin >> choice2;
				//cout << endl;
			}

			else if (choice2 == 4)
			{
				ViewPage();
				//cout << endl;
				cout << "===============================\n";
				cout << "1. Show Home Page\n\n";
				cout << "2. Show Friend list\n\n";
				cout << "3. Show Liked Pages\n\n";
				cout << "4. Show Page Timeline\n\n";
				cout << "5. Show User Timeline\n\n";
				cout << "6. Log out\n";
				cout << "===============================\n";
				cout << "Choice: ";
				cin >> choice2;
			}

			else if (choice2 == 5)
			{
				viewUserTimeline(users[indexUser]);
				cout << "===============================\n";
				cout << "1. Show Home Page\n\n";
				cout << "2. Show Friend list\n\n";
				cout << "3. Show Liked Pages\n\n";
				cout << "4. Show Page Timeline\n\n";
				cout << "5. Show User Timeline\n\n";
				cout << "6. Log out\n";
				cout << "===============================\n";
				cout << "Choice: ";
				cin >> choice2;

			}
			else if (choice2 == 6)
			{
				cout << "Log out Successful!! Good Bye!\n\n";
				system("pause");
				break;
			}
			else
			{
				cout << "Invalid choice, choose again!!\n\n";
				cout << "Choice: ";
				cin >> choice2;
			}
		}
	}
	system("pause");
}
//=============================================== PAGES CLASS ======================================================\\

Page::Page()
{
	title = " ";
	ID = " ";
	totalPages = 0;
}

void Page::loadFromPages(ifstream& file)
{
	file >> ID;
	getline(file,title);
}

string Page::getID()
{
	return ID;
}

string Page::getTitle()
{
	return title;
}

void Page::addSharedPost(Post* post)
{
	sharedPosts.push_back(post);
}

void Page::addLikedPost(Post* post)
{
	likedPosts.push_back(post);
}

vector<Post*> Page::getSharedPosts()
{
	return sharedPosts;
}
//=============================================== POSTS CLASS ======================================================\\

Post::Post()
{
	activity = 0;
	postID = " ";
	text = " ";
	totalPosts = 0;
}

Post::Post(string id, string t, int tp, int a)
{
	cout << "Parametrized constructor of Users() called\n\n";
	postID = id;
	text = t;
	totalPosts = tp;
	activity = a;
}

Post::~Post()
{
	//cout << "Destructor for Post() called\n";
	
}

void Post::loadFromPosts(ifstream& file)
{
	string str;
	file >> postID;
	file >> str;
	date = stoi(str);
	file >> str;
	month = stoi(str);
	file >> str;
	year = stoi(str);
	string a, b;
	file >> a;
	getline(file, b);
	text = a + b;
}

void Post::addSharedBy(User* users)
{
	sharedBy.push_back(users);
}

void Post::addSharedBy(Page* page)
{
	shared.push_back(page);
}

void Post::addlikedby(User* users)
{
	likedBy.push_back(users);
}

void Post::addComment(Comments* c)
{
	comment.push_back(c);
}
void Post::addlikedby(Page* page)
{
	likedPost.push_back(page);
}
string Post::getPostIDd()
{
	return postID;
}

vector<User*> Post::getSharedBy(int a)
{
	return sharedBy;
}

vector<Page*> Post::getSharedBy()
{
	return shared;
}
string Post::getText()
{
	return text;
}

string Post::getPostBy()
{
	return postBy;
}

void Post::setActivity(int a)
{
	activity = a;
}

int Post::getActiviti()
{
	return activity;
}

void Post::setPostBy(string str)
{
	postBy = str;
}

vector<Comments*> Post::getComments()
{
	return comment;
}

vector<User*> Post::getLikedBy()
{
	return likedBy;
}
//=============================================== COMMENTS CLASS ======================================================\\
		   
Comments::Comments()
{
	ID = " ";
	totalComments = 0;
}

Comments::~Comments()
{
	//cout << "Destructor for Comments() called\n\n";
}

void Comments::loadFromComments(ifstream& file)
{
	file >> ID;
}

void Comments::addPosts(Post* post)
{
	onPost.push_back(post);
}

void Comments::addUser(User* user)
{
	byUser.push_back(user);
}

void Comments::addPage(Page* pages)
{
	byPage.push_back(pages);
}

string Comments::getText()
{
	return comm;
}


string Comments::getCommentBy()
{
	return commentBy;
}

void Comments::setCommentBy(string str)
{
	commentBy = str;
}

void Comments::setComment(string str)
{
	comm = str;
}


//=============================================== ACTIVITY CLASS ======================================================\\

Activity::Activity()
{
	activity = 0;
	act = " ";
	totalActivities = 0;
}

void Activity::loadFromActivity(ifstream& file, string str)
{
	file >> str;
	activity = stoi(str);
	getline(file, act);
}

void Activity::addPostPtr(Post* post)
{
	ptr.push_back(post);
}

int Activity::getActivity()
{
	return activity;
}