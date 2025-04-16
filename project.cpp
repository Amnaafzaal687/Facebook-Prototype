#include<iostream>
#include<fstream>

using namespace std;

class Helper_class;
class page_class;
class user_class;
class facebook_networkingclass;
class Activity_class;
class Date_class;
class Memory_class;
class object_class;
class comment_class;
class post_class;


class Helper_class
{
public:

	// Calculates the length of a Cstring.
	static int to_calculatelength(const char* string)
	{
		if (!string)
			return 0;
		int count = 0;
		for (int i = 0; string[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}

	// Copies the contents of one C string to another.
	static void to_copy(char* str1, const char* str2)
	{
		int l = to_calculatelength(str2);
		for (int i = 0; i < l; i++)
		{
			str1[i] = str2[i];
		}
		str1[l] = '\0';           // Add a null terminator to the end of the destination string.
	}

	// Returns a dynamically allocated copy of a C-style string.
	static char* GetStringFromBuffer(const char* buffer)
	{
		int l = to_calculatelength(buffer);
		char* arr = 0;
		if (l > 0)
		{
			int len = l + 1;
			arr = new char[len];
			// Copy the input string to the new array.
			to_copy(arr, buffer);
		}
		return arr;
	}

	// Compares two C strings lexicographically.
	static int to_comparing(const char* string1, const char* string2)
	{
		// Iterate over the characters in both strings until the end of one is reached.
		int i;
		for (i = 0; string1[i] != '\0' && string2[i] != '\0'; i++)
		{
			if (string1[i] != string2[i]) // If the characters at this position differ, return -1 or 1 based on which is larger.
			{
				if (string1[i] < string2[i])
				{
					return -1;
				}
				else
				{
					return 1;
				}
			}
		}
		if (string1[i] == '\0' && string2[i] == '\0')        // If both strings have been fully compared and are identical, return 0.
		{
			return 0;
		}
		if (string1[i] < string2[i])
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	static char* to_concatenate(const char* string1, char*& string2)
	{
		char* temp_str = 0;
		int len1 = to_calculatelength(string1);
		int len2 = to_calculatelength(string2);
		int p = len1 + len2;
		temp_str = new char[p + 1];
		int i;
		for (i = 0; string1[i] != '\0'; i++)
			temp_str[i] = string1[i];
		int k;
		i = 0;
		for (k = i; string2[i] != '\0'; k++)
		{
			temp_str[k] = string2[i];
			i++;
		}
		temp_str[len1 + len2] = '\0';
		delete[]string2;
		return temp_str;
	}
	static char* int_tochararr(int t)
	{
		int k = t;
		int calculate = 0;
		for(;k > 0;)
		{
			calculate++;
			k = k / 10;
		}
		char* temp_arr = new char[calculate + 1];
		temp_arr[calculate] = '\0';
		for (; t > 0;)
		{
			int l = t % 10;
			temp_arr[--calculate] = l + '0';
			t = t / 10;
		}
		return temp_arr;
	}
	static char* creating_newid(const char* previous, int new_id)
	{
		//converting int type into char array
		char* temp_id = int_tochararr(new_id);
		//concatenating both strings
		char* New_ID = to_concatenate(previous, temp_id);
		//return concatenating char
		return New_ID;
	}
};

class Activity_class
{
private:
	int Type;
	char* value;
public:
	Activity_class();
	Activity_class(int, char*);
	~Activity_class();
	void ReadActivityFromFile(ifstream&);
	void showactivity();
};

Activity_class::Activity_class()
{
	Type = 0;
	value = nullptr;
}
Activity_class::Activity_class(int t, char* val)
{
	Type = t;
	value = Helper_class::GetStringFromBuffer(val);
}

void Activity_class::ReadActivityFromFile(ifstream& fin)
{
	char temp[50];
	fin >> Type;
	fin.getline(temp, 50);
	value = Helper_class::GetStringFromBuffer(temp);
}
void  Activity_class::showactivity()    // Prints the activity to the console
{
	// Check the value of Type and print the corresponding activity type
	if (Type == 1)
		cout << " feeling ";
	if (Type == 2)
		cout << " thinking about ";
	if (Type == 3)
		cout << " making  ";
	if (Type == 4)
		cout << " celebrating ";
	// Print the value of the activity
	cout << value << "  ";

}

Activity_class::~Activity_class()
{
	if (value)
		delete[] value;
}


class Date_class
{
	int date, month, year;
public:
	Date_class();
	Date_class(int, int, int);
	static Date_class CurrentDate;
	static void SetCurrentDate(int, int, int);
	static bool tocompare(Date_class);
	static int datediff(Date_class);
	void showdate();
	void ReadDateFromFile(ifstream&);
};

Date_class::Date_class()
{
	date = month = year = 0;
}

Date_class::Date_class(int d, int m, int y)
{
	date = d;
	month = m;
	year = y;
}

void Date_class::SetCurrentDate(int da, int mon, int ye)
{
	CurrentDate.date = da;
	CurrentDate.month = mon;
	CurrentDate.year = ye;
}

void Date_class::ReadDateFromFile(ifstream& fin)
{
	fin >> date;
	fin >> month;
	fin >> year;
}

void Date_class::showdate()
{
	cout << "(" << date << "/" << month << "/" << year << ")";
}

bool  Date_class::tocompare(Date_class comparing)       // to compare two dates and check if they are the same or the day before
{
	if (CurrentDate.date == comparing.date || CurrentDate.date - 1 == comparing.date)
	{
		if (CurrentDate.month == comparing.month)
		{
			if (CurrentDate.year == comparing.year)
			{
				return true;
			}
		}
	}
	else
		return false;
}

int Date_class::datediff(Date_class shareddate)            // to calculate the difference in years between two dates
{
	int diff = CurrentDate.year - shareddate.year;
	return diff;
}

Date_class Date_class::CurrentDate;

class object_class     //object class which serves as a base class for other classes
{
private:
	char* id;
public:
	object_class();
	virtual~object_class();
	virtual void addposttotimeline(post_class*) = 0;
	virtual void show_listview() = 0;
	virtual void currentuser() = 0;
	void setID(char*);
	char* getID();
};

object_class::object_class()
{
	id = NULL;
}

void object_class::setID(char* ID)
{
	id = Helper_class::GetStringFromBuffer(ID);
}
char* object_class::getID()
{
	return id;
}

object_class::~object_class()
{
	if (id)
		delete[]id;
}


class comment_class
{
	char* id;
	const char* description;
	object_class* commentor;        // pointer to object class to store commenter object
public:
	static int comment_no;
	comment_class();
	comment_class(const char*, object_class*);
	void setcomments_values(char*, const char*, object_class*);
	~comment_class();
	void showcomments();
};
int comment_class::comment_no = 0;

comment_class::comment_class()
{
	id = nullptr;
	description = nullptr;
	commentor = nullptr;
}
comment_class::comment_class(const char* t, object_class* c)
{
	id = Helper_class::creating_newid("c", ++comment_no);
	description = Helper_class::GetStringFromBuffer(t);
	commentor = c;
}


void comment_class::setcomments_values(char* comID, const char* text, object_class* commentted)
{
	id = Helper_class::GetStringFromBuffer(comID);
	description = Helper_class::GetStringFromBuffer(text);
	commentor = commentted;
}

void comment_class::showcomments()
{
	cout << endl << "\t";
	commentor->currentuser();
	cout << " wrote : (" << description << ")";
}

comment_class::~comment_class()
{
	if (id)
		delete[]id;
	if (description)
		delete[]description;
}

class post_class
{
private:
	int posttype;
	char* postid;
	int likedno;
	int commentno;
	const char* Text_msg;
	Date_class SharedDate;
	Activity_class* activity;                           // The activity associated with the post (if any)
	object_class* SharedBy;
	object_class** LikedBy;                             // The array of objects that liked the post
	comment_class** comments;                           // The array of comments on the post
public:
	static int postno;
	post_class();
	~post_class();
	void readdatafrom_postfile(ifstream&);
	char* getting_postID();
	void setting_sharedby(object_class*);
	void setting_likedby(object_class*);
	const char* gettext_msg();
	void add_comment(comment_class*);
	virtual void showing_postview(bool, bool);             // to show the post view
	Date_class getshareddate();
	object_class* getting_sharedby();                      // to get the object that shared the post
	void viewlikedlist();                                  // Function to view the list of objects that liked the post
	void Setvalues(const char*, post_class*);
};

int post_class::postno = 0;
post_class::post_class()
{
	postid = NULL;
	commentno = likedno = posttype = 0;
	Text_msg = NULL;
	activity = NULL;
	SharedBy = NULL;
	LikedBy = NULL;
	comments = NULL;
}

void post_class::readdatafrom_postfile(ifstream& fin)
{
	char temp[80];
	fin >> posttype;
	fin >> temp;
	postid = Helper_class::GetStringFromBuffer(temp);
	SharedDate.ReadDateFromFile(fin);
	fin.ignore();
	fin.getline(temp, 80);
	Text_msg = Helper_class::GetStringFromBuffer(temp);
	if (posttype == 2)                       //if type is 2 then it means it is activity 
	{                                         //for this we allocate space 
		activity = new Activity_class;
		activity->ReadActivityFromFile(fin);   //read activity 
	}
}

char* post_class::getting_postID()
{
	return postid;
}

void post_class::setting_sharedby(object_class* obj) //to set the shared by
{
	SharedBy = obj;
}
Date_class post_class::getshareddate()               // to get the shared date of the post
{
	return SharedDate;
}
const char* post_class::gettext_msg()
{
	return Text_msg;
}
void post_class::setting_likedby(object_class* obj)    //to set liked by objects
{
	if (likedno == 0 && obj != NULL)
	{
		LikedBy = new object_class * [10];             //if likedpost is zero then allocating space of 10 likes
	}
	if (obj != NULL && likedno < 10)
	{
		LikedBy[likedno] = obj;
		likedno++;
	}
}
void post_class::Setvalues(const char* text, post_class* temp)
{
	postid = Helper_class::creating_newid("post", ++postno);
	SharedBy = temp->SharedBy;
	SharedDate = Date_class::CurrentDate;
	Text_msg = Helper_class::GetStringFromBuffer(text);
}
void post_class::add_comment(comment_class* comment_ptr)// to add a comment to the post
{
	if (commentno == 0 && comment_ptr != NULL)
	{
		comments = new comment_class * [10];              //if commentlist is zero then allocating space of 10 comments
	}
	if (comment_ptr != NULL && commentno < 10)
	{
		comments[commentno] = comment_ptr;
		commentno++;
	}
}

void post_class::showing_postview(bool date_check = true, bool comment_check = true)
{
	cout << endl << "---";
	SharedBy->currentuser();
	if (activity == NULL)               //if activity is 1 like if post is simple then this is printing
	{
		cout << " shared " << Text_msg << "---";
		if (date_check)
			SharedDate.showdate();
	}
	else
	{            // if activity is 2 like if post is activity then this is printing
		cout << " is ";
		activity->showactivity();
		cout << endl << Text_msg << "---";
		if (date_check)
			SharedDate.showdate();
	}
	if (comment_check)
		for (int row = 0; row < commentno; row++)
		{
			comments[row]->showcomments();
		}
	cout << endl;
}

object_class* post_class::getting_sharedby()
{
	return SharedBy;
}
void post_class::viewlikedlist()
{
	cout << "Post liked by : " << endl;
	for (int i = 0; i < likedno; i++)
	{
		LikedBy[i]->show_listview();
	}
}

post_class::~post_class()
{
	if (postid)
		delete[]postid;
	if (Text_msg)
		delete[]Text_msg;
	if (activity)
		delete activity;
	if (LikedBy)
		delete[]LikedBy;
	if (comments) {
		for (int i = 0; (i < commentno) && (i < 10); i++)
		{
			delete comments[i];
		}
		delete[]comments;
	}
}


class Memory_class : public post_class
{
	post_class* original_post;
public:
	Memory_class(const char*, post_class*);
	void showing_postview(bool, bool);           //used when timeline contains memory pointer
};

Memory_class::Memory_class(const char* message, post_class* previous_post)
{
	original_post = previous_post;
	Setvalues(message, previous_post);
}
void Memory_class::showing_postview(bool flag, bool check)
{
	cout << endl << "***";
	getting_sharedby()->currentuser();
	cout << " Shared a memory " << "***";
	getshareddate().showdate();
	cout << endl << gettext_msg() << endl;
	cout << "\t( " << Date_class::datediff(original_post->getshareddate());
	cout << "years ago )" << endl;
	original_post->showing_postview(1, 0);
}

class page_class : public object_class
{
private:
	char* page_Title;
	int timeno;
	post_class** timeline;             // Pointer to an array of post pointers
public:
	page_class();
	void show_listview();             // to display the page ID and title
	void readdatafrom_pagefile(ifstream&);
	~page_class();
	void addposttotimeline(post_class*);
	void currentuser();
	void showing_latestpost(bool);   //to display the home view of the page
	void viewpage();         //to display the page view
};


page_class::page_class()
{
	page_Title = 0;
	timeline = NULL;
	timeno = 0;
}

void page_class::show_listview()
{
	cout << getID() << "-" << page_Title << endl;
}

void page_class::readdatafrom_pagefile(ifstream& fin)
{
	char temp_buffer[50];
	fin >> temp_buffer;
	setID(temp_buffer);
	fin.getline(temp_buffer, 50);
	page_Title = Helper_class::GetStringFromBuffer(temp_buffer);
}

void page_class::currentuser()
{
	cout << page_Title;
}

void page_class::showing_latestpost(bool flag)
{
	if (timeline != NULL)
	{
		for (int row = 0; row < timeno; row++)
		{
			if (Date_class::tocompare(timeline[row]->getshareddate()))
				timeline[row]->showing_postview(flag, 1);
		}
	}
}
void page_class::viewpage()
{
	currentuser();
	cout << "--Timeline" << endl;
	if (timeline != NULL)
	{
		for (int row = 0; row < timeno; row++)
		{
			timeline[row]->showing_postview(1, 1);
			cout << endl;
		}
	}
}
void page_class::addposttotimeline(post_class* timeline_ptr)
{
	if (timeno == 0 && timeline_ptr != NULL)
	{
		timeline = new post_class * [10];              //if timelinelist is zero then allocating space of 10 comments
	}
	if (timeline_ptr != NULL && timeno < 10)
	{
		timeline[timeno] = timeline_ptr;
		timeno++;
	}
}

page_class::~page_class()
{
	if (page_Title)
	{
		delete[]page_Title;
	}
	if (timeline) {
		for (int i = 0; (i < timeno) && (i < 10); i++)
		{
			delete timeline[i];  // Deallocate memory for each post
		}
		delete[]timeline;        // Deallocate memory for the array of post pointers
	}
}


class user_class : public object_class
{
private:
	char* user_firstname;
	char* user_lastname;
	page_class** listof_likedpages;
	user_class** listof_friends;
	int no_likedpages;
	int no_friendlist;
	int time_no;
	post_class** timeline;
public:
	void users_likedpages(page_class*);
	void users_friends(user_class*);
	void showing_friendlist();
	void showing_likedpages();
	void printing_currentuserlistview();
	user_class();
	~user_class();
	void readdatafrom_userfile(ifstream&);
	void show_listview();
	void addposttotimeline(post_class*);
	void currentuser();
	void viewhomepage();
	void showing_latestpost(bool);
	void viewtimeline();
	void seeyourmemory();
	void posting_comment(post_class*, const char*);
};

user_class::user_class()
{
	user_firstname = user_lastname = 0;
	listof_likedpages = NULL;
	listof_friends = NULL;
	no_likedpages = 0;
	time_no = 0;
	no_friendlist = 0;
	timeline = NULL;
}

void user_class::readdatafrom_userfile(ifstream& reading)
{
	char temp_buffer[20];
	reading >> temp_buffer;
	setID(temp_buffer);
	reading >> temp_buffer;
	user_firstname = Helper_class::GetStringFromBuffer(temp_buffer);
	reading >> temp_buffer;
	user_lastname = Helper_class::GetStringFromBuffer(temp_buffer);

}

// Function to add a page to the list of pages a user has liked
void user_class::users_likedpages(page_class* page_ptr)
{
	if (no_likedpages == 0 && page_ptr != NULL)
	{

		listof_likedpages = new page_class * [10];                // Allocate space for 10 pages if the user has not liked any pages yet
	}
	if (page_ptr != NULL && no_likedpages < 10)
	{
		listof_likedpages[no_likedpages] = page_ptr;             // Add the page to the list of liked pages if the list is not full
		no_likedpages++;
	}
}

void user_class::users_friends(user_class* user_ptr)
{
	if (no_friendlist == 0 && user_ptr != NULL) {
		listof_friends = new user_class * [10];                  // Allocate space for 10 friends if the user does not have any friends yet
	}
	if (user_ptr != NULL && no_friendlist < 10) {
		listof_friends[no_friendlist] = user_ptr;                // Add the user to the list of friends if the list is not full
		no_friendlist++;
	}
}

void user_class::showing_friendlist()
{
	cout << "\n___________________________________________________________________________" << endl;
	cout << "Command:          View Friend List " << endl;
	cout << "___________________________________________________________________________" << endl;
	cout << user_firstname << " " << user_lastname << "- Freindlist \n" << endl;
	if (listof_friends == NULL) {
		cout << "You have no friends." << endl;
		return;
	}
	for (int i = 0; i < no_friendlist; i++)
	{
		listof_friends[i]->show_listview();
	}
	cout << "___________________________________________________________________________" << endl;
}

void user_class::showing_likedpages()
{
	cout << "Command:          View liked Pages" << endl;
	cout << "___________________________________________________________________________" << endl;
	cout << user_firstname << " " << user_lastname << "- Liked Pages \n" << endl;
	if (listof_likedpages == NULL) {
		cout << "You haven't liked any pages." << endl;
		return;
	}
	for (int i = 0; i < no_likedpages; i++) {
		listof_likedpages[i]->show_listview();
		cout << endl;
	}
	cout << "___________________________________________________________________________" << endl;
}

void user_class::printing_currentuserlistview()
{
	//printing detailed view of currentuser list 
	showing_friendlist();
	showing_likedpages();
}

void user_class::show_listview()
{
	cout << getID() << " ";
	cout << user_firstname << " " << user_lastname << endl;
}

void user_class::addposttotimeline(post_class* timeline_ptr)
{
	if (time_no == 0 && timeline_ptr != NULL)
	{
		timeline = new post_class * [10];           // If the timeline is empty and the timeline pointer is not null, allocating space for 10 comments
	}
	if (timeline_ptr != NULL && time_no < 10)
	{
		timeline[time_no] = timeline_ptr;           // If the timeline pointer is not null and the time_no is less than 10, adding the pointer to the timeline array
		time_no++;
	}
}

void user_class::posting_comment(post_class* post, const char* comment)
{
	comment_class* commenting = new comment_class(comment, this);     //allocate space 
	post->add_comment(commenting);             //adding comment in post
}
void user_class::viewtimeline()
{
	bool flag = true;
	currentuser();
	cout << "--Timeline " << endl;
	if (timeline != NULL)
	{
		for (int row = 0; row < time_no; row++)
		{
			timeline[row]->showing_postview(flag, 1);
		}
	}
}

void user_class::currentuser()
{
	cout << user_firstname << " " << user_lastname;
}

void  user_class::showing_latestpost(bool flag)
{
	if (timeline != NULL)
	{
		for (int row = 0; row < time_no; row++)
		{
			if (Date_class::tocompare(timeline[row]->getshareddate()))
				timeline[row]->showing_postview(flag, 1);
		}
	}
}

void user_class::viewhomepage()
{
	currentuser();
	cout << "- Home Page \n ";
	bool flag = false;
	if (listof_friends)
	{
		for (int row = 0; row < no_friendlist; row++)
		{
			listof_friends[row]->showing_latestpost(flag);
		}
	}
	if (listof_likedpages)
	{
		for (int row = 0; row < no_likedpages; row++)
		{
			listof_likedpages[row]->showing_latestpost(flag);
		}
	}
}

void  user_class::seeyourmemory()
{
	cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl << endl;
	int diff = 0;
	if (timeline != NULL)
	{
		for (int row = 0; row < time_no; row++)
		{
			if (Date_class::tocompare(timeline[row]->getshareddate()))
			{
				diff = Date_class::datediff(timeline[row]->getshareddate());
				if (diff > 0)
				{
					cout << "On this date ";
					cout << endl;
					cout << diff << " years ago " << endl;
					timeline[row]->showing_postview(1, 1);
				}
			}
		}
	}
}

user_class::~user_class()
{
	if (user_firstname)
	{
		delete[]user_firstname;
	}
	if (user_lastname)
	{
		delete[]user_lastname;
	}
	if (listof_likedpages)
	{
		delete[] listof_likedpages;
	}
	if (listof_friends)
	{
		delete[] listof_friends;
	}
	if (timeline) {
		for (int i = 0; (i < time_no)&&(i<10); i++)
		{
			if (timeline[i])
				delete timeline[i];     // Deallocate memory for each post
		}
		delete[]timeline;               // Deallocate memory for the array of post pointers
	}
}


class facebook_networkingclass
{
	page_class** pages;
	user_class** users;
	post_class** post;
	int total_pagesno;
	int total_usersno;

public:

	//functions to find page,user,post and object drom ID
	page_class* pageFinding_byID(const char*);
	user_class* userFinding_byID(const char*);
	post_class* postFinding_byID(const char*);
	object_class* objectFinding_byID(const char*);

	//loading functions
	void fetching_pagesfromfile(const char*);
	void fetching_userfromfile(const char*);
	void fetching_postsfromfile(const char*);
	void fetching_commentsfromfile(const char*);

	facebook_networkingclass();
	void  show_Posts(post_class*);
	void show_memory(post_class*, const char*);
	void running();                                    //that load pagesfrom file and userfrom file
	void printing();                                   //that print home page and different commands from user
	~facebook_networkingclass();

};

facebook_networkingclass::facebook_networkingclass()
{
	pages = NULL;
	users = NULL;
	post = NULL;
	total_pagesno = total_usersno = 0;
}

void facebook_networkingclass::fetching_pagesfromfile(const char* filename)
{
	ifstream pagefile;
	pagefile.open(filename);
	if (pagefile.is_open())
	{
		pagefile >> total_pagesno;
		pages = new page_class * [total_pagesno];           //allocating space 
		for (int i = 0; i < total_pagesno; i++)
		{
			pages[i] = new page_class;
			pages[i]->readdatafrom_pagefile(pagefile);
		}
		pagefile.close();
	}
}

void facebook_networkingclass::fetching_userfromfile(const char* filename)
{
	ifstream userfile;
	userfile.open(filename);
	if (userfile.is_open())
	{
		char*** temp_ptr = nullptr;       //1st initializing to nullptr
		userfile >> total_usersno;
		int j = 0;
		users = new user_class * [total_usersno];
		temp_ptr = new char** [total_usersno];
		for (int p = 0; p < total_usersno; p++)
		{
			users[p] = new user_class;
			users[p]->readdatafrom_userfile(userfile);
			char arrayptr[50];
			arrayptr[0] = NULL;           //1st initializing to null
			temp_ptr[p] = new char* [10];
			int k = 0;
			while (Helper_class::to_comparing(arrayptr, "-1") != 0)             //running loop until -1 
			{
				userfile >> arrayptr;
				temp_ptr[p][k] = Helper_class::GetStringFromBuffer(arrayptr);
				k++;
			}
			temp_ptr[p][k] = NULL;                               //putting null when friendlist is completed
			arrayptr[0] = NULL;
			j = 0;
			while (Helper_class::to_comparing(arrayptr, "-1") != 0)    //running loop until -1 
			{
				userfile >> arrayptr;
				page_class* ptr_page = pageFinding_byID(arrayptr);
				users[p]->users_likedpages(ptr_page);
				j++;
			}
			j = 0;
		}

		for (int i = 0; i < total_usersno; i++)
		{
			j = 0;
			while (temp_ptr[i][j] != NULL)
			{                                                   //associating friends
				user_class* Ptr_user = userFinding_byID(temp_ptr[i][j]);
				users[i]->users_friends(Ptr_user);
				j++;
			}
		}

		for (int i = 0; i < total_usersno; i++)                  //deleting 3d pointer
		{
			j = 0;
			for (; temp_ptr[i][j] != NULL; j++)
			{
				delete temp_ptr[i][j];
			}
			delete[] temp_ptr[i];
		}
		delete[] temp_ptr;
	}
	userfile.close();
}

void  facebook_networkingclass::fetching_postsfromfile(const char* filename)
{
	ifstream postfile;
	postfile.open(filename);
	if (postfile.is_open())
	{
		char* id;
		postfile >> post_class::postno;
		post = new post_class * [post_class::postno];
		for (int i = 0; i < post_class::postno; i++)
		{
			char temp_buffer[50];
			post[i] = new post_class;
			post[i]->readdatafrom_postfile(postfile);
			postfile >> temp_buffer;
			id = Helper_class::GetStringFromBuffer(temp_buffer);
			object_class* sharedBy = objectFinding_byID(id);
			post[i]->setting_sharedby(sharedBy);
			sharedBy->addposttotimeline(post[i]);

			postfile >> temp_buffer;
			while (Helper_class::to_comparing(temp_buffer, "-1") != 0)             //running loop until -1 
			{
				object_class* likedby = objectFinding_byID(temp_buffer);
				post[i]->setting_likedby(likedby);
				postfile >> temp_buffer;
			}
		}
	}
	postfile.close();
}

void facebook_networkingclass::fetching_commentsfromfile(const char* filename)
{
	ifstream commentsfile;
	commentsfile.open(filename);
	if (commentsfile.is_open())
	{
		commentsfile >> comment_class::comment_no;
		char* id, * postID, * CommentBy, * text;
		for (int k = 0; k < comment_class::comment_no; k++)
		{
			comment_class* Comment = new comment_class;
			char temp_buffer[80];
			commentsfile >> temp_buffer;
			id = Helper_class::GetStringFromBuffer(temp_buffer);
			commentsfile >> temp_buffer;
			postID = Helper_class::GetStringFromBuffer(temp_buffer);
			post_class* postPtr = postFinding_byID(postID);
			postPtr->add_comment(Comment);
			commentsfile >> temp_buffer;
			CommentBy = Helper_class::GetStringFromBuffer(temp_buffer);
			object_class* commectBy = objectFinding_byID(CommentBy);
			commentsfile.getline(temp_buffer, 80);
			text = Helper_class::GetStringFromBuffer(temp_buffer);
			Comment->setcomments_values(id, text, commectBy);
		}
	}
	commentsfile.close();
}

page_class* facebook_networkingclass::pageFinding_byID(const char* pageID)
{
	for (int i = 0; i < total_pagesno; i++) {
		if (Helper_class::to_comparing(pages[i]->getID(), pageID) == 0) {               //if both are equal then return that page 
			return pages[i];
		}
	}
	return NULL;
}

user_class* facebook_networkingclass::userFinding_byID(const char* userID)
{
	for (int i = 0; i < total_usersno; i++) {
		if (Helper_class::to_comparing(users[i]->getID(), userID) == 0)
		{         //if both are equal then return the user 
			return users[i];
		}
	}
	return NULL;
}

post_class* facebook_networkingclass::postFinding_byID(const char* postID)
{
	for (int i = 0; i < post_class::postno; i++) {
		if (Helper_class::to_comparing(post[i]->getting_postID(), postID) == 0)
		{        //if both are equal then return the post
			return post[i];
		}
	}
	return NULL;
}

object_class* facebook_networkingclass::objectFinding_byID(const char* objID)
{
	if (objID[0] == 'u')
	{           //if both are equal then return the object
		return userFinding_byID(objID);
	}
	else
	{           //if both are equal then return the object
		return pageFinding_byID(objID);
	}
}

void  facebook_networkingclass::show_Posts(post_class* ptr)
{
	//this function adds memory post after last post by allocating new space 
	post_class::postno++;
	int p;
	p = post_class::postno;
	post_class** new_postptr = new post_class * [p];
	for (int i = 0; i < p - 1; i++)
	{
		new_postptr[i] = post[i];
	}
	new_postptr[p - 1] = ptr;
	//deleting previous post 
	delete[]post;
	//copy new_post into post ptr 
	post = new_postptr;
}

void facebook_networkingclass::show_memory(post_class* Previous__post, const char* message)
{
	Memory_class* memory = new Memory_class(message, Previous__post);
	show_Posts(memory);
}
void facebook_networkingclass::running()
{
	//executing files (page,user,post and comment )
	fetching_pagesfromfile("pages.txt");
	fetching_userfromfile("users.txt");
	fetching_postsfromfile("posts.txt");
	fetching_commentsfromfile("comments.txt");
}
void facebook_networkingclass::printing()
{
	const char* ID = "u7";
	user_class* Current__user = userFinding_byID(ID);
	Date_class::SetCurrentDate(15, 11, 2017);
	if (Current__user)

	{
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:           Set current System Date 15 11 2017" << endl;
		cout << "System Date:      ";
		Date_class::CurrentDate.showdate();
		cout << "\n___________________________________________________________________________" << endl;                              //print current view 
		cout << "Command:            Set current user " << ID << endl;
		Current__user->currentuser();
		cout << " successfully set as Current User " << endl;
		Current__user->printing_currentuserlistview();
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:            View home Page" << endl;
		cout << "___________________________________________________________________________" << endl;
		Current__user->viewhomepage();
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:            View TimeLine" << endl << endl;
		Current__user->viewtimeline();
		cout << "___________________________________________________________________________" << endl;
		post_class* Current__post = postFinding_byID("post5");
		cout << "Command:            ViewLikedList(" << Current__post->getting_postID() << ")" << endl << endl;
		Current__post->viewlikedlist();
		cout << "___________________________________________________________________________" << endl;
		object_class* Likedby = objectFinding_byID("u7");
		Current__post->setting_likedby(Likedby);  //about liked post and also about exception 
		cout << "Command:            LikePost(" << Current__post->getting_postID() << ")" << endl;
		cout << "Command :           ViewLikedList(" << Current__post->getting_postID() << ")" << endl << endl;
		Current__post->viewlikedlist();
		cout << "___________________________________________________________________________" << endl;
		Current__post = postFinding_byID("post4");
		Current__user->posting_comment(Current__post, " Good Luck for your Result");
		cout << "Command:            PostComment(" << Current__post->getting_postID() << " Good Luck for your Result)" << endl;
		cout << "Command :           ViewPost(" << Current__post->getting_postID() << ")" << endl << endl;
		Current__post->showing_postview(0, 1);
		cout << "___________________________________________________________________________" << endl;
		Current__post = postFinding_byID("post8");
		Current__user->posting_comment(Current__post, "Thanks for all the wishes.");
		cout << "Command:            PostComment(" << Current__post->getting_postID() << ", Thanks for the wishes)" << endl;
		cout << "Command :           ViewPost(" << Current__post->getting_postID() << ")" << endl << endl;
		Current__post->showing_postview(1, 1);
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:           SeeYourMemories() " << endl;
		Current__user->seeyourmemory();
		cout << "___________________________________________________________________________" << endl;
		Current__post = postFinding_byID("post10");
		show_memory(Current__post, "Never thought I will be specialist in this field");
		cout << "Command:           ShareMemory(" << Current__post->getting_postID() << ", Never thought I will be specialist in this field) " << endl;
		cout << "Command:           View TimeLine" << endl;
		cout << "___________________________________________________________________________" << endl;
		Current__user->addposttotimeline(post[post_class::postno - 1]);
		Current__user->viewtimeline();
		cout << "___________________________________________________________________________" << endl;
		page_class* Current__page = pageFinding_byID("p1");
		cout << "Command:           ViewPage(" << Current__page->getID() << ")" << endl << endl;
		Current__page->viewpage();
		cout << "\n___________________________________________________________________________" << endl;
	}
	else
		cout << "\n User with ID " << ID << " does not exist.";
	ID = "u11";
	Current__user = userFinding_byID(ID);                               //again printing current view of different users
	cout << "Command:            Set current user " << ID << endl;
	Current__user->currentuser();
	cout << " successfully set as Current User " << endl;
	if (Current__user)
	{
		Current__user->printing_currentuserlistview();
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:            View home Page" << endl << endl;
		Current__user->viewhomepage();
		cout << "___________________________________________________________________________" << endl;
		cout << "Command:            View TimeLine" << endl << endl;
		Current__user->viewtimeline();
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
	}
}

facebook_networkingclass::~facebook_networkingclass()
{
	if (pages) {
		for (int i = 0; (i < total_pagesno) && (i < 10); i++)
		{
			delete pages[i];
		}
		delete[] pages;
	}
	if (users) {
		for (int i = 0; (i < total_usersno) && (i < 10); i++)
		{
			delete users[i];
		}
		delete[] users;
	}
	if (post) {
		delete[] post;
	}
}


int main()
{
	facebook_networkingclass obj_fb;
	//loading all txt files
	obj_fb.running();        
	//printing all view including (home,timeline,postliked,commenting,viewing memory 
	obj_fb.printing();
	system("pause");
	return 0;
}