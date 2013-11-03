#include "cv.h"
#include "highgui.h"
#include "math.h"

using namespace cv;
double centerx1,centery1,centerx2,centery2,centerx3,centery3,radius1,radius2,radius3;
char* lowerH1;
char* lowerS1;
char* lowerV1;
char* upperH1;
char* upperS1;
char* upperV1;
void Threshold_Demo1(int,void*);
int lowerh1,lowers1,lowerv1,upperh1,uppers1,upperv1;
char* lowerH2;
char* lowerS2;
char* lowerV2;
char* upperH2;
char* upperS2;
char* upperV2;
void Threshold_Demo2(int,void*);
int lowerh2,lowers2,lowerv2,upperh2,uppers2,upperv2;
char* lowerH3;
char* lowerS3;
char* lowerV3;
char* upperH3;
char* upperS3;
char* upperV3;
void Threshold_Demo3(int,void*);
int lowerh3,lowers3,lowerv3,upperh3,uppers3,upperv3;
Mat frame1,frame, edges,sc;
void thresh_callback(int, void* );
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
float botspx,botspy,botspangle,botspradius;

char* Top;
char* Bottom;
char* Left;
char* Right;
void crop(int,void*);
int left=1,right=640,top=1,bottom=480;
int num = 0;

int main(int, char**)
{
    VideoCapture cap(0);
    if(!cap.isOpened()) return -1;

    bool running = true;


        while(running){



        if(num == 0){
        std::cout<<"Color following bot version 1.0"<<std::endl<<std::endl<<std::endl;
        std::cout << "Enter particular numbers to perform specific operations" << std::endl <<std::endl<< "1-to take snapshot for calibration"<< std::endl <<"9-to crop the arena"<<std::endl<< "2-to calibrate bot front color"<< std::endl << "3-to calibrate bot back color "<< std::endl << "4-to calibrate object color" << std::endl;
        std::cout<<"5,6,7-to check center calibration of bot front,back,object color" << std::endl << "8-To start execution of program"<< std::endl;
        std::cin >> num ;
        }


    if(num==1){
            namedWindow("edges",1);
    //for(int i=0;i<2;i++)
    //{

        cap >> frame1;
        //cap::read(frame);
        //cvtColor(frame, edges, CV_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);


        //if(waitKey(30) >= 0)     break;
   // }
     imshow("edges", frame1);
    }
     else if(num==2){
            namedWindow("Trackbars",CV_GUI_EXPANDED);
            createTrackbar( "lowerH1","Trackbars", &lowerh1,255,Threshold_Demo1);
            createTrackbar( "LowerS1","Trackbars", &lowers1,255, Threshold_Demo1 );
            createTrackbar( "LowerV1","Trackbars", &lowerv1,255, Threshold_Demo1 );
            createTrackbar( "upperH1","Trackbars", &upperh1,255,Threshold_Demo1);
            createTrackbar( "upperS1","Trackbars", &uppers1,255, Threshold_Demo1 );
            createTrackbar( "upperV1","Trackbars", &upperv1,255, Threshold_Demo1 );
     }
     else if(num==3){
            namedWindow("Trackbars",CV_GUI_EXPANDED);
            createTrackbar( "lowerH2","Trackbars", &lowerh2,255,Threshold_Demo2);
            createTrackbar( "LowerS2","Trackbars", &lowers2,255, Threshold_Demo2 );
            createTrackbar( "LowerV2","Trackbars", &lowerv2,255, Threshold_Demo2 );
            createTrackbar( "upperH2","Trackbars", &upperh2,255,Threshold_Demo2);
            createTrackbar( "upperS2","Trackbars", &uppers2,255, Threshold_Demo2 );
            createTrackbar( "upperV2","Trackbars", &upperv2,255, Threshold_Demo2 );
     }
     else if(num==4){
            namedWindow("Trackbars",CV_GUI_EXPANDED);
            createTrackbar( "lowerH3","Trackbars", &lowerh3,255,Threshold_Demo3);
            createTrackbar( "LowerS3","Trackbars", &lowers3,255, Threshold_Demo3 );
            createTrackbar( "LowerV3","Trackbars", &lowerv3,255, Threshold_Demo3 );
            createTrackbar( "upperH3","Trackbars", &upperh3,255,Threshold_Demo3);
            createTrackbar( "upperS3","Trackbars", &uppers3,255, Threshold_Demo3 );
            createTrackbar( "upperV3","Trackbars", &upperv3,255, Threshold_Demo3 );
     }
     else if(num == 5){

            cvtColor( frame,sc, CV_BGR2GRAY );
            inRange(frame,Scalar(lowerh1,lowers1,lowerv1),Scalar(upperh1,uppers1,upperv1),sc);
            GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
            vector<Vec3f> circles;
            HoughCircles( sc, circles, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);
            for( size_t i = 0; i < circles.size(); i++ )
            {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                std::cout << cvRound(circles[i][0]) << cvRound(circles[i][1]) <<std::endl;
                *&centerx1 = cvRound(circles[i][0]);
                *&centery1 = cvRound(circles[i][1]);

            // circle center
                circle( sc, center, 3, Scalar(0,255,0), -1, 8, 0 );
   // circle outline
                circle( sc, center, radius, Scalar(0,45,255), 3, 8, 0 );
            }

                imshow( "NewArena", sc );
        }
        else if(num == 6){

            cvtColor( frame,sc, CV_BGR2GRAY );
            inRange(frame,Scalar(lowerh2,lowers2,lowerv2),Scalar(upperh2,uppers2,upperv2),sc);
            GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
            vector<Vec3f> circles;
            HoughCircles( sc, circles, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);
            for( size_t i = 0; i < circles.size(); i++ )
            {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                std::cout << cvRound(circles[i][0]) << cvRound(circles[i][1]) <<std::endl;
                *&centerx2 = cvRound(circles[i][0]);
                *&centery2 = cvRound(circles[i][1]);

            // circle center
                circle( sc, center, 3, Scalar(0,255,0), -1, 8, 0 );
   // circle outline
                circle( sc, center, radius, Scalar(0,45,255), 3, 8, 0 );
            }

                imshow( "NewArena", sc );
        }
        else if(num == 7){

            cvtColor( frame,sc, CV_BGR2GRAY );
            inRange(frame,Scalar(lowerh3,lowers3,lowerv3),Scalar(upperh3,uppers3,upperv3),sc);
            GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
            vector<Vec3f> circles;
            HoughCircles( sc, circles, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);
            for( size_t i = 0; i < circles.size(); i++ )
            {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                std::cout << cvRound(circles[i][0])<< cvRound(circles[i][1]) <<std::endl;
                *&centerx3 = cvRound(circles[i][0]);
                *&centery3 = cvRound(circles[i][1]);

                // circle center
                circle( sc, center, 3, Scalar(0,255,0), -1, 8, 0 );
                // circle outline
                circle( sc, center, radius, Scalar(0,45,255), 3, 8, 0 );
            }

                imshow( "NewArena", sc );
        }
        else if(num == 8){
                for(;;)
                {
                    Rect rect;
                    cap >> frame1;                                  //capture snapshot
                    rect = Rect(left,top,right-left,bottom-top);    //crops the image
                    frame = frame1(rect);


                    cvtColor( frame,sc, CV_BGR2GRAY );
                    inRange(frame,Scalar(lowerh1,lowers1,lowerv1),Scalar(upperh1,uppers1,upperv1),sc);
                    GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
                    vector<Vec3f> circles1;
                    HoughCircles( sc, circles1, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);

                    for( size_t i = 0; i < circles1.size(); i++ )
                    {
                        Point center(cvRound(circles1[i][0]), cvRound(circles1[i][1]));
                        int radius = cvRound(circles1[i][2]);
                       // std::cout << cvRound(circles1[i][0]) << cvRound(circles1[i][1]) <<std::endl;
                        *&centerx1 = cvRound(circles1[i][0]);
                        *&centery1 = cvRound(circles1[i][1]);
                        *&radius1 = cvRound(circles1[i][2]);


                    }


                    cvtColor( frame,sc, CV_BGR2GRAY );
                    inRange(frame,Scalar(lowerh2,lowers2,lowerv2),Scalar(upperh2,uppers2,upperv2),sc);
                    GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
                    vector<Vec3f> circles2;
                    HoughCircles( sc, circles2, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);

                    for( size_t i = 0; i < circles2.size(); i++ )
                    {
                        Point center(cvRound(circles2[i][0]), cvRound(circles2[i][1]));
                        int radius = cvRound(circles2[i][2]);
                       // std::cout << cvRound(circles2[i][0]) << cvRound(circles2[i][1]) <<std::endl;
                        *&centerx2 = cvRound(circles2[i][0]);
                        *&centery2 = cvRound(circles2[i][1]);
                        *&radius2 = cvRound(circles2[i][2]);

                    }



                    cvtColor( frame,sc, CV_BGR2GRAY );
                    inRange(frame,Scalar(lowerh3,lowers3,lowerv3),Scalar(upperh3,uppers3,upperv3),sc);
                    GaussianBlur( sc, sc, Size(9, 9), 2, 2 );
                    vector<Vec3f> circles3;
                    HoughCircles( sc, circles3, CV_HOUGH_GRADIENT, 1, sc.rows/16, 200, 25, 10, 60);

                    for( size_t i = 0; i < circles3.size(); i++ )
                    {
                        Point center(cvRound(circles3[i][0]), cvRound(circles3[i][1]));
                        int radius = cvRound(circles3[i][2]);
                        //std::cout << cvRound(circles3[i][0]) << cvRound(circles3[i][1]) <<std::endl;
                        *&centerx3 = cvRound(circles3[i][0]);
                        *&centery3 = cvRound(circles3[i][1]);
                        *&radius3 = cvRound(circles3[i][2]);
                    }

                    Point center1(centerx1, centery1);
                    circle( frame,center1, 3, Scalar(0,255,0), -1, 8, 0 );    //plot bot front center
                    circle( frame,center1 ,radius1, Scalar(0,255,0), 3, 8, 0 );

                    Point center2(centerx2, centery2);
                    circle( frame,center2, 3, Scalar(0,255,0), -1, 8, 0 );    //plot bot back center
                    circle( frame,center2 ,radius2, Scalar(0,00,255), 3, 8, 0 );

                    Point center3(centerx3, centery3);
                    circle( frame,center3, 3, Scalar(0,255,0), -1, 8, 0 );    //plot object center
                    circle( frame,center3 ,radius3, Scalar(255,00,0), 3, 8, 0 );


                    imshow("current frame",frame);



                    if(circles1.size()!=0 && circles2.size()!=0 && circles3.size()!=0){
                    double distox = centerx2-centerx3;              //calculates object angle
                    double distoy = centery2-centery3;
                    double angleo,angleod;
                    if(distox<0 && distoy >0){
                    distox = distox*-1;
                    angleo = atan(distoy/distox);
                    angleod = angleo*180/3.14;
                    }
                    else if(distox>0 && distoy >0){
                    angleo = atan(distoy/distox);
                    angleod = 180 -(angleo*180/3.14);
                    }
                    else if(distox>0 && distoy <0){
                    distoy = distoy*-1;
                    angleo = atan(distoy/distox);
                    angleod = 180+angleo*180/3.14;

                    }
                    else if(distox<0 && distoy <0){
                    distoy = distoy*-1;
                    distox = distox*-1;
                    angleo = atan(distoy/distox);
                    angleod = 360 -(angleo*180/3.14);
                    }
                        std::cout <<"Orientation of object "<<angleod << std::endl;


                    double distbx = centerx2-centerx1;              //calculates bot angle
                    double distby = centery2-centery1;
                    double angleb,anglebd;
                    if(distbx<0 && distby >0){
                    distbx = distbx*-1;
                    angleb = atan(distby/distbx);
                    anglebd = angleb*180/3.14;
                    }
                    else if(distbx>0 && distby >0){
                    angleb = atan(distby/distbx);
                    anglebd = 180 -(angleb*180/3.14);
                    }
                    else if(distbx>0 && distby <0){
                    distby = distby*-1;
                    angleb = atan(distby/distbx);
                    anglebd = 180+angleb*180/3.14;

                    }
                    else if(distbx<0 && distby <0){
                    distby = distby*-1;
                    distbx = distbx*-1;
                    angleb = atan(distby/distbx);
                    anglebd = 360 -(angleb*180/3.14);
                    }
                        std::cout <<"Orientation of bot "<<anglebd << std::endl;

                    if(angleod>=anglebd){
                            if(anglebd<90 && angleod>270){
                                std::cout<<"Turn right"<< std::endl;
                            }
                            else if(angleod-anglebd<5){
                                int distx = (centerx1-centerx3)*(centerx1-centerx3);
                                int disty = (centery1-centery3)* (centery1-centery3);
                                double dist = sqrt(distx+disty);
                                if(dist<40){
                                    std::cout<<"Stop"<< std::endl;
                                }
                                else{
                                    std::cout<<"Move forward"<<std::endl;
                                }

                        }
                        else{
                        std::cout << "turn left" << std::endl;
                        }
                    }
                    else{
                            if(angleod<90 && anglebd>270){
                                std::cout<<"Turn left"<< std::endl;
                            }
                            else if(anglebd-angleod<5){
                                int distx = (centerx1-centerx3)*(centerx1-centerx3);
                                int disty = (centery1-centery3)* (centery1-centery3);
                                double dist = sqrt(distx+disty);
                                if(dist<40){
                                    std::cout<<"Stop"<< std::endl;
                                }
                                else{
                                    std::cout<<"Move forward"<<std::endl;
                                }

                            }
                            else{
                        std::cout << "Turn right" << std::endl;


                            }
                    }
                }



                     system("CLS");
                    if(waitKey(30) >= 0)     break;
        }


        }
        else if(num==9){
            namedWindow("Trackbars",CV_GUI_EXPANDED);
            createTrackbar( "Top","Trackbars", &top,frame1.rows,crop);
            createTrackbar( "Bottom","Trackbars", &bottom,frame1.rows,crop );
            createTrackbar( "Left","Trackbars", &left,frame1.cols,crop);
            createTrackbar( "Right","Trackbars", &right,frame1.cols,crop);



        }
         system("CLS");
         num = 0;


//}

    waitKey( 1200000 );
    destroyAllWindows();
    }




    return 0;
}
void Threshold_Demo1( int,void*)
{
    namedWindow("NewArena",1);

    inRange(frame,Scalar(lowerh1,lowers1,lowerv1),Scalar(upperh1,uppers1,upperv1),edges);
    *&lowerh1 = lowerh1;
    *&lowers1 = lowers1;
    *&lowerv1 = lowerv1;
    *&upperh1 = upperh1;
    *&uppers1 = uppers1;
    *&upperv1 = upperv1;
    imshow( "NewArena", edges );
}
void Threshold_Demo2( int,void*)
{
    namedWindow("NewArena",1);

    inRange(frame,Scalar(lowerh2,lowers2,lowerv2),Scalar(upperh2,uppers2,upperv2),edges);
    *&lowerh2 = lowerh2;
    *&lowers2 = lowers2;
    *&lowerv2 = lowerv2;
    *&upperh2 = upperh2;
    *&uppers2 = uppers2;
    *&upperv2 = upperv2;
    imshow( "NewArena", edges );
}
void Threshold_Demo3( int,void*)
{
    namedWindow("NewArena",1);

    inRange(frame,Scalar(lowerh3,lowers3,lowerv3),Scalar(upperh3,uppers3,upperv3),edges);
    *&lowerh3 = lowerh3;
    *&lowers3 = lowers3;
    *&lowerv3 = lowerv3;
    *&upperh3 = upperh3;
    *&uppers3 = uppers3;
    *&upperv3 = upperv3;
    imshow( "NewArena", edges );
}
void crop( int,void*)
{
            Rect rect;
            rect = Rect(left,top,right-left,bottom-top);
            *&left = left;
            *&top = top;
            *&right = right;
            *&bottom = bottom;

            frame = frame1(rect);
            imshow("NewArena",frame);
}
void thresh_callback(int, void* )
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using Threshold
   inRange(frame,Scalar(lowerh1,lowers1,lowerv1),Scalar(upperh1,uppers1,upperv1),sc);
   threshold( sc, threshold_output, thresh, 255, THRESH_BINARY );

  /// Find contours
  findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Approximate contours to polygons + get bounding rects and circles
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( size_t i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       float f = 5.00;
       minEnclosingCircle( contours_poly[i], center[i],*&f);
       std::cout << center[i].x << std::endl;
       std::cout << center[i].y << std::endl;
       *&botspx = center[i].x;
       *&botspy = center[i].y;

     }


  /// Draw polygonal contour + bonding rects + circles

  for( size_t i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours_poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
       circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
     }

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}


