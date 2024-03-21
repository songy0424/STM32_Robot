#include "bsp_adc.h"
#include "init.h"

__IO uint16_t ADC_ConvertedValue;

static void ADC1_GPIO_Config(void)
{
	GPIO_INIT(GPIOA,GPIO_Pin_1,GPIO_Mode_AIN);
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// 使能 DMA 通道
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	ADC_InitTypeDef ADC_InitStruct;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE );
	
	ADC_InitStruct.ADC_Mode = 							ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = 			DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = 	ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = 					ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 			1;
	
	ADC_Init(ADC_x,&ADC_InitStruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

	ADC_Cmd(ADC_x, ENABLE);
	
	// 使能ADC DMA 请求
	ADC_DMACmd(ADC_x, ENABLE);
	// ADC开始校准
	ADC_StartCalibration(ADC_x);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADC_x));
}

void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC_Mode_Config();	
}

float Read_ADC_data(void)
{
	float kk=0;
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//开关_ADC软件触发-开关    状态寄存器为0
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//等待转换结束
	kk=(((float)ADC_GetConversionValue(ADC1)/4096)*33); 
	//百分比值转化成电压值，    因为读取了数据寄存器，状态寄存器自动清0
	
//	kk=(float) ADC_ConvertedValue/4096*12.7;
	return kk;
	//返回电压值
}
