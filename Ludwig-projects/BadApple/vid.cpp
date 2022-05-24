#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <conio.h>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    int i = 0;
    int j = 0;
    Mat frame;
    
    VideoCapture vid("Y:/C++/BadApple/Bad_Apple.mp4", CAP_FFMPEG);

    if (!vid.isOpened())  // check if we succeeded
        cout << "Cannot load video.";

    while (vid.read(frame))
    {
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        vector<vector<int>> pixels(frame.rows, vector<int>(frame.cols));

            for (int yp = 0; yp < frame.rows; ++yp)
            {
                for (int xp = 0; xp < frame.cols; ++xp)
                {
                    pixels[yp][xp] = frame.at<uchar>(yp, xp);
                }
            }

        if (i % 100 == 0)
            cout << i << '\n';
        ++i;

    }


    /*for (auto& p : filesystem::directory_iterator("Y:\\C++\\BadApple\\frames"))
    {
        string path = p.path().string();
        string image_path = samples::findFile(path);
        Mat img = imread(image_path, IMREAD_COLOR);
        if (img.empty())
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
        imshow("Display window", img);

    }*/
    


    /*
    std::string image_path = samples::findFile("Y:/C++/BadApple/frames/0455.png");
    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window*/

    _getch();
    return 0;
}