# camera capture sdk for windows with simple api


## SDCameraCapSdk简介
本库完成Windows平台下摄像头采集功能，其支持特性如下：

* 1、支持MJPEG采集，因而能充分发挥摄像头性能，实现高分辨率、高帧率采集。同时支持RAW格式（YUV）采集，保持最大兼容性。
* 2、内部自动遍历摄像头能力（分辨率、帧率），选择与用户请求能力最为匹配的能力进行采集，提高设备采集成功率。
* 3、内置缩放和色度转换，支持对外输出用户指定的分辨率和色度空间，可直通编码器。
* 4、支持枚举摄像头列表。
* 5、摄像头被占用时，模块启动采集将返回失败。摄像头采集过程中被移除时，模块将停止输出采集数据。
* 6、仅六个接口，调用简洁，性能强劲。
* 7、C++开发动态库，支持C、C++、C#跨语言调用


## SDCameraCapSdk  C API

### 
* 环境初始化，系统只需调用一次<br>
@param: outputPath：日志文件输出的目录，若目录不存在将自动创建<br>
@param: outputLevel：日志输出的级别，只有等于或者高于该级别的日志输出到文件<br>
@return: <br>
void  `SDCameraCap_Enviroment_Init`(const char * outputPath,  int outputLevel);

### 
* 环境反初始化，系统只需调用一次<br>
@return:<br>
void  `SDCameraCap_Enviroment_Free`();

### 
* 创建SDCameraCap对象<br>
@return: 返回模块指针，为NULL则失败<br>
void*  `SDCameraCap_New`();

### 
* 销毁SDCameraCap,注意：【涉及到资源销毁，使用者应该做好本接口与其他接口的互斥保护】<br>
@param  ppCameraCap: 模块指针的指针，内部销毁完后将设置为NULL<br>
@return: <br>
void  `SDCameraCap_Delete`(void** ppCameraCap);

### 
* 开始启动采集<br>
@param pCameraCap: 模块指针<br>
@param unCameraId: 待采集的设备ID。<br>
@param unCapFrameRate: 请求采集帧率，当摄像头实际支持帧率不足时，输出实际帧率。模块内部将确保实际帧率不会超出请求帧率。<br>
@param unCapWidth: 请求采集输出宽度，当摄像头不支持该宽高时，将以最为接近的分辨率进行采集，并缩放至请求宽高。<br>
@param unCapHeight: 请求采集输出高度<br>
@param eCapFormat: 请求采集输出格式，建议根据编码器输入格式来确定采集输出格式，尽量保持一致，以便直通编码，提高性能。<br>
@param pfCapCallback: 采集输出回调接口，可以在回调中进行编码耗时操作。<br>
@param pObject: 采集输出回调接口透传参数<br>
@return: TURE成功，FALSE失败<br>
BOOL  `SDCameraCap_Start`(void* pCameraCap, unsigned int unCameraId, unsigned int unCapFrameRate, unsigned int unCapWidth, unsigned int unCapHeight, CAMERA_CAP_OUT_FORMAT eCapFormat, CaptureCameraVideoCallback pfCapCallback, void* pObject);

### 
* 停止采集<br>
@param pCameraCap: 模块指针<br>
@return: <br>
void  `SDCameraCap_Stop`(void* pCameraCap);

### 
* 枚举当前可用的摄像头设备<br>
@param punCameraDeviceIds: 设备ID存放列表<br>
@param pCameraDeviceNames: 设备名称存放列表，ANSI编码。<br>
@param unMaxDeviceNum: 最大枚举的设备数量，小于等于SD_MAX_SUPPORT_CAMERA_DEVICES_NUM<br>
@param unMaxDeviceNameLen: 最大设备名长度，必须等于SD_MAX_SUPPORT_CAMERA_NAME_LEN<br>
@return: 返回可用设备数量，即上述数组中有效元素数目。<br>
unsigned int  `SDCameraCap_GetCameraDeviceList`(unsigned int* punCameraDeviceIds, char(*pCameraDeviceNames)[SD_MAX_SUPPORT_CAMERA_NAME_LEN], unsigned int unMaxDeviceNum, unsigned int unMaxDeviceNameLen);


### 本库可免费使用，若需要商用或定制服务请联系 www.mediapro.cc
