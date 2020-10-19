/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
FRESULT fresult;
FATFS USBDISKFatFs;          
FIL MyFile;   
char USBDISKPath[4];  
UINT byte_read;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
char Rx_data[13],Data_Rx_Buffer[3000],Data_Buff[500];
uint8_t vrRx;
char ALL_NameFile[500];
uint8_t flag,flag2;
UART_HandleTypeDef huart2;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
extern ApplicationTypeDef Appli_state;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void MX_USB_HOST_Process(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int e = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

    if(huart->Instance == huart2.Instance)
			{
			    if(vrRx != '!'&&vrRx != '/')
						{
							
							Rx_data[e] = vrRx;
							e++;
						}
					 else if (vrRx == '/')
					  {
							printf("%s",Rx_data);
						  flag2 = 1;
					  }						
          else
            {
							printf("%s",Rx_data);
						  flag = 1;
            }	
        HAL_UART_Receive_IT(&huart2,&vrRx,1);						
      }
}
PUTCHAR_PROTOTYPE 
{
 HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
 return ch;
}

FRESULT scan_files (
    char* path        
)
{
    FRESULT res;
    DIR dir;
	  int i = 0;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   
            if (res != FR_OK ) break;  
					int a;
  				for(a = 0;a<13;a++)
					{
						if(fno.fname[a] == '.')// loc file TXT
						{
							
								if(fno.fname[a+1] == 'T')
							{
								sprintf(&ALL_NameFile[((int)fno.fname[0]*1000 + (int)fno.fname[1]*100 + (int)fno.fname[2]*10 + (int)fno.fname[3])*8],"%s" ,fno.fname);
								
								i=strlen(ALL_NameFile);
								//printf("%d",i);
								break;
							}
							else
							{		
								break;
							}
						}
					}										
        }
        f_closedir(&dir);
    }
    return res;
}
void getFileName()
{
	 fresult = f_mount(&USBDISKFatFs,(TCHAR const*)USBDISKPath,1);
						if(fresult == FR_OK)
							{
               fresult = scan_files(Data_Buff);
								}
							else
								{
									printf("error");
									}
}

/*void OpenFileName(char *Num_File)
{
	for(int j = 0;j<13;j++)
	{
		if(Num_File[j] == '!')
			{
				for(int i = 0;i<13;i++)
				{
					if(i<j)
						{
							Rx_data[i] = Num_File[i];
						}
					if(i>=j)
						{
							Rx_data[i] = NULL;
						}
				}
			}
	}
	printf("%s",Rx_data);
}*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    HAL_UART_Receive_IT(&huart2,&vrRx,1);
	//printf("%s",Rx_data);
  while (1)
  {   
    MX_USB_HOST_Process();
    if(flag == 1)
	   {
			 printf("ok");
			 getFileName();
			 printf("%s",(char *)ALL_NameFile);
			 memset(Rx_data,0,13); 
			 e = 0;
			 flag =0;				 
		 }
      //printf("%s",Fno_file);			
		if(flag2 == 1)
			{
			    //OpenFileName(Rx_data);
				   //printf("%c",ALL_NameFile[3]);
				  // printf("%s",Fno_file);
			     fresult = f_mount(&USBDISKFatFs,(TCHAR const*)USBDISKPath,1);
						if(fresult == FR_OK)
							{
								fresult = f_open(&MyFile,Rx_data,FA_READ);
								if(fresult == FR_OK)
							   {
											printf("welldone");
											//f_lseek(&MyFile,0);
									  
											 f_lseek(&MyFile,0);
											 f_read(&MyFile,Data_Rx_Buffer,3000,&byte_read);								
									    //fresult = f_read(&MyFile,Data_Rx_Buffer,253,(UINT*)&byte_read);
									    //printf("huy");
											printf("%s",(char*)Data_Rx_Buffer);
											f_close(&MyFile);
											memset(Rx_data,0,13); 
											memset(Data_Rx_Buffer,NULL,3000); 
											e = 0;
							    }
								}
							else
								{
									printf("error");
	              }
		       flag2 =0;
		    }
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC6 PC7 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
