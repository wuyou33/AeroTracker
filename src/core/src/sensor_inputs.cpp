
#include <ros/ros.h>
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. Refer to: http://www.ros.org/doc/api/sensor_msgs/html/namespacesensor__msgs_1_1image__encodings.html for more info.
#include <sensor_msgs/image_encodings.h>
//Include headers for OpenCV Image processing
#include <opencv2/imgproc/imgproc.hpp>
//Include headers for OpenCV GUI handling
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <core/Camera_msgs.h>


using namespace cv; 
 
//Store all constants for image encodings in the enc namespace to be used later.
namespace enc = sensor_msgs::image_encodings;
 
//Declare a string with the name of the window that we will create using OpenCV where processed images will be displayed.
static const char WINDOW[] = "Image Processed";
 
//Use method of ImageTransport to create image publisher
image_transport::Publisher pub;
ros::Publisher camera_pub;
// coordinates
int lastX = 0;
int lastY = 0;


// Get Binary Image 
cv::Mat GetThresholdedImage(cv::Mat& imgHSV){       
    cv::Mat imgThresh(imgHSV.size(),CV_8UC1);
    cv::inRange(imgHSV, Scalar(77,160,60), Scalar(130,256,256), imgThresh); 
    return imgThresh;
}


// finding the centroid of the object

void getCentroid(cv::Mat& img, cv::Mat& track)
{
    int x,y; 
    cv::Size s(img.size());
    cv::Mat  gr_img(img.size(),CV_8UC1);
    cv::Mat temp= cv::Mat::zeros(img.size(),CV_8UC3);
    cvtColor(img,gr_img,CV_BGR2GRAY,1);
    cv::Moments mm = cv::moments(gr_img,false);
    double moment10 = mm.m10;
    double moment01 = mm.m01;
    double moment00 = mm.m00;
     x = int(moment10 / moment00);
     y = int(moment01 / moment00);
     
     if(lastX>=0 && lastY>=0 && x>=0 && y>=0)
     {
        
        //cv::line(temp, cv::Point(x, y), cv::Point(s.width/2, s.height/2), cv::Scalar(0,255,0), 2,8);
        //cv::line(temp, cv::Point(x, y), cv::Point(lastX, lastY), cv::Scalar(0,0,255), 2,8);
    	  lastX =x;
    	  lastY = y;
        ROS_INFO("center x: %d y: %d  image Center x: %d  y:%d",(s.width/2),  (s.height/2), x, y);
     }
      cv::add(temp,track,track);

    return;
}


static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

cv::Mat findSquare(cv::Mat& img )
{
    vector<vector<Point> > squares;
    vector<vector<Point> > contours;
     vector<Point> approx;
      
     squares.clear();
    Canny(img, img, 30, 100, 5);  
    findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    cv::Mat drawing= cv::Mat::zeros(img.size(),CV_8UC3);
    
     for( size_t i = 0; i < contours.size(); i++ )
     {
         approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
         if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                     double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }
                     if( maxCosine < 0.3 ){
                        squares.push_back(approx);
                       
                        drawContours( drawing, contours, i, Scalar(170,255,60), 2, 8,noArray(),0, Point() );
                        break;
                        }
                }
     } 
     
     
     
     for( size_t j = 0;j < squares.size(); j++ )
    {
        const Point* p = &squares[j][0];
        int n = (int)squares[j].size();
        polylines(img, &p, &n, 1, true, Scalar(255,255,255), 3, CV_AA);
    }     
     
   return drawing;
}
//This function is called everytime a new image is published
void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{
    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat hsv_image; 
    try
    {
        //Always copy, returning a mutable CvImage
        //OpenCV expects color images to use BGR channel order.
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        //if there is an error during conversion, display it
        ROS_ERROR("core::main.cpp::cv_bridge exception: %s", e.what());
        return;
    }
     
    
   
      static cv::Mat tracker = cv::Mat::zeros(cv_ptr->image.size(),CV_8UC3);
      cv::cvtColor(cv_ptr->image, hsv_image, CV_BGR2HSV);
      hsv_image = GetThresholdedImage(hsv_image);
      GaussianBlur(hsv_image,hsv_image,Size(3,3),0,0);
      
       hsv_image= findSquare(hsv_image);
       getCentroid(hsv_image,tracker);
            
      cv::add(hsv_image,tracker,hsv_image);
       //cv_ptr->image=hsv_image;
     cv::add(cv_ptr->image,hsv_image,cv_ptr->image);
     
    //Display the image using OpenCV
    cv::imshow(WINDOW, cv_ptr->image);
    //Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
    cv::waitKey(3);
    /**
    * The publish() function is how you send messages. The parameter
    * is the message object. The type of this object must agree with the type
    * given as a template parameter to the advertise<>() call, as was done
    * in the constructor in main().
    */
    //Convert the CvImage to a ROS image message and publish it on the "camera/image_processed" topic.
       // pub.publish(cv_ptr->toImageMsg());
       core::Camera_msgs message;
       cv::Size s(hsv_image.size());
       message.center_x= int(s.width/2);
       message.center_y= int(s.height/2);
       message.centroid_x=lastX;
       message.centroid_y=lastY;
       message.time= ros::Time::now();
       camera_pub.publish(message);
}
 
// callback for sonar 
 void sonarCallback(const std_msgs::Int16& msg)//
{
  ROS_INFO("the obstacle distance: [%d]", msg.data);
}
 
/**
* This tutorial demonstrates simple image conversion between ROS image message and OpenCV formats and image processing
*/
int main(int argc, char **argv)
{
    /**
    * The ros::init() function needs to see argc and argv so that it can perform
    * any ROS arguments and name remapping that were provided at the command line. For programmatic
    * remappings you can use a different version of init() which takes remappings
    * directly, but for most command-line programs, passing argc and argv is the easiest
    * way to do it.  The third argument to init() is the name of the node. Node names must be unique in a running system.
    * The name used here must be a base name, ie. it cannot have a / in it.
    * You must call one of the versions of ros::init() before using any other
    * part of the ROS system.
    */
        ros::init(argc, argv, "image_processor");
    /**
    * NodeHandle is the main access point to communications with the ROS system.
    * The first NodeHandle constructed will fully initialize this node, and the last
    * NodeHandle destructed will close down the node.
    */
        ros::NodeHandle nh;
    //Create an ImageTransport instance, initializing it with our NodeHandle.
        image_transport::ImageTransport it(nh);
    //OpenCV HighGUI call to create a display window on start-up.
    cv::namedWindow(WINDOW, CV_WINDOW_AUTOSIZE);
    /**
    * Subscribe to the "camera/image_raw" base topic. The actual ROS topic subscribed to depends on which transport is used. 
    * In the default case, "raw" transport, the topic is in fact "camera/image_raw" with type sensor_msgs/Image. ROS will call 
    * the "imageCallback" function whenever a new image arrives. The 2nd argument is the queue size.
    * subscribe() returns an image_transport::Subscriber object, that you must hold on to until you want to unsubscribe. 
    * When the Subscriber object is destructed, it will automatically unsubscribe from the "camera/image_raw" base topic.
    */
        image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, imageCallback);
        
        ros::Subscriber sub_sonar = nh.subscribe("sonar/sonar_max", 1, sonarCallback);
    //OpenCV HighGUI call to destroy a display window on shut-down.
    cv::destroyWindow(WINDOW);
    /**
    * The advertise() function is how you tell ROS that you want to
    * publish on a given topic name. This invokes a call to the ROS
    * master node, which keeps a registry of who is publishing and who
    * is subscribing. After this advertise() call is made, the master
    * node will notify anyone who is trying to subscribe to this topic name,
    * and they will in turn negotiate a peer-to-peer connection with this
    * node.  advertise() returns a Publisher object which allows you to
    * publish messages on that topic through a call to publish().  Once
    * all copies of the returned Publisher object are destroyed, the topic
    * will be automatically unadvertised.
    *
    * The second parameter to advertise() is the size of the message queue
    * used for publishing messages.  If messages are published more quickly
    * than we can send them, the number here specifies how many messages to
    * buffer up before throwing some away.
    */
        //pub = it.advertise("camera/image_processed", 1);
        camera_pub = nh.advertise<core::Camera_msgs>("tracking_inputs", 1);
    /**
    * In this application all user callbacks will be called from within the ros::spin() call. 
    * ros::spin() will not return until the node has been shutdown, either through a call 
    * to ros::shutdown() or a Ctrl-C.
    */
        ros::spin();
    //ROS_INFO is the replacement for printf/cout.
    ROS_INFO("core::main.cpp::No error.");
 
}