//#include "opencv/cv.h"
//#include "opencv/cxcore.h"
//#include "opencv/highgui.h"

#include <opencv2/core/types_c.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#if defined(NDEBUG)
#pragma comment (lib, "opencv_world412.lib")
#else
#pragma comment (lib, "opencv_world412d.lib")
#endif

//#if defined(NDEBUG)
//	#pragma comment (lib, "opencv_core2411.lib")
//	#pragma comment (lib, "opencv_imgproc2411.lib")
//	#pragma comment (lib, "opencv_highgui2411.lib")
//	#pragma comment (lib, "opencv_ml2411.lib")
//	#pragma comment (lib, "opencv_video2411.lib")
//	#pragma comment (lib, "opencv_calib3d2411.lib")
//	#pragma comment (lib, "opencv_features2d2411.lib")
//	#pragma comment (lib, "opencv_objdetect2411.lib")
//	#pragma comment (lib, "opencv_contrib2411.lib")
//	#pragma comment (lib, "opencv_legacy2411.lib")
//	#pragma comment (lib, "opencv_flann2411.lib")
//#else
//	#pragma comment (lib, "opencv_core2411d.lib")
//	#pragma comment (lib, "opencv_imgproc2411d.lib")
//	#pragma comment (lib, "opencv_highgui2411d.lib")
//	#pragma comment (lib, "opencv_ml2411d.lib")
//	#pragma comment (lib, "opencv_video2411d.lib")
//	#pragma comment (lib, "opencv_calib3d2411d.lib")
//	#pragma comment (lib, "opencv_features2d2411d.lib")
//	#pragma comment (lib, "opencv_objdetect2411d.lib")
//	#pragma comment (lib, "opencv_contrib2411d.lib")
//	#pragma comment (lib, "opencv_legacy2411d.lib")
//	#pragma comment (lib, "opencv_flann2411d.lib")
//#endif

