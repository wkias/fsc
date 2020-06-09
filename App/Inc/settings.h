//ADC-采样频数
#define ADC_SAMPLING_FREQ 12

//电机测速-权值滤波
#define MOTOR_MEASURE_FILTER_WIGHT_0 0.5
#define MOTOR_MEASURE_FILTER_WIGHT_1 0.3
#define MOTOR_MEASURE_FILTER_WIGHT_2 0.2

//舵机误差-权值滤波
#define MOTOR_MEASURE_FILTER_WIGHT_0 0.5
#define MOTOR_MEASURE_FILTER_WIGHT_1 0.3
#define MOTOR_MEASURE_FILTER_WIGHT_2 0.2

//电机-PID
#define MOTOR_PID_PARAMENTER_P 1
#define MOTOR_PID_PARAMENTER_I 3
#define MOTOR_PID_PARAMENTER_D 0

//舵机-PID
#define SERVO_PID_PARAMENTER_P 0.3
#define SERVO_PID_PARAMENTER_I 0.3
#define SERVO_PID_PARAMENTER_D 1.2

//舵机-偏转-占空比//3900—4700—5500
#define SERVO_BASE_POINT 4950           //基点
#define SERVO_RIGHT_LIMIT 4950 + 850    //右极限
#define SERVO_LEFT_LIMIT 4950 - 850     //左极限

//引脚定义-拨码开关
#define PORT_SWITCHER_1 PTC1
#define PORT_SWITCHER_2 PTC2
#define PORT_SWITCHER_3 PTC3
#define PORT_SWITCHER_4 PTC4
//引脚定义-电机
#define PORT_MOTOR FTM0
//引脚定义-舵机
#define PORT_SERVO FTM1
//引脚定义-编码器
#define PORT_CODER FTM2

// ADCn_Ch_e adc[6] = {
//     ADC1_SE4a, //PTE0    左电磁
//     ADC1_SE5a, //PTE1    最左电磁
//     ADC1_SE6a, //PTE2    右电磁
//     ADC1_SE7a, //PTE3    最右电磁
//     ADC0_SE17, //PTE24   左竖电磁
//     ADC0_SE18  //PTE25   右竖电磁
// };