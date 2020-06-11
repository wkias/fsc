#define led led(LED0,LED_ON)

//是否使用参数切换开关
#define ENABLE_PARAM_SWITCHER 1
#define ENABLE_LED 0

//打印-延时
#define PRINT_DELAY 1000

//灯光效果
#define LED_CARPORT LED0
#define LED_SAMPLING LED1
#define LED_SERVO LED2
#define LED_MOTOR LED3

//显示位置
#define COLUMN_WIDTH 30
#define COLUMN_1 0
#define COLUMN_2 COLUMN_1 + COLUMN_WIDTH * 1
#define COLUMN_3 COLUMN_1 + COLUMN_WIDTH * 2
#define COLUMN_4 COLUMN_1 + COLUMN_WIDTH * 3
#define COLUMN_5 COLUMN_1 + COLUMN_WIDTH * 4
#define COLUMN_6 COLUMN_1 + COLUMN_WIDTH * 4
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
#define ADC_SAMPLING_FREQ 12
//ADC-采样精度
#define ADC_SAMPLING_PRECISION ADC_16bit

//编码器-权值滤波-权值
#define ENCODER_FILTER_WIGHT_0 0.5 //最近观测值
#define ENCODER_FILTER_WIGHT_1 0.3 //上次观测值
#define ENCODER_FILTER_WIGHT_2 0.2 //前次观测值

//电机-PID
#define MOTOR_PID_PARAMENTER_P 1
#define MOTOR_PID_PARAMENTER_I 3
#define MOTOR_PID_PARAMENTER_D 0
//电机-速度限制
#define MOTOR_VELOCITY_BASE_POINT 1000     //基点
#define MOTOR_VELOCITY_SUPERIOR_LIMIT 2000 //上极限
#define MOTOR_VELOCITY_INFERIOR_LIMIT 0    //下极限

//舵机-误差计算-权值
#define SERVO_ERRORS_WEIGHT_0 0.5 //权值1，对应电感1、6差值
#define SERVO_ERRORS_WEIGHT_1 0.3 //权值2，对应电感2、5差值
#define SERVO_ERRORS_WEIGHT_2 0.2 //权值3，对应电感3、4差值
//舵机-PID
#define SERVO_PID_PARAMENTER_P 0.3
#define SERVO_PID_PARAMENTER_I 0.3
#define SERVO_PID_PARAMENTER_D 1.2
//舵机-偏转-占空比//4150—4950—5800
#define SERVO_BASE_POINT 4950                    //基点
#define SERVO_LEFT_LIMIT SERVO_BASE_POINT - 850  //左极限
#define SERVO_RIGHT_LIMIT SERVO_BASE_POINT + 850 //右极限
//舵机-电机-输出参数比例
#define PARAMENTER_SERVO_MOTOR_RATIO 2.5

//引脚定义-干簧管
#define PORT_REED_SWITCHER_1 PTA6
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

//编译器提示不兼容，弃用
// #define MAX(a, b) (a > b) ? a : b
// #define MIN(a, b) (a < b) ? a : b
// #define ABS(a) (a > 0) ? a : -a
