//***************************************************************************//
//* 版权所有  www.mediapro.cc
//*
//* 内容摘要：windows摄像头采集 DLL封装
//*	
//* 当前版本：V1.0		
//* 作    者：mediapro
//* 完成日期：2021-10-01
//**************************************************************************//

#ifndef _SD_CAMERA_CAPTURE_SDK_H_
#define _SD_CAMERA_CAPTURE_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined _WIN32 || defined __CYGWIN__
  #ifdef DLL_EXPORTS
    #ifdef __GNUC__
      #define DLLIMPORT_CAMERACAP __attribute__ ((dllexport))
    #else
      #define DLLIMPORT_CAMERACAP __declspec(dllexport) 
    #endif
  #else
    #ifdef __GNUC__
      #define DLLIMPORT_CAMERACAP 
    #else
      #define DLLIMPORT_CAMERACAP 
    #endif
  #endif
#else
  #if __GNUC__ >= 4
    #define DLLIMPORT_CAMERACAP __attribute__ ((visibility ("default")))
  #else
    #define DLLIMPORT_CAMERACAP
  #endif
#endif

#ifdef WIN32
typedef signed __int64       int64_t;
#endif

#ifdef __APPLE__
#ifndef OBJC_BOOL_DEFINED
typedef int BOOL;
#endif 
#else
#ifndef BOOL
typedef int BOOL;
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif



//枚举摄像头设备的最大数量
#define SD_MAX_SUPPORT_CAMERA_DEVICES_NUM				5
//摄像头设备名称的最大长度																															
#define SD_MAX_SUPPORT_CAMERA_NAME_LEN			        512



//日志输出的级别
typedef enum CAMERA_CAP_LOG_OUTPUT_LEVEL
{
    CAMERA_LOG_LEVEL_DEBUG = 1,
    CAMERA_LOG_LEVEL_INFO,
    CAMERA_LOG_LEVEL_WARNING,
    CAMERA_LOG_LEVEL_ERROR,
    CAMERA_LOG_LEVEL_ALARM,
    CAMERA_LOG_LEVEL_FATAL,
    CAMERA_LOG_LEVEL_NONE
} CAMERA_CAP_LOG_OUTPUT_LEVEL;


//输出视频格式
typedef enum CAMERA_CAP_OUT_FORMAT
{
    CAMERA_OUT_FORMAT_YUV420P = 0,
    CAMERA_OUT_FORMAT_NV12,
    CAMERA_OUT_FORMAT_NV21,
    CAMERA_OUT_FORMAT_RGB24,
    CAMERA_OUT_FORMAT_RGBA32
} CAMERA_CAP_OUT_FORMAT;



//采集数据输出回调函数
typedef void (*CaptureCameraVideoCallback)(CAMERA_CAP_OUT_FORMAT eFormat, unsigned char* pucData, unsigned int unWidth, unsigned int unHeight, void* pObject);



//////////////////////////////////////////////////////////////////////////
// 摄像头采集封装接口


/***
* 枚举当前系统可用的摄像头设备(获取设备ID和设备名称)
* @param: punCameraDeviceIds 设备ID存放列表
* @param: pCameraDeviceNames 设备名称存放列表
* @param: unMaxDeviceNum 最大枚举的设备数量，小于等于SD_MAX_SUPPORT_CAMERA_DEVICES_NUM
* @param: unMaxDeviceNameLen 最大设备名长度，必须等于SD_MAX_SUPPORT_CAMERA_NAME_LEN
* @return: 返回设备数量
*/
DLLIMPORT_CAMERACAP unsigned int SDCameraCap_GetCameraDeviceList(unsigned int* punCameraDeviceIds, char(*pCameraDeviceNames)[SD_MAX_SUPPORT_CAMERA_NAME_LEN],
                                                        unsigned int unMaxDeviceNum, unsigned int unMaxDeviceNameLen);




/***
* 环境初始化，系统只需调用一次，主要用于日志模块\ffmpeg等的初始化
* @param: outputPath表示日志存放路径，支持相对路径和绝对路径，若目录不存在将自动创建
* @param: outputLevel表示日志输出的级别，只有等于或者高于该级别的日志输出到文件，取值范围参考CAMERA_CAP_LOG_OUTPUT_LEVEL
* @return:
*/
DLLIMPORT_CAMERACAP void  SDCameraCap_Enviroment_Init(const char* outputPath, int outputLevel);

DLLIMPORT_CAMERACAP void  SDCameraCap_Enviroment_Free();


/***
* 创建SDCameraCap对象
* @return: 返回模块指针，为NULL则失败
*/
DLLIMPORT_CAMERACAP void*  SDCameraCap_New();


/***
* 销毁SDCameraCap对象，使用者应该做好与其他API之间的互斥保护
* @param ppCameraCap: 模块指针指针
* @return:
*/
DLLIMPORT_CAMERACAP void  SDCameraCap_Delete(void** ppCameraCap);



/***
* 启动采集
* @param: pCameraCap 模块指针
* @param: unCameraId 待采集的设备ID
* @param: unCapFrameRate 采集帧率
* @param: unWidth 采集输出宽度
* @param: unHeight 采集输出高度
* @param: eCapFormat 采集输出格式
* @param: pfCapCallback 采集输出回调接口，可以再回调中进行编码耗时操作
* @param: pObject 采集输出回调接口透传参数
* @return: TRUE成功，FALSE失败
*/
DLLIMPORT_CAMERACAP BOOL  SDCameraCap_Start(void* pCameraCap, unsigned int unCameraId, unsigned int unCapFrameRate, unsigned int unWidth, unsigned int unHeight,
                                CAMERA_CAP_OUT_FORMAT eCapFormat, CaptureCameraVideoCallback pfCapCallback, void* pObject);



/***
* 停止采集
* @param: pCameraCap 模块指针
*/
DLLIMPORT_CAMERACAP void  SDCameraCap_Stop(void* pCameraCap);


#ifdef __cplusplus
}
#endif

#endif // _SD_CAMERA_CAPTURE_SDK_H_
