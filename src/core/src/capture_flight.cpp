#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include <opencv2/imgproc/imgproc.hpp>
//Include headers for OpenCV GUI handling
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <core/Camera_msgs.h>

#include <boost/thread.hpp>

using namespace cv;
using namespace std;
using namespace boost;

bool is_recording=true;

// function to record video taken by usb camera
int record_video(VideoWriter &oVideoWriter, VideoCapture &cap){

     namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
     if ( !oVideoWriter.isOpened() ) //if not initialize the VideoWriter successfully, exit the program
      {
	  cout << "ERROR: Failed to write the video" << endl;
	  return -1;
      }
     is_recording=true;
     while (is_recording)
       {
    	 Mat frame;

         bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
          {
    	     cout << "ERROR: Cannot read a frame from video file" << endl;
    	     break;
    	  }

    	 oVideoWriter.write(frame); //writer the frame into the file

    	 imshow("MyVideo", frame); //show the frame in "MyVideo" window
         if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
          {
            cout << "esc key is pressed by user" << endl;
            break;
          }
        }

}

void capture_callback(const std_msgs::Int16& msg)
 {
   if(msg.data == 1)
      is_recording = false;
 }

int record_setup(){
      VideoCapture cap(0); // open the video camera no. 0

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "ERROR: Cannot open the video file" << endl;
        return -1;
    }


   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

   cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

   Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

   VideoWriter oVideoWriter ("MyVideo.avi", CV_FOURCC('P','I','M','1'), 20, frameSize, true); //initialize the VideoWriter object

   record_video(oVideoWriter,cap);
   
   return 0;
   
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
     ros::Subscriber sub = n.subscribe("capture_commands", 1, capture_callback);
     
     thread thread_1 = thread(record_setup);
     thread_1.detach();
    
 
   ros::spin();
   return 0;

 }


