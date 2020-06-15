//功能开关部分
//是否恒速
#define CONSTENT_VELOCITY
//是否使用参数切换开关
#define ENABLE_PARAM_SWITCHER
//参数持久化
#define FLASH_WRITE_PARAM 0
//尽量用最后面的扇区，确保安全
#define SECTOR_NO  (FLASH_SECTOR_NUM-1)
//按模型解算位置
// #define INDUCTOR_CENTER_DISTANCE
//拟合多项式计算位置偏差
// #define FIT_POLYNOME

//打印-延时
#define PRINT_DELAY 1000

//显示位置
#define COLUMN_WIDTH 30
#define COLUMN_1 0
#define COLUMN_2 COLUMN_1 + COLUMN_WIDTH * 1
#define COLUMN_3 COLUMN_1 + COLUMN_WIDTH * 2
#define COLUMN_4 COLUMN_1 + COLUMN_WIDTH * 3
#define COLUMN_5 COLUMN_1 + COLUMN_WIDTH * 4
#define COLUMN_6 COLUMN_1 + COLUMN_WIDTH * 5
#define ROW_HIGHT 8
#define ROW_1 1
#define ROW_2 2
#define ROW_3 3
#define ROW_4 4
#define ROW_5 5
#define ROW_6 6
#define ROW_7 7
#define ROW_8 8

//ADC-采样频数
#define ADC_SAMPLING_FREQ 20
//ADC-样本丢弃数量
#define ADC_SAMPLING_DEPRICATE 6
//ADC-采样精度
#define ADC_SAMPLING_PRECISION ADC_10bit
//ADC-参数-磁感应强度关于水平距离的方程斜率
#define ADC_SAMPLING_PARAMETER_SLOPE 20
//ADC-电感高度-mm
#define ADC_SAMPLING_PARAMETER_HEIGHT 70
//ADC-前瞻距离-mm
#define ADC_SAMPLING_PARAMETER_FORWARD 110

//编码器-权值滤波-权值
#define ENCODER_FILTER_WIGHT_0 0.5  //最近观测值
#define ENCODER_FILTER_WIGHT_1 0.35 //上次观测值
#define ENCODER_FILTER_WIGHT_2 0.15 //前次观测值

//电机-PID
#define MOTOR_PID_PARAMETER_P 1
#define MOTOR_PID_PARAMETER_I 3
#define MOTOR_PID_PARAMETER_D 0
//电机-速度限制
#define MOTOR_VELOCITY_BASE_POINT 1000     //基点
#define MOTOR_VELOCITY_SUPERIOR_LIMIT 2000 //上极限
#define MOTOR_VELOCITY_INFERIOR_LIMIT 0    //下极限

//舵机-PI
#define PI 3.14159265358979f
//舵机-偏转角度极限
#define SERVO_ANGLE_LIMIT 90
//舵机-误差计算-权值
#define SERVO_ERRORS_WEIGHT_0 0.5   //权值1，对应电感1、6差值
#define SERVO_ERRORS_WEIGHT_1 0.3   //权值2，对应电感2、5差值
#define SERVO_ERRORS_WEIGHT_2 0.2   //权值3，对应电感3、4差值
//舵机-PID
#define SERVO_PID_PARAMETER_P 18
#define SERVO_PID_PARAMETER_I 0
#define SERVO_PID_PARAMETER_D 0
//舵机-偏转-占空比//4150—4950—5800
#define SERVO_BASE_POINT 4950                    //基点
#define SERVO_DUTY_INTERVAL_LIMIT 850
#define SERVO_LEFT_LIMIT SERVO_BASE_POINT - SERVO_DUTY_INTERVAL_LIMIT  //左极限
#define SERVO_RIGHT_LIMIT SERVO_BASE_POINT + SERVO_DUTY_INTERVAL_LIMIT //右极限
//舵机-电机-输出参数比例
#define PARAMENTER_SERVO_MOTOR_RATIO 0.2

//引脚定义-干簧管
#define PORT_REED_SWITCHER PTA7
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
#define PORT_ENCODER FTM2
//引脚定义-电感，仅展示用，毋改，不然报错
// ADCn_Ch_e port_adc[6] = {
//     ADC0_SE17, //PTE24   1
//     ADC1_SE5a, //PTE1    2
//     ADC1_SE4a, //PTE0    3
//     ADC1_SE6a, //PTE2    4
//     ADC1_SE7a, //PTE3    5
//     ADC0_SE18  //PTE25   6
// };

//编译器不兼容，弃用
// #define MAX(a, b) (a > b) ? a : b
// #define MIN(a, b) (a < b) ? a : b
// #define ABS(a) (a > 0) ? a : -a
