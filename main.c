#include <project.h>
#include <stdio.h> //需要使用sprintf
#include<stdlib.h>
/***************************************
函数功能：由数值转换为字符串的函数
****************************************/
void IntToString(char *str, int number)// 由数值变换为字符串的函数
{
    sprintf(str, "%d", number);
}

/****************************************
函数功能：初始化元器件
****************************************/

int main()
{
    uint32 ADC_Result = 0;//ADC_Result;表示数值的变量
    char string[50];// 由数值变换为字符串时存储的阵列
	float dist;
    float PWM_Left = 4400,PWM_Right=5100;
	int dis_1,dis_2;
    int amux_n=1;
    CyGlobalIntEnable;          //ADC组件的初始化
    ADC_SAR_Seq_Start();
    AMux_1_Select(amux_n);
    ADC_SAR_Seq_StartConvert();    //开始AD转换，因为在组件属性里设定为Continuous，因此以下自动连续采样
    LCD_Char_Start();
    LCD_Char_LoadCustomFonts(LCD_Char_customFonts);

    for(;;)
    {
        amux_n=1;
        AMux_1_Select(amux_n);//choose the right detector
        ADC_SAR_Seq_StartConvert();
        ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); 
        ADC_Result = ADC_SAR_Seq_GetResult16(0);                              //结果存储到变量ADC_Result
        if(ADC_Result >0x7FFF)
        {
            ADC_Result =0;
        }
		
        if(ADC_Result>0)
        {
            
            dist=0.5/(0.00002*ADC_Result -0.00045)-2;
            dis_1=(int)dist;
            if(dis_1>20)        //black detected in the right
            {

                    PWM_Left =3800-10*(dis_1-20);//left motor starts and adjust to the error
                    PWM_Right =4500;//right motor stops

          }
            PWM_Start();
            PWM_WriteCompare(PWM_Right);
            PWM_2_Start();
            PWM_2_WriteCompare(PWM_Left);
        }
        //----------------------------------------------------------------------------------
        amux_n=3;
        AMux_1_Select(amux_n);//choose the left detector
        ADC_SAR_Seq_StartConvert();
        ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); 
        ADC_Result = ADC_SAR_Seq_GetResult16(0);                              //结果存储到变量ADC_Result
        if(ADC_Result >0x7FFF)
        {
            ADC_Result =0;
        }
		
        if(ADC_Result>0)
        {
            
            dist=0.5/(0.00002*ADC_Result -0.00045)-2;
            dis_2=(int)dist;
            if(dis_2>20)        //black detected in the left
            {
                    PWM_Left =4500;//left motor stops
                    PWM_Right =5300+10*(dis_2-20);//right motor starts and adjust to the error
            }
            else
            {//right and left motor act in the same speed
                PWM_Left = 3900;
                PWM_Right = 5100;
            }
        }
    }
    return 0;
}
