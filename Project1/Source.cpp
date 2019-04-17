// include the librealsense C++ header file
#include <librealsense2/rs.hpp>
#include <librealsense2/h/rs_frame.h>
// include OpenCV header file
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


String IR_Frame = "IR image whit colorization";
String Depth_Frame = "Depth image whit colorization";
String RGB_Frame = "RGB image";



int main()
{

	//Contruct a pipeline which abstracts the device
	rs2::pipeline pipe;
	//Construting a handel for colors on depth image
	rs2::colorizer color_map;

	rs2::align align_to(RS2_STREAM_DEPTH);

	//Construting a obejct to hold the configrations
	rs2::config cfg;

	// Use a configuration object to request only depth from the pipeline 
	// What to stream, ratio of image, format i.e 8bit / 16bit and the framerate
	
	
	cfg.enable_stream(RS2_STREAM_GYRO);
	cfg.enable_stream(RS2_STREAM_ACCEL);
	cfg.enable_stream(RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, 30);
	cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
	cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
	
	//Instruct pipeline to start streaming with the requested configuration
	pipe.start(cfg);

	namedWindow(IR_Frame, WINDOW_AUTOSIZE);
	namedWindow(Depth_Frame, WINDOW_AUTOSIZE);
	namedWindow(RGB_Frame, WINDOW_AUTOSIZE);


	while (waitKey(1) < 0)
	{
		// Wait for next set of frames from the camera
		rs2::frameset data = pipe.wait_for_frames();


		// Getting frames from d435i
		
		rs2::frame ir_frame = data.get_infrared_frame();
		rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
		rs2::frame RGB = data.get_color_frame();
		
		// Find and retrieve IMU 
		rs2::motion_frame accel_frame = data.first_or_default(RS2_STREAM_ACCEL);
		rs2::motion_frame gyro_frame = data.first_or_default(RS2_STREAM_GYRO);
		rs2_vector accel_sample = accel_frame.get_motion_data();
		rs2_vector gyro_sample = gyro_frame.get_motion_data();
			

		
		// Query frame size (width and height)
		const int w = ir_frame.as<rs2::video_frame>().get_width();
		const int h = ir_frame.as<rs2::video_frame>().get_height();
		// Create OpenCV matrix of size (w,h) from the colorized depth data
		Mat IRimg(Size(w, h), CV_8UC1, (void*)ir_frame.get_data(), Mat::AUTO_STEP);

		const int w1 = depth.as<rs2::video_frame>().get_width();
		const int h1 = depth.as<rs2::video_frame>().get_height();
		
		Mat Depthimg(Size(w1, h1), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
		

		const int w2 = RGB.as<rs2::video_frame>().get_width();
		const int h2 = RGB.as<rs2::video_frame>().get_height();

		Mat RGBimg(Size(w2, h2), CV_8UC3, (void*)RGB.get_data(), Mat::AUTO_STEP);
		
		// applying color to IR image
		applyColorMap(IRimg, IRimg, COLORMAP_JET);

		//Put our code here
		
		
		// Update the window with new data
		
		imshow(IR_Frame, IRimg);
		imshow(Depth_Frame, Depthimg);
		imshow(RGB_Frame, RGBimg);
	}
	waitKey(0);

	return 0;
}
