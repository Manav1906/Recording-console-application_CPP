#include "opencv2/opencv.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <time.h>
#include <stdio.h>
using namespace cv;
using namespace std;
vector<string> ls; /// list of videos recorded
int c = 0;
string file_path;
int fl = 0;
map<string, int> data_username;
map<string, string> Password;

void gausian_blur(Mat& image, Mat& frame_res) {
    GaussianBlur(image, frame_res, Size(7, 7), 1);
}


void video_rec() {
    time_t start, end;
    VideoCapture vcap(0, CAP_DSHOW);
    if (!vcap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return;
    }
    vcap.set(CAP_PROP_FRAME_WIDTH, 640);
    vcap.set(CAP_PROP_FRAME_WIDTH, 480);
    //int frame_width = vcap.get(CAP_PROP_FRAME_WIDTH);
    //int frame_height = vcap.get(CAP_PROP_FRAME_HEIGHT);

  
    string file_name = "Record_";
    //cout << "Name Of Video-" << endl;
   // cin >> file_name;
    char video_count = char('0' + c);
    file_name += video_count;
    file_name += ".avi";
    file_name = file_path + "\\" + file_name;


    VideoWriter video(file_name, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480), false);
    ls.push_back(file_name);


    //starting time
    time(&start);

    map<int, int> M;
    for (;;) {

        Mat frame;
        vcap >> frame;

        char c = (char)waitKey(33);
        if (c == 27) break;
        Mat fr = frame;
        gausian_blur(frame, fr);
        //seperating channels 
        vector<Mat> rgb;
        split(fr, rgb);
        // 2 is the red channel


      // frame = frame_res;

        video.write(rgb[2]);
        imshow("Frame", rgb[2]);

        //Current Time
        time(&end);
        double dif = difftime(end, start);
        M[dif]++;
        if (M[dif] == 1)cout << "time--> " << dif << "s" << endl;

        if (dif == 10)
        {
            cout << "DONE!!!" << endl;
            vcap.release();
            video.release();
            destroyAllWindows();
            break;
        }
    }
}


bool login() {

    if (fl > 0) {
        cout << "Do you want to login again?(Y/N) " << endl;
        char again = 'Y';
        cin >> again;
        while (again != 'Y' && again != 'N') {
            cout << "INVALID Answer Enter (Y) for Yes or (N) for NO" << endl; cin >> again;
        }
        if (again == 'N') {
            cout << "Thanks for using" << endl << "You're logged out successfully" << endl;
            return 0;
        }
    }
    if (fl==0) {
        cout << "You are a New User, Please Set Your User Name and Password." << endl;
        string usr, paswd;
        cout << "Set your UserName-";
        cin >> usr;
        cout << "Set your Password-";
        cin >> paswd;
        data_username[usr]++;
        Password[usr] = paswd;
        fl++;
        cout << "Now you can login" << endl;
    }
    string userName;
    string userPassword;
    int loginAttempt = 0, f = 0;
    while (loginAttempt < 5)
    {
        cout << "Please enter your user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;

        if (Password[userName] == userPassword)
        {
            cout <<"Hello "<< userName << "!!\n"; f = 1;
            break;
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate.";
        return 0;
    }
    return f;
}


int main() {
    char s = 'Y';
    while (1) {
        if (s=='Y' && !login()) {
            return 0;
        }
        cout << "Do you want to record your video?(Y/N)" << endl;
        char ans = 'Y';
        cin >> ans;
        while (ans != 'Y' && ans != 'N') {
            cout << "INVALID Answer Enter (Y) for Yes or (N) for NO" << endl; cin >> ans;
        }
        while (ans == 'Y') {
            c++;//video no.
            if (c == 1) {
                string p = "(Ex-C:\\Users\\user\\Desktop\\Manav_Prajapat)";
                cout << "Enter the path where you want the video to be stored"<<endl<<p<<endl;
                cin >> file_path;
            }
            video_rec();
            cout << "Was'nt that good?"<<endl<<"Do you want to record another one?(Y/N)" << endl;
            cin >> ans;
            while (ans != 'Y' && ans != 'N') {
                cout << "INVALID Answer Enter (Y) for Yes or (N) for NO" << endl; cin >> ans;
            }
        }
        if (ls.empty()) {
            cout<<"You have'nt recorded any video yet !!"<<endl;
        }
        else {
            cout << "Here is the list of paths of videos recorded by you till now-->" << endl;
            for (auto i : ls) {
                cout << i << endl;
            }
        }
        //logout();
        cout << "Do you want to logout(Y/N)?" << endl;
        cin >> s;
        while (s != 'Y' && s != 'N') {
            cout << "INVALID Answer Enter (Y) for Yes or (N) for NO" << endl; cin >> s;
        }
    }
}