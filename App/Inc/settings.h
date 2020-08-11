// #define SIGMOID
// 打印-延时-毫秒
#define PRINT_DELAY 1000

// 显示布局
#define COLUMN_WIDTH 30
#define COLUMN_1 0
#define COLUMN_2 COLUMN_1 + COLUMN_WIDTH * 1
#define COLUMN_3 COLUMN_1 + COLUMN_WIDTH * 2
#define COLUMN_4 COLUMN_1 + COLUMN_WIDTH * 3
#define COLUMN_5 COLUMN_1 + COLUMN_WIDTH * 4
#define ROW_HIGHT 8
#define ROW_1 0
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3
#define ROW_5 4
#define ROW_6 5
#define ROW_7 6
#define ROW_8 7

// ADC-采样频数
#define ADC_SAMPLING_FREQ 20
// ADC-样本丢弃数量
#define ADC_SAMPLING_DEPRICATE 6
// ADC-采样精度-提高精度也无必要，显示会乱码
#define ADC_SAMPLING_PRECISION ADC_10bit

// 编码器-权值滤波-权值
#define ENCODER_FILTER_WIGHT_0 0.5  // 最近观测值
#define ENCODER_FILTER_WIGHT_1 0.35 // 上次观测值
#define ENCODER_FILTER_WIGHT_2 0.15 // 前次观测值

//电机-保护-防短路
#define MOTOR_PROTECTION
// 电机-PID
#define MOTOR_PID_PARAMETER_P 3 // 1
#define MOTOR_PID_PARAMETER_I 1 // 1
#define MOTOR_PID_PARAMETER_D 2 // 1
// 电机-速度限制
#define MOTOR_VELOCITY_INTERVAL 500    // 区间半径
#define MOTOR_VELOCITY_BASE_POINT 2300 // 基点
// #define MOTOR_VELOCITY_SUPERIOR_LIMIT MOTOR_VELOCITY_BASE_POINT + MOTOR_VELOCITY_INTERVAL // 上极限
#define MOTOR_VELOCITY_SUPERIOR_LIMIT 2300                                                // 上极限
#define MOTOR_VELOCITY_INFERIOR_LIMIT MOTOR_VELOCITY_BASE_POINT - MOTOR_VELOCITY_INTERVAL // 下极限
// 电机-减速等待时间
#define DECELERATE_TIME 200

// 环岛检测-水平电感溢出阈值
#define AD_BRUST_THRESHOLD 800
// 环岛检测-垂直电感阈值
#define VERTICAL_INDUCTOR_THRESHOLD_MAX 500
#define VERTICAL_INDUCTOR_THRESHOLD_MIN 100
// 丢线-水平电感阈值
#define LOST_IN_FRANXX_THRESHOLD_MAX 200
#define LOST_IN_FRANXX_THRESHOLD_MIN 50
#define LOST_IN_FRANXX_THRESHOLD_MED 200
// 舵机-误差计算-权值
#define SERVO_BIAS_WEIGHT_0 0 // 权值1，对应电感1、6差值 1
#define SERVO_BIAS_WEIGHT_1 1 // 权值2，对应电感2、5差值 1
#define SERVO_BIAS_WEIGHT_2 1 // 权值3，对应电感3、4差值 1
// 舵机-PID
#define SERVO_PID_PARAMETER_P 0.2
#define SERVO_PID_PARAMETER_I 0
#define SERVO_PID_PARAMETER_D 1
// 舵机-偏转-占空比// 旧4150—4950—5800 新700-810-920
#define SERVO_BASE_POINT 810 // 基点
#define SERVO_DUTY_INTERVAL_LIMIT 110
#define SERVO_LEFT_LIMIT SERVO_BASE_POINT - SERVO_DUTY_INTERVAL_LIMIT  // 左极限
#define SERVO_RIGHT_LIMIT SERVO_BASE_POINT + SERVO_DUTY_INTERVAL_LIMIT // 右极限
// 舵机-电机-输出参数比例

// 引脚定义-干簧管-和车库检查回调函数联动-不可单独改动
#define PORT_REED_SWITCHER PTB0
// 引脚定义-光电开关
#define PORT_LIGHT_SWITCHER PTA25
//引脚定义-蜂鸣器
#define PORT_BEEPER PTB22
// 引脚定义-拨码开关
#define PORT_SWITCHER_1 PTC1
#define PORT_SWITCHER_2 PTC2
#define PORT_SWITCHER_3 PTC3
#define PORT_SWITCHER_4 PTC4
// 引脚定义-电机
#define PORT_MOTOR FTM0
// 引脚定义-舵机
#define PORT_SERVO FTM1
// 引脚定义-编码器
#define PORT_ENCODER FTM2
