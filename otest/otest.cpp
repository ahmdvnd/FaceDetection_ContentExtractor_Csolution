//****Face And Eye detection program codes******
//****Input: Path of Image***** 
//****Output:Text file that contains the coordinates of Faces,Eyes and etc.*********
// otest.cpp : Defines the entry point for the console application.
//******************************************************************************************************************
/** Function Headers */
#include "stdafx.h" 
#include "HD.h"
#include <iostream>
#include <stdio.h>
#include<Windows.h>
using namespace std;
using namespace cv;
#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
#include <cstdlib>
#include <cstdlib> 
#include <fstream>
#include <iostream>
#include <string>
#include <tchar.h>
//#define ColorImage
//********************************************************************************************************************
/**Main Function for Detecting**/
void detectAndDisplay(Mat frame, TCHAR*  FileName, TCHAR* OutputPathProperty, CvSize OutputSize, TCHAR* OutputPathImage);
 //*******************************************************************************************************************
/** Process:{1. Reperesenting XML files  */


String face_cascade_name_default="E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
String face_cascade_name =       "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
String eyes_cascade_name =       "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
String tree_cascadeT_name =      "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
String bigpair_cascadeB_name =   "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
String smallpair_cascadeS_name = "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
String mouth_cascadeM_name =     "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml";
String mcsleft_cascadeMLE_name = "E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
String mcsright_cascadeMRE_name ="E:\\opencv412\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
// End 1}
//***********************************************************************************************************************
/** Process:{2.Defining the Cascade Classifiers as Global variables**/
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier tree_cascadeT;
CascadeClassifier left2split_cascadeL2;
CascadeClassifier bigpair_cascadeB;
CascadeClassifier smallpair_cascadeS;
CascadeClassifier mouth_cascadeM;
CascadeClassifier nose_cascadeN;
CascadeClassifier  right2split_cascadeR2;
CascadeClassifier mcsleft_cascadeMLE;
CascadeClassifier mcsright_cascadeMRE;
//End 2}
//*************************************************************************************************************************
string window_name = "Capture - Face detection";
RNG rng(12345);
//*************************************************************************************************************************

void	RemoveExtention()
{

}

Mat	CannyEdging(Mat src)
{
	Mat canny_out;
	Canny(src, canny_out, 10, 10, 3);

	/*imshow("CANNY", canny_out);	
	waitKey(0);*/
	return	canny_out;
}

Mat	SobleEdging(Mat src)
{
	Mat srcsobel, src_gray;
	Mat grad;
	char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;
	GaussianBlur(src, srcsobel, Size(3, 3), 0, 0, BORDER_DEFAULT);
	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(srcsobel, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(srcsobel, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	//imshow(window_name, grad);	
	return grad;
}


void	Test()
{
	Mat Test;
	Test = imread("E:\\DB\\BioID\\BioID-FaceDatabase-V1.2_2\\BioID_0000.pgm");
	imshow("Test", Test);
	cvWaitKey();

}

/** @function main */
//* Process:{3.Main Function
int main(int argc, const char** argv)
{
	//TestEdging();return 0;
	//Test();
	
	int Canny = 1&0;
	int soble = 1&0;
	int face = 1;
	int RAW = 1 & 0;
	int PPM = 1 & 0;
	int PGM = 1 & 0;
	int Resize =0 & 1;

	cout << argc << " Batch Found \n";
	for (size_t i = 1; i < argc; i++)
	{
		TCHAR	StartPath[_MAX_PATH];
		TCHAR	FinderPath[_MAX_PATH];
		TCHAR	OutputPathProperty[_MAX_PATH];
		TCHAR	OutputPathImage[_MAX_PATH];
		TCHAR	OutputPathCanny[_MAX_PATH];
		TCHAR	OutputPathResize[_MAX_PATH];
		TCHAR	OutputPathsobel[_MAX_PATH];
		TCHAR	ImageExtention [_MAX_PATH];
		//_tcscpy(StartPath, _T("E:\\DB\\Yale\\Yale_facedatabase_B\\CroppedYale\\yaleB01\\"));
		_tcscpy(StartPath, argv[i]);
		_tcscpy(OutputPathImage, argv[i]);
		_tcscpy(OutputPathCanny, argv[i]);
		_tcscpy(OutputPathsobel, argv[i]);
		_tcscpy(OutputPathProperty, argv[i]);
		_tcscpy(OutputPathResize, argv[i]);
		
		_tcscat(OutputPathProperty, _T("\\FacesInfo\\"));
		_tcscat(OutputPathImage, _T("\\CroppedImages\\"));
		_tcscat(OutputPathCanny, _T("\\CannydImages\\"));
		_tcscat(OutputPathsobel, _T("\\SobelImages\\"));
		_tcscat(OutputPathResize, _T("\\ResizedImages\\"));
		
		CreateDirectory(OutputPathProperty, NULL);
		CreateDirectory(OutputPathImage, NULL);
		if(soble)
			CreateDirectory(OutputPathsobel, NULL);
		if(Canny)
			CreateDirectory(OutputPathCanny, NULL);
		if(Resize)
			CreateDirectory(OutputPathResize, NULL);


		_tcscpy(FinderPath, StartPath);
		
		if (RAW)
		{
			_tcscat(FinderPath, _T("\\*.raw"));
			//_tccpy(ImageExtention, ".RAW");
		}
		else if(PPM)
		{
			_tcscat(FinderPath, _T("\\*.ppm"));
		}
		else if (PGM)
		{
			_tcscat(FinderPath, _T("\\*.PGM"));

		}
		else  
		{
			_tcscat(FinderPath, _T("\\*.jpg"));
		}


		
		cout << argv[i] << "\n";
		Mat frame;     //frame is original Input Image from class Mat
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		TCHAR szDir[_MAX_PATH];
		TCHAR dstDir[_MAX_PATH];
		size_t length_of_arg;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		DWORD dwError = 0;
		hFind = FindFirstFile(FinderPath, &ffd); //Path of input image
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
			}
			else
			{
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
				_tcscpy(szDir, StartPath);
				TCHAR*  fn = ffd.cFileName;
				TCHAR FileName[_MAX_PATH] = { 0 };
				memmove(&FileName, ffd.cFileName, strlen(ffd.cFileName) - 4);
				//memmove(&word[idxToDel], &word[idxToDel + 1], strlen(word) - idxToDel);

				_tcscat(szDir, "\\");
				_tcscat(szDir, fn);

				if (RAW)
				{
					FILE *fp = NULL;
					char *imagedata = NULL;
					int imWidth = 768;
					int imHeight = 1728;
					int framesize = imWidth * imHeight;
					CvSize imageSize;
					//Open raw Bayer image.
					fp = fopen(szDir, "rb");

					//Memory allocation for bayer image data buffer.
					imagedata = (char*)malloc(sizeof(char) * framesize);

					//Read image data and store in buffer.
					fread(imagedata, sizeof(char), framesize, fp);

					//Image dimension.
					imageSize.height = imHeight;
					imageSize.width = imWidth;

					//Create Opencv mat structure for image dimension. For 8 bit bayer, type should be CV_8UC1.
					frame.create(imageSize.height, imageSize.width, CV_8UC1);

					memcpy(frame.data, imagedata, framesize);

					free(imagedata);

					fclose(fp);
					//imshow("Test", frame);
					//Perform demosaicing process
					cvtColor(frame, frame, CV_BayerBG2BGR);
					//imshow("Test2", frame);
					//cvWaitKey();

				}
				else
				{
					frame = imread(szDir); //Read Image	
					/*imshow("Frame",frame);
					waitKey();*/
				}
				
				TCHAR FullPath[MAX_PATH];
				if (soble)
				{									
					
					_tcscpy(FullPath,OutputPathsobel);
					_tcscat(FullPath, FileName);
					_tcscat(FullPath, "_");
					_tcscat(FullPath, ".jpg");					
					imwrite(FullPath, SobleEdging(frame));

				}
				if (Canny)
				{
					_tcscpy(FullPath,OutputPathCanny);
					_tcscat(FullPath , FileName);
					_tcscat(FullPath , "_");
					_tcscat(FullPath , ".jpg");
					imwrite(FullPath , CannyEdging(frame));
				}

				if (Resize)
				{
					Mat Resized;
					TCHAR FName[_MAX_PATH];
					_tcscpy(FName, OutputPathResize);
					_tcscat(FName, "\\");
					_tcscat(FName, FileName);
					_tcscat(FName, "_");
					_tcscat(FName, ".jpg");



					resize(frame, Resized, cv::Size(133, 133), 0, 0, INTER_LINEAR);
					imwrite(FName, Resized);

				}

				if (!face)
				{
					continue;
				}

				//******************************************************************************************************************************
					//**Process:{ 3-1. Load the cascades
				//imshow(" ",frame);cvWaitKey();
				if (!face_cascade.load(face_cascade_name_default)) { return -1; };
				if (!face_cascade.load(face_cascade_name)) { return -1; };
				if (!eyes_cascade.load(eyes_cascade_name)) { return -1; };
				if (!mouth_cascadeM.load(mouth_cascadeM_name)) { return -1; };
				if (!tree_cascadeT.load(tree_cascadeT_name)) { return -1; };
				if (!bigpair_cascadeB.load(bigpair_cascadeB_name)) { return -1; };
				if (!smallpair_cascadeS.load(smallpair_cascadeS_name)) { return -1; };
				if (!mcsleft_cascadeMLE.load(mcsleft_cascadeMLE_name)) { return -1; };
				//if (!mcsright_cascadeMRE.load(mcsright_cascadeMRE_name)) { return -1; };

				{ 
					detectAndDisplay(frame, FileName, OutputPathProperty,cv::Size(133,133), OutputPathImage); 
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);
	}
	return 0;
}
 //End 3.1
 //End 3}
 //******************************************************************************************************************************
/** @Detection Function*/
 //**Process:{4.Detection Function
void detectAndDisplay(Mat frame, TCHAR*  FileName, TCHAR* OutputPathProperty,CvSize OutputSize, TCHAR* OutputPathImage)
{
	vector<Rect> faces; //faces from class Rect
	vector<int> rejectLevels;
	vector<double> levelWeights;
	Mat frame_gray;  //frame_gray from class Mat
	Mat frame_resized(cvRound(frame.rows), cvRound(frame.cols), CV_8UC1);
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	resize(frame_gray, frame_resized, frame_resized.size(), 0, 0, INTER_LINEAR);
	//cvNamedWindow( "result", 1 );
	double MinRelDistEye, MaxRelDistEye, ConfScoreThresh;
	//cout<< "Minimum of Relative Distance Between Two Eyes=";
	//cin>>MinRelDistEye; //Minimum of Relative Distance Between Two Eyes for Accepting Face, i.e. The Distance Between Two Eyes Divided By Width of Original Image.
	MinRelDistEye = 0.02;
	MaxRelDistEye = 0.9;
	ConfScoreThresh = 1;
	//cout<< "Maximum of Relative Distance Between Two Eyes=";
	//cin>>MaxRelDistEye;//Maximum of Relative Distance Between Two Eyes for Accepting Face, i.e. The Distance Between Two Eyes Divided By Width of Original Image.
	//cout<< "Confidence Score Threshold For Accepting Faces =";
	//cin>>ConfScoreThresh;//The Confidence Score Threshold for Accepting the Faces  With Low Confidence Scores
	double MinWidth = 2 * MinRelDistEye*frame.cols; //Minimum width of acceptable face in terms of width of image and user input.
	double MinHeight = 3 * MinRelDistEye*frame.cols; //Minimum height of acceptable face in terms of width of image and user input.
	double MaxWidth = 2 * MaxRelDistEye*frame.cols;  //Maximum width of acceptable face in terms of width of image and user input.
	double MaxHeight = 3 * MaxRelDistEye*frame.cols; //Maximum height of acceptable face in terms of width of image and user input.
	//If MinWidth,MinHeight,MaxWidth,MaxHeight larger than width of image.
	if (MinWidth > frame.cols) {
		MinWidth = frame.cols;
	}
	if (MinHeight > frame.cols) {
		MinHeight = frame.cols;
	}
	if (MaxWidth > frame.cols) {
		MaxWidth = frame.cols;
	}
	if (MaxHeight > frame.cols) {
		MaxHeight = frame.cols;
	}
	//************************************************************************************************************************************//
	Size minsize = Size(MinWidth, MinHeight);
	Size maxsize = Size(MaxWidth, MaxHeight);
	//**************************************************************************************************************************************
	//** Process:{4.1. Face Detection Function
	memset(&faces, 0, sizeof(faces));
	memset(&rejectLevels, 0, sizeof(rejectLevels));
	memset(&levelWeights,0, sizeof(levelWeights));
	face_cascade.detectMultiScale(frame_resized, faces);//, rejectLevels, levelWeights);//, 2, ConfScoreThresh, 0 | CASCADE_SCALE_IMAGE, minsize, maxsize);
	//End 4.1}
	   //**************************************************************************************************************************************
	
	TCHAR FacesInfo[_MAX_PATH] = { 0 };
	TCHAR FacesImage[_MAX_PATH] = { 0 };
	_tcscpy(FacesInfo, OutputPathProperty);	
	_tcscat(FacesInfo, FileName);
	_tcscat(FacesInfo, _T(".txt"));
	std::ofstream outdata(FacesInfo);


	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		//ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		Mat faceROI = frame_resized(faces[i]);
		//*************************************************************************************************************************************
			//** Process:{4.2. Mouth Detection Function and applying mouthcascsde classifier
		//std::vector<Rect> mouth;
		//memset(&mouth, 0, sizeof(mouth));
		//mouth_cascadeM.detectMultiScale(faceROI, mouth);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.2}
		//**************************************************************************************************************************************
		//** Process:{4.3. Eye Detection Function and applying eyecascade classifier
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale(faceROI, eyes);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.3}
		//***************************************************************************************************************************************
			//** Process:{4.4. Treeglass  eye Detection Function and applying treeglass_eyecascade classifier
		//std::vector<Rect> tree;
		//tree_cascadeT.detectMultiScale(faceROI, tree);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.4}
		//****************************************************************************************************************************************
		//** Process:{4.5. BigPair eye Detection Function and applying bigpair classifier
		//std::vector<Rect> bigpair;
		//bigpair_cascadeB.detectMultiScale(faceROI, bigpair);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.5}
		//***************************************************************************************************************************************
		//** Process:{4.6. SmallPair eye Detection Function and applying Smallpair classifier
		//std::vector<Rect> smallpair;
		//smallpair_cascadeS.detectMultiScale(faceROI, smallpair);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.6 }
		//***************************************************************************************************************************************
		//**Process:{4.7. Mcsleft eye Detection Function and applying mcsleft classifier
		//std::vector<Rect> mcsleft;
		//mcsleft_cascadeMLE.detectMultiScale(faceROI, mcsleft);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.7}
		//****************************************************************************************************************************************
		//**Process:{4.8. Mcsright eye Detection Function and applying mcsright classifier
		//std::vector<Rect> mcsright;
		//mcsright_cascadeMRE.detectMultiScale(faceROI, mcsright);//, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(faces[i].width*0.1, faces[i].width*0.1));
		//End 4.8}
		//****************************************************************************************************************************************
		//** Process:{4.9. Writing the outputs of all above classifiers in Text Format File
		//Face
		

		outdata << "Face: " << "x= " << faces[i].x << ",y= " << faces[i].y << ",width= " << faces[i].width << ",height= " << faces[i].height << "," << endl;
		if (eyes.size() != 0)
		{
			for (int jj = 0; jj < eyes.size(); jj++)

			{
				outdata << "Eyes: " << "x= " << eyes[jj].x << ",y= " << eyes[jj].y << ",width= " << eyes[jj].width << ",height= " << eyes[jj].height << "," << endl;
			};
		}
		//***************************************************************************************************************************************************
		//Treeglass
		//if (tree.size() != 0)
		//{
		//	for (int jj = 0; jj < tree.size(); jj++)

		//	{
		//		outdata << "Tree: " << "x= " << tree[jj].x << ",y= " << tree[jj].y << ",width= " << tree[jj].width << ",height= " << tree[jj].height << "," << endl;
		//	};
		//}
		////*****************************************************************************************************************************************************
		////MCSLeft
		//if (mcsleft.size() != 0)
		//{
		//	for (int jj = 0; jj < mcsleft.size(); jj++)

		//	{
		//		outdata << "McsLeft: " << "x= " << mcsleft[jj].x << ",y= " << mcsleft[jj].y << ",width= " << mcsleft[jj].width << ",height= " << mcsleft[jj].height << "," << endl;
		//	};

		//}
		////********************************************************************************************************************************************************
		////MCSRight
		//if (mcsright.size() != 0)
		//{
		//	for (int jj = 0; jj < mcsright.size(); jj++)

		//	{
		//		outdata << "McsRight: " << "x= " << mcsright[jj].x << ",y= " << mcsright[jj].y << ",width= " << mcsright[jj].width << ",height= " << mcsright[jj].height << "," << endl;
		//	};

		//}
		////*************************************************************************************************************************************************************
		// //BigPair
		//if (bigpair.size() != 0)


		//{
		//	for (int jj = 0; jj < bigpair.size(); jj++)

		//	{
		//		outdata << "BigPair: " << "x= " << bigpair[jj].x << ",y= " << bigpair[jj].y << ",width= " << bigpair[jj].width << ",height= " << bigpair[jj].height << "," << endl;
		//	};

		//}
		////******************************************************************************************************************************************************************
		////Smallpair
		//if (smallpair.size() != 0)


		//{
		//	for (int jj = 0; jj < smallpair.size(); jj++)

		//	{
		//		outdata << "SmallPair: " << "x= " << smallpair[jj].x << ",y= " << smallpair[jj].y << ",width= " << smallpair[jj].width << ",height= " << smallpair[jj].height << "," << endl;
		//	};
		//}
		//*********************************************************************************************************************************************************************
		//Mouth
		if (faces.size() != 0)
		{
			/*for (int jj = 0; jj < mouth.size(); jj++)

			{
				outdata << "Mouth: " << "x= " << mouth[jj].x << ",y= " << mouth[jj].y << ",width= " << mouth[jj].width << ",height= " << mouth[jj].height << "," << endl;
			};*/
			//FaceCropper
			TCHAR Num[10];
			itoa(i, Num, 10);
			_tcscpy(FacesImage, OutputPathImage);
			_tcscat(FacesImage, FileName);
			_tcscat(FacesImage, "_");
			_tcscat(FacesImage, Num);
			_tcscat(FacesImage, ".jpg");
			Mat	Croped;
#ifdef ColorImage// Color
			resize(frame(faces[i]), Croped, OutputSize, 0, 0, INTER_LINEAR);

#else
			resize(frame_resized(faces[i]), Croped, OutputSize, 0, 0, INTER_LINEAR);
#endif 

			imwrite(FacesImage,Croped);//Save Face image in File
			//imwrite(FacesImage, frame_resized(faces[i]));//Save Face image in File
			//imshow("Test", frame_resized(faces[i]));
			//cvWaitKey();

		}
	}
	outdata.close();
	//End 4.9}
}
	  //End 4} 
	