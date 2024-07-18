#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class User;
class Page;
class Post;
class Date;
class Comments;
using namespace std;
//================================================\\

class Date
{
protected:
	int currentDate;
	int currentMonth;
	int currentYear;
	int date;
	int month;
	int year;

public:
	Date();
	~Date();
	void setDate(int);
	void setMonth(int);
	void setYear(int);
	int getDate();
	int getMonth();
	int getYear();
};
//================================================\\

class Activity
{
protected:
	int activity;
	vector <Post*> ptr;
	string act;
	int totalActivities;

public:
	Activity();
	void loadFromActivity(ifstream&,string);
	void addPostPtr(Post*);
	int getActivity();
};

//================================================\\

class Page
{
protected:
	int totalPages;
	string ID;
	string title;
	vector<Post*> sharedPosts;
	vector <Post*> likedPosts;

public:
	Page();
	string getID();
	string getTitle();
	void addSharedPost(Post*);
	void addLikedPost(Post*);
	vector<Post*> getSharedPosts();
	void loadFromPages(ifstream&);
};
//================================================\\

class Post:public Date
{
protected:
	string postID;
	string text;
	int totalPosts;
	string postBy;
	int activity;
	vector<User*> sharedBy;
	vector<User*> likedBy;
	vector<Page*> shared;
	vector<Page*> likedPost;
	vector<Comments*> comment;
public:
	Post();
	Post(string, string, int,int);
	string getPostIDd();
	void loadFromPosts(ifstream&);
	virtual void addSharedBy(User*);
	virtual void addlikedby(User*);
	void addComment(Comments*);
	void addSharedBy(Page*);
	void addlikedby(Page*);
	virtual vector<User*> getSharedBy(int);
	vector<Page*> getSharedBy();
	string getText();
	string getPostBy();
	void setActivity(int);
	int getActiviti();
	void setPostBy(string);
	vector<Comments*> getComments();
	vector<User*> getLikedBy();
	
	~Post();
};
//================================================\\

class User
{
protected:
	string id;
	string fname;
	string lname;
	string password;
	int friendCount;
	vector <User*> friends;
	vector <string> friendsID;
	vector <string> pagesID;
	vector <Page*> likedPages;
	vector<Post*> sharedPosts;
	vector<Post*> likedPosts;
	vector <Comments*> comment;
public:
	User();
	~User();
	void loadFromUser(ifstream&);
	string getFname();
	string getLname();
	virtual string getID();
	void addFriendID(string);
	void addFriend(User*);
	void addPageID(string);
	void addPage(Page*);
	void addLikedPosts(Post*);
	void addSharedPosts(Post*);
	void addComments(Comments*);
	vector<User*> getFriends();
	vector<Page*> getPage();
	vector<Post*> getLikedPost();
	vector<Post*> getSharedPost();
	vector<string> getFriendID();
	vector<string> getPageID();
	void addPassword(string);
	string getPassword();
};
//================================================\\

class Comments
{
protected:
	string ID;
	int totalComments;
	string comm;
	string commentBy;
	vector<Post*> onPost;
	vector<User*> byUser;
	vector<Page*> byPage;

public:
	Comments();
	~Comments();
	void loadFromComments(ifstream&);
	void addPosts(Post*);
	void addUser(User*);
	void addPage(Page*);
	string getCommentBy();
	void setCommentBy(string);
	void setComment(string);
	string getText();
};
//================================================\\

class Facebook:public User,Post,Page,Comments,Activity
{
protected:
	vector<User*> users;
	vector<Page*> pages;
	vector<Post*> posts;
	vector<Comments*> comments;
	vector<Activity*> activ;
	int totalUsers;
	
public:
	Facebook();
	~Facebook();
	void load();
	void loadPassword();
	void loadPosts();
	void loadPages();
	void loadComments();
	void loadActivity();
	void Functionality();
	void postFunctionality(vector<Comments*>&,Post*,User*);
	void addAComment(Post*,	User*,vector<Comments*>&);
	void addLikes(Post*,User*);
	void timeLineDisplay(int, User*);
	void ViewPage();
	void viewUserTimeline(User*);
	void viewFriends(int);
	void viewLikedPages(int);
	void viewLikedBy(Post*&);
	void viewComments(vector<Comments*>);
	int getTotalUsers();	
};
//================================================\\

//================================================\\

class StringHelper
{
public:
	virtual int Compare(vector<User*>, string, int);
	int Compare(vector<Page*>, string, int);
	int Compare(vector<Post*>, string, int);
};
//================================================\\

//================================================\\
