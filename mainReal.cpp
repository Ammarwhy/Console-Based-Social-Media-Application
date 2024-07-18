#include <iostream>
#include "header.h"
#include <Windows.h>
using namespace std;

int main()
{
    try {
       
        unique_ptr<Facebook> fb = make_unique<Facebook>();

        fb->load();
        fb->loadPassword();
        fb->loadPages();
        fb->loadPosts();
        fb->loadComments();
        fb->loadActivity();
        fb->Functionality();
    }
    catch (const exception& ex) {
        cerr << "An error occurred: " << ex.what() << endl;
        return 1;
    }

    return 0;
}