#include "stdafx.h"
#include <iostream>
/*
The MIT License (MIT)

Copyright (c) 2015 Shiqi Yu
shiqi.yu@gmail.com
fengxuting@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "stdafx.h"
#include "opencv2/opencv.hpp"

#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect-x64.lib")
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//load an image and convert it to gray (single-channel)
	//Mat gray = imread("D:\\c\\ConsoleApplication1\\lena.png", CV_LOAD_IMAGE_GRAYSCALE); 
	std::string str(argv[1]) ;
	//printf(argv[1]) ;
	string type = argv[1] ;
	string dir = argv[2] ;
	string filename = argv[3] ;
	Mat gray = imread(dir+filename, CV_LOAD_IMAGE_GRAYSCALE); 
	//根节点
    Json::Value root;

    //根节点属性
    root["retcode"] = Json::Value("0");
    root["retmsg"] = Json::Value("success");
	//子节点
    Json::Value face;
 	Json::StyledWriter sw;
   

	if(gray.empty())
	{
		//fprintf(stderr, "Can not load the image file.\n");
		root["retcode"] = Json::Value("1");
		root["retmsg"] = Json::Value("Can not load the image file.");
		cout << sw.write(root) << endl << endl;
		return -1;
	}

	int * pResults = NULL; 
	if(type== "1"){
		///////////////////////////////////////////
		// frontal face detection 
		// it's fast, but cannot detect side view faces
		//////////////////////////////////////////
		//!!! The input image must be a gray one (single-channel)
		//!!! DO NOT RELEASE pResults !!!
		pResults = facedetect_frontal((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
												   1.2f, 3,  24);
		//printf("%d frontal faces detected.\n", (pResults ? *pResults : 0));
		root["face_count"] = Json::Value((pResults ? *pResults : 0));
		//print the detection results
		for(int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults+1))+6*i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];

			//printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x,y,w,h,neighbors);
			face["x"] = x ;
			face["y"] = y ;
			face["w"] = w ;
			face["h"] = h ;
			face["neighbors"] = neighbors ;
			root["faces"].append(face);
		}
	}
	if(type== "2"){
		///////////////////////////////////////////
		// multiview face detection 
		// it can detect side view faces, but slower than facedetect_frontal().
		//////////////////////////////////////////
		//!!! The input image must be a gray one (single-channel)
		//!!! DO NOT RELEASE pResults !!!
		pResults = facedetect_multiview((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
												   1.2f, 5, 24);
		//printf("%d faces detected.\n", (pResults ? *pResults : 0));
		root["face_count"] = Json::Value((pResults ? *pResults : 0));
		//print the detection results
		for(int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults+1))+6*i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];
			int angle = p[5];

			//printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);
			face["x"] = x ;
			face["y"] = y ;
			face["w"] = w ;
			face["h"] = h ;
			face["neighbors"] = neighbors ;
			face["angle"] = angle ;
			root["faces"].append(face);
		}
	}

	if(type== "3"){
		///////////////////////////////////////////
		// reinforced multiview face detection 
		// it can detect side view faces, better but slower than facedetect_multiview().
		//////////////////////////////////////////
		//!!! The input image must be a gray one (single-channel)
		//!!! DO NOT RELEASE pResults !!!
		pResults = facedetect_multiview_reinforce((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
												   1.2f, 5, 24);
		//printf("%d faces detected.\n", (pResults ? *pResults : 0));
		root["face_count"] = Json::Value((pResults ? *pResults : 0));

		//print the detection results
		for(int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults+1))+6*i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];
			int angle = p[5];

			//printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);
			face["x"] = x ;
			face["y"] = y ;
			face["w"] = w ;
			face["h"] = h ;
			face["neighbors"] = neighbors ;
			face["angle"] = angle ;
			root["faces"].append(face);
		}
	}
	if(type== "4"){
		///////////////////////////////////////////
		// new frontal face detection 
		// it can detect faces with bad illumination.
		//////////////////////////////////////////
		//!!! The input image must be a gray one (single-channel)
		//!!! DO NOT RELEASE pResults !!!
		pResults = facedetect_frontal_tmp((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
												   1.2f, 5, 24);
		//printf("%d faces detected.\n", (pResults ? *pResults : 0));
		root["face_count"] = Json::Value((pResults ? *pResults : 0));

		//print the detection results
		for(int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults+1))+6*i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];

			//printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x,y,w,h,neighbors);
			face["x"] = x ;
			face["y"] = y ;
			face["w"] = w ;
			face["h"] = h ;
			face["neighbors"] = neighbors ;
			root["faces"].append(face);
		}
	}
	cout << sw.write(root) << endl << endl;
	return 0;
}

