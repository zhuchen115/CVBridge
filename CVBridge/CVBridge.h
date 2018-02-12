// CVBridge.h
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace CVBridge {

	public ref class MatConvert
	{
	public:
		/**
		Convert a OpenCV Mat to the Managed Bitmap
		*/
		static Bitmap^ Mat2Bitmap(cv::Mat &imgorig) {
			cv::Mat img;
			// Do Some image processing by opencv
			// The width must can be divided by 4, 
			// see https://msdn.microsoft.com/en-us/library/zy1a2d14(v=vs.110).aspx
			cv::resize(imgorig, img, cv::Size(436, 843));
			// Copy the image Information
			int width = img.size().width;
			int height = img.size().height;
			size_t stride = img.elemSize()*width;
			PixelFormat pfType;
			switch (img.type()) {
				case CV_8UC1:
					pfType = PixelFormat::Format8bppIndexed;
					break;
				case CV_16UC1:
					pfType = PixelFormat::Format16bppGrayScale;
					break;
				case CV_8UC3:
					pfType = PixelFormat::Format24bppRgb;
					break;
				case CV_8UC4:
					pfType = PixelFormat::Format32bppArgb;
					break;
				default:
					pfType = PixelFormat::Undefined;
					break;
			}
			uchar* ptrOrig = img.data;
			size_t szImg = width * height*img.elemSize();
			//Allocate new memory to store the image
			uchar* ptrImage = new uchar[szImg];
			//Copy the image to the new memory
			memcpy_s(ptrImage, szImg, ptrOrig, szImg);
			IntPtr ptrImgint(ptrImage);
			Bitmap ^bmp = gcnew Bitmap(width, height, stride, pfType, ptrImgint);
			return bmp;
		};
	
		static Bitmap^ Load() {
			cv::Mat img = cv::imread("i.jpg");
			return Mat2Bitmap(img);
		}
	};
}
