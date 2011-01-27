#include <ntk/camera/kinect_grabber.h>
#include <ntk/camera/rgbd_processor.h>
#include <ntk/utils/opencv_utils.h>

using namespace ntk;
using namespace cv;

int main()
{
  KinectGrabber grabber;
  grabber.initialize();
  // Set camera tilt.
  grabber.setTiltAngle(15);
  grabber.start();

  // Postprocess raw kinect data.
  // Tell the processor to transform raw depth into meters using baseline-offset technique.
  RGBDProcessor processor;
  processor.setFilterFlag(RGBDProcessor::ComputeKinectDepthBaseline, true);

  // OpenCV windows.
  namedWindow("color");
  namedWindow("depth");
  namedWindow("depth_as_color");
  
  // Current image. An RGBDImage stores rgb and depth data.
  RGBDImage current_frame;
  while (true)
  {
    grabber.waitForNextFrame();
    grabber.copyImageTo(current_frame);
    processor.processImage(current_frame);

    // Show the frames per second of the grabber
    int fps = grabber.frameRate();
    cv::putText(current_frame.rgbRef(),
                cv::format("%d fps", fps),
                Point(10,20), 0, 0.5, Scalar(255,0,0,255));

    // Display the color image
    imshow("color", current_frame.rgb());

    // Show the depth image as normalized gray scale
    imshow_normalized("depth", current_frame.depth());

    // Compute color encoded depth.
    cv::Mat3b depth_as_color;
    compute_color_encoded_depth(current_frame.depth(), depth_as_color);
    imshow("depth_as_color", depth_as_color);

    // Enable switching to InfraRead mode.
    unsigned char c = cv::waitKey(10) & 0xff;
    if (c == 'q')
      exit(0);
  }
  
 
  return 0;
}
