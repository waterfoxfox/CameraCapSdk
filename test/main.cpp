
#include <stdio.h>
#include <string>
#include "SDCameraCaptureSdk.h"


static void saveYuv(unsigned char* buf, int wrap, int xsize, int ysize, const char* recfilename)
{
	FILE* f = fopen(recfilename, "ab+");
	for (int i = 0; i < ysize; i++)
	{
		fwrite(buf + i * wrap, 1, xsize, f);
	}
	fclose(f);
}


void CaptureCameraVideoDataCallback(CAMERA_CAP_OUT_FORMAT eFormat, unsigned char* pucData, unsigned int nWidth, unsigned int nHeight, void* pObject)
{
#if 0
	//YUV420P
	unsigned char* dst_y = pucData;
	int dst_stride_y = nWidth;
	unsigned char* dst_u = dst_y + nWidth * nHeight;
	int dst_stride_u = nWidth / 2;
	unsigned char* dst_v = dst_u + (nWidth * nHeight) / 4;
	int dst_stride_v = nWidth / 2;

	saveYuv(dst_y, dst_stride_y, nWidth, nHeight, "D:\\camera.yuv");
	saveYuv(dst_u, dst_stride_u, nWidth / 2, nHeight / 2, "D:\\camera.yuv");
	saveYuv(dst_v, dst_stride_v, nWidth / 2, nHeight / 2, "D:\\camera.yuv");
#endif

	printf("cap a fram %dx%d!\n", nWidth, nHeight);
}


int main()
{
	SDCameraCap_Enviroment_Init("./log", CAMERA_LOG_LEVEL_INFO);

	unsigned int unCameraDeviceIds[SD_MAX_SUPPORT_CAMERA_DEVICES_NUM];
	char pCameraDeviceNames[SD_MAX_SUPPORT_CAMERA_DEVICES_NUM][SD_MAX_SUPPORT_CAMERA_NAME_LEN];

	unsigned int unDeviceNum = SDCameraCap_GetCameraDeviceList(unCameraDeviceIds, pCameraDeviceNames, SD_MAX_SUPPORT_CAMERA_DEVICES_NUM, SD_MAX_SUPPORT_CAMERA_NAME_LEN);
	for (unsigned int i = 0; i < unDeviceNum; i++)
	{
		printf("device:%s  id:%d\n", pCameraDeviceNames[i], unCameraDeviceIds[i]);
	}

	getchar();

	if (unDeviceNum == 0)
	{
		return 0;
	}

	void* pCameraCap = SDCameraCap_New();

	SDCameraCap_Start(pCameraCap, unCameraDeviceIds[0], 30, 1280, 720, CAMERA_OUT_FORMAT_YUV420P, CaptureCameraVideoDataCallback, NULL);

	printf("staring...\n");

	getchar();

	SDCameraCap_Stop(pCameraCap);
	SDCameraCap_Delete(&pCameraCap);

	SDCameraCap_Enviroment_Free();

	return 0;
}


