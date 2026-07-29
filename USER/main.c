#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "flash.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "gt911.h"
#include "protocol.h"
#include "can.h" 
#include "stm32f4xx_hal.h"      // 为 CanRxMsgTypeDef 等
#include "main.h"
#include "rtc.h"
#include "uart.h"
typedef struct {
    float steam_boiler_temp;     // 蒸汽锅炉温度（单位：°C）
    float coffee_boiler_temp;    // 咖啡锅炉温度（单位：°C）
    float brew_head_temp;        // 冲煮头温度（单位：°C）
    float pressure; //压力值（单位：Pa）
} TemperatureData;
TemperatureData current_temp = {0};

TaskFeedback_t taskFeedback;
/// @brief external variables
extern volatile uint16_t Currenttargeweight;
extern volatile uint8_t dataIsReady;
extern uint8_t rFrameBuf[FRAME_MAX_LEN];
extern uint8_t recivedCount;
extern bool hotwaterenable;
/// @brief static global variables
static uint8_t buf[FRAME_MAX_LEN];
static struct Protocol c;
static const char version[12] = "MRC_V1.0.0";

void vLvglTaskFunction( void * pvParameters );
void thread_serial(void *pvParameters);

struct GrindRealData GrindDataStr;
struct GrindData GrindDatarx;//GrindData
TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
TaskHandle_t xSerialTaskHandle = NULL; 

lv_ui guider_ui;

bool isGrindMode = MODE_TIME;
uint8_t step = 0;
CanMsg can_msg = {0};

// 接收完成：从 HAL 的 pRxMsg 读取数据，转交给 CAN_UserRxCb，然后重新使能接收
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan_if)
{
    CanRxMsgTypeDef *r = hcan_if->pRxMsg;

    uint8_t i = 0;

    can_msg.rx_dlen = r->DLC;

    for (i = 0; i < r->DLC && i < 8; i++) 
        can_msg.rx_data[i] = r->Data[i];

    for (; i < 8; i++) 
        can_msg.rx_data[i] = 0x00;

#ifdef CAN_Id_Extended
    if (r->IDE == CAN_Id_Extended) {
        can_msg.rx_efid = r->ExtId;
        can_msg.data_is_ready = 1;
    } 
#else
    // 如果你的 HAL 没有 CAN_Id_Extended 宏，使用常见数值判断：0x04 表示扩展（老 HAL 习惯）
    if (r->IDE == 0x04U) {
        is_ext = 1; id = r->ExtId;
    } else {
        is_ext = 0; id = r->StdId;
    }
#endif
    // 转给我们封装的用户回调（由用户覆盖）
    //CAN_UserRxCb(is_ext, id, r->DLC, data);

    // 重新使能接收（legacy HAL 的 Receive_IT 是一次性的）
    HAL_CAN_Receive_IT(hcan_if, CAN_FIFO0);
}

// 发送完成回调：通知用户
void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef *hcan_if)
{
    (void)hcan_if;
    CAN_UserTxCb();
}

// 错误回调：转发或记录错误码。你可以在这里打印 hcan_if->ErrorCode
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan_if)
{
    // 用户可覆盖 HAL_CAN_ErrorCallback 或实现 CAN_UserXXX 来打印错误
    // 例如：Debug_Printf("CAN err 0x%08lX\n", hcan_if->ErrorCode);
}

void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; 
    DWT->CYCCNT = 0;                                
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;           
}

/// 32K offset
#define APP_FLASH_OFFSET 0x8000
int main(void)
{ 
    
    SCB->VTOR = FLASH_BASE | APP_FLASH_OFFSET;
	DWT_Init();
	BaseType_t xReturned;
	HAL_Init();      
    
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); 
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0); 
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	STM32_Clock_Init(336,25,2,7);  	

	delay_init(168);               
	LED_Init();					
	//TIM2_Init();	
	//KEY_Init();
    uart6_init(); 

    ISL1208_Init();

    // ISL1208_Time_t current_time;
    // ISL1208_Time_t time_read;
    // // // 2. 设置时间
    // current_time.seconds = 00;
    // current_time.minutes = 57;
    // current_time.hours = 11;    // 14:45:30
    // current_time.date = 6;
    // current_time.month = 3;
    // current_time.year = 26;     // 2026年
    // current_time.day = 5;       // 星期天
    // current_time.format_12h = 0; // 24小时制
    
    // ISL1208_SetTime(&current_time);

    // 3. 读取时间
    printf("App is running.Version:%s Compiled on %s %s\n",version,__DATE__,__TIME__);

    uart4_init();
    gt911_init();

    flashDataInit();
    
    CAN_Init_IT(500);
    CAN_ConfigFilterAcceptAll();
    CAN_StartReceive_IT();
    
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
    xTaskCreate(thread_serial, "thread_serial", 1024, NULL, 2, &xSerialTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
	}
}

void parseTaskFeedback(uint8_t *data)
{
    taskFeedback.function = data[0];
    taskFeedback.step = data[1];
    taskFeedback.state = data[2];
    taskFeedback.progress = data[3];
    taskFeedback.error = data[4];
    taskFeedback.update_flag = 1;
}

extern volatile uint16_t volume;
extern volatile uint16_t steamvolume;
float blocktemp = 0;
float brewtemp = 0;
volatile uint8_t coffee_run_flag = 0;
volatile uint8_t steam_run_flag = 0;
extern uint8_t teasetflag ;
extern uint8_t teaflag ;
extern uint8_t steamEnable;
bool startflag;
extern uint8_t scheduleall;
bool updatetaskflag = false;
void CoffeeVolumeProcess(void)
{
    static TickType_t lastTick = 0;
    static int schedule = 0;
    // 没启动则直接返回
    if(coffee_run_flag == 0)
    {
        lv_obj_add_flag(guider_ui.screen_cont_countdown, LV_OBJ_FLAG_HIDDEN);
        return;
    }
    lv_obj_clear_flag(guider_ui.screen_cont_countdown, LV_OBJ_FLAG_HIDDEN);
    // 每1s减一次
    if(xTaskGetTickCount() - lastTick >= pdMS_TO_TICKS(1000))
    {
        lastTick = xTaskGetTickCount();
        if(volume > 9)
        lv_label_set_text_fmt(guider_ui.screen_label_18, "00:%d", volume); 
        else if(volume >= 0)
        lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", volume);
        if(volume > 0){
            schedule = (volume*100)/scheduleall;
            volume--;
            // printf("scheduieall = %d volume = %d  schedule = %d\r\n", scheduleall,volume,schedule);
        } else {
            lv_obj_add_flag(guider_ui.screen_cont_countdown, LV_OBJ_FLAG_HIDDEN);
            startflag = false;
            hotwaterenable = false;
            #if (LEFT_OR_COFFEE == LEFT)            
            lv_obj_set_style_bg_opa(guider_ui.screen_btn_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
            #endif
            volume = 0;
            schedule = (volume*100)/scheduleall;
            coffee_run_flag = 0;
            printf("Coffee volume finished\r\n");
        }       
        // if(schedule > 9)
        // lv_label_set_text_fmt(guider_ui.screen_label_18, "00:%d", schedule); 
        // else if(schedule >= 0)
        // lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", schedule);
    }

}

void SteamVolumeProcess(void)
{
    static TickType_t lastTickSteam = 0;
    // static int schedule = 0;
    // 没启动则直接返回
    if(steamEnable == 0)
    {
        return;
    }
    // 每1s减一次
    if(xTaskGetTickCount() - lastTickSteam >= pdMS_TO_TICKS(1000))
    {
        lastTickSteam = xTaskGetTickCount();
        lv_label_set_text_fmt(guider_ui.screen_label_steamtime, "%d", steamvolume);
        if(steamvolume > 0){
            steamvolume--;
        } else {
            lv_obj_add_flag(guider_ui.screen_label_steamtime, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_opa(guider_ui.screen_btn_steam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
            steamvolume = 0;
            steamEnable = 0;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftSteam(0,volume);
            #else
                canSendRightSteam(0,volume);
            #endif
            printf("steam volume finished\r\n");
        }       
    }
}

void thread_serial(void *pvParameters)
{
    int len = 0;
    int timeover = 0;
    GrindDataStr.data.mode = MODE_TIME;
    GrindDataStr.data.target = 3000; ///ms
    GrindDataStr.data.cmd_number = 0;
    GrindDataStr.data.cmd_state = CMD_STATE_IDLE;
    GrindDataStr.data.cmd = CMDTYPE_GRIND;
    uint8_t lasttaskstate = 0;


    static TickType_t lastUpdateTime = 0;
    const TickType_t updateTimePeriod = pdMS_TO_TICKS(8000); 
    #if (LEFT_OR_COFFEE == RIGHT)
    const TickType_t machineInfoupdateTimePeriod = pdMS_TO_TICKS(7000); 
    #else
    const TickType_t machineInfoupdateTimePeriod = pdMS_TO_TICKS(6500); 
    #endif
    int time = 0;
    int machinetime = 0;
    ISL1208_Time_t time_read;
    bool isfillwater = false;
    // //读取时间
    // ISL1208_GetTime(&time_read);
    uint32_t runtime = 0;
    while (1){
   // 开机5s后补一次水
        TickType_t currentTime = xTaskGetTickCount();
        if (currentTime - lastUpdateTime >= updateTimePeriod && time < 1 ) {           
            GrindDataStr.data.cmd = CMDTYPE_SYSTEM_FILL_WATER;
            time++;
        } 
        if (currentTime - lastUpdateTime >= machineInfoupdateTimePeriod && machinetime < 2 ) {           
            GrindDataStr.data.cmd = CMDTYPE_SET_STEAMBLOCK;
            machinetime++;
        } 
        if (GrindDataStr.data.cmd == CMDTYPE_GRIND){

        }
        else if (GrindDataStr.data.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            #if (LEFT_OR_COFFEE == LEFT)
            canSendFillWater();
            #endif
            
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_BEVERAGEMAKE_CHANNELB){
            coffee_run_flag = 1;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftCoffee(1,volume);
            #else
                canSendRightCoffee(1,volume);
            #endif
            
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_MAKE_TEA){
            coffee_run_flag = 1;
            printf("do tea");
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftTeaProfile(GrindSetData.extract_time[teasetflag]);
                vTaskDelay(10 / portTICK_RATE_MS);
                canSendLeftTeaStart(1);
            #else
                canSendRightTeaProfile(GrindSetData.extract_time[teaflag]);
                vTaskDelay(10 / portTICK_RATE_MS);
                canSendRightTeaStart(1);
            #endif

            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if(GrindDataStr.data.cmd == CMDTYPE_MAKE_STEAM) {
            steamEnable = 1;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftSteam(1,volume);
            #else
                canSendRightSteam(1,volume);
            #endif
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB){
            coffee_run_flag = 0;
            volume = 0;
            lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", volume); 
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftCoffee(0,volume);
            #else
                canSendRightCoffee(0,volume);
            #endif
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_STEAMBLOCK) { 
            volume = GrindSetData.temp_steam;
            canSendsteamtemp(0,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_SET_COFFEEBLOCK;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_COFFEEBLOCK) { 
            #if(LEFT_OR_COFFEE == LEFT)
            int target = 0;
            #else
            int target = 1;
            #endif
            volume = GrindSetData.temp_coffee;
            canSendcoffeetemp(target,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_SET_BREWBLOCK;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_BREWBLOCK) { 
            #if(LEFT_OR_COFFEE == LEFT)
            int target = 0;
            #else
            int target = 1;
            #endif
            volume = GrindSetData.temp_brew;
            canSendbrewtemp(target,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } 
        #if (LEFT_OR_COFFEE == LEFT)
        else if (GrindDataStr.data.cmd == CMDTYPE_HOTWATER) { 
            coffee_run_flag = 1;
            canSendhotwater(1,volume);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_EMPTY_WATER){
            canSendmaintain(CMDTYPE_EMPTY_WATER,1);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_CHANGE_WATER){
            canSendmaintain(CMDTYPE_CHANGE_WATER,1);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_DESCALE){
            canSendmaintain(CMDTYPE_DESCALE,step);
            step = 0;
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } 
        #endif
        #if 0
        if (GrindDataStr.data.cmd == CMDTYPE_GRIND){

        } else if (GrindDataStr.data.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            len = setFillwater(buf,&GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        } else if (GrindDataStr.data.cmd == CMDTYPE_MAKE_STEAM){
            len = setdosteam(buf, &GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        } else if (GrindDataStr.data.cmd == CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB ){
            len = setcancel(buf, &GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        }
        
        timeover = 0;
        while (!dataIsReady && timeover < 20) {
            timeover++;
            vTaskDelay(pdMS_TO_TICKS(1));
        }
        #if 1
        if (timeover >= 20) {
            // printf("timeover line = %d\r\n", __LINE__);
            uint32_t error_code;// = huart->ErrorCode;
            uint32_t sr_register = UART4->SR;  // 直接读取状态寄存器
            
            // 打印错误信息（如果可以使用printf）=
            // printf("UART4 Error!  SR: 0x%04lX\r\n", sr_register);
        }
        #endif
        if (dataIsReady){
            dataIsReady = 0;  
            getProtocol(rFrameBuf,&c);
            if (c.frame.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            
            } 
        }
        #endif
        if (can_msg.data_is_ready){
            can_msg.data_is_ready = 0;
            uint8_t crc = 0;
            for(int i = 0;i < can_msg.rx_dlen;i++){
                crc += can_msg.rx_data[i];
            }
            if (getCrc(can_msg.rx_efid)  == crc ) {
                if (getDestId(can_msg.rx_efid)  == HMI_ID ) {
                    if ( getCmdType(can_msg.rx_efid) == FUNC_TEMPERATURE_B) {
                        int ret = can_msg.rx_data[1] << 8 | can_msg.rx_data[0];
                        current_temp.steam_boiler_temp = (float)ret/10;
                        // if(runtime >= 1000){
                        //     char temp_str[20];
                        //     sprintf(temp_str, "%.1f", blocktemp);
                        //     lv_label_set_text(guider_ui.screen_label_3, temp_str);
                        // }
                    } else if (getCmdType(can_msg.rx_efid) == FUNC_TEMPERATURE_A){
                        #if (LEFT_OR_COFFEE == LEFT)
                        int ret = can_msg.rx_data[5] << 8 | can_msg.rx_data[4];
                        int ret2 = can_msg.rx_data[3] << 8 | can_msg.rx_data[2];   
                        current_temp.brew_head_temp = (float)ret2/10;   
                        current_temp.coffee_boiler_temp = (float)ret/10;
                        // if(runtime >= 1000){
                        //     char temp_str[20];
                        //     char temp_str1[20];
                        //     sprintf(temp_str, "%.1f", blocktemp);
                        //     lv_label_set_text(guider_ui.screen_label_4, temp_str);
                            // sprintf(temp_str1, "%.1f", brewtemp);
                            // lv_label_set_text(guider_ui.screen_label_1, temp_str1);
                        // }      
                
                        #else
                        int ret = can_msg.rx_data[7] << 8 | can_msg.rx_data[6];
                        current_temp.coffee_boiler_temp = (float)ret/10;
                        // if(runtime >= 1000){
                        //      char temp_str[20];

                        //     sprintf(temp_str, "%.1f", blocktemp);
                        //     lv_label_set_text(guider_ui.screen_label_4, temp_str);
                        // }                               
                        #endif
                    } else if (getCmdType(can_msg.rx_efid) == FUNC_PRESSURE_CURRENT){ 
                        current_temp.pressure = (float)can_msg.rx_data[0]/10;
                        // if(runtime >= 1000){
                        //      char temp_str[20];

                        //     sprintf(temp_str, "%.1f bar", ret);
                        //     lv_label_set_text(guider_ui.screen_label_16, temp_str);
                        // }   
                    } else if (getCmdType(can_msg.rx_efid)==FUNC_TASK_FEEDBACK){ 
                        parseTaskFeedback(can_msg.rx_data);
                        if(lasttaskstate != taskFeedback.state){
                            updatetaskflag = true;
                        }
                        lasttaskstate = taskFeedback.state;
                    } 
                    
                    #if (LEFT_OR_COFFEE == RIGHT)
                    else if (getCmdType(can_msg.rx_efid) == FUNC_VALVE){ 
                        int ret = can_msg.rx_data[5] << 8 | can_msg.rx_data[4];
                        // printf("ret %.1f\n",ret);
                        current_temp.brew_head_temp = (float)ret/10;
                        // if(runtime >= 1000){
                        //     char temp_str[20];
                        //     sprintf(temp_str, "%.1f", brewtemp);
                        //     lv_label_set_text(guider_ui.screen_label_1, temp_str);
                        // }   
                    }
                    #endif
                }
            } else {
                printf("crc failed\r\n");
            }
        }

        if(!startflag){
            lv_obj_add_flag(guider_ui.screen_img_stop, LV_OBJ_FLAG_HIDDEN);
            #if (LEFT_OR_COFFEE == LEFT)
            lv_obj_clear_flag(guider_ui.screen_btn_hotwater, LV_OBJ_FLAG_HIDDEN);
            #endif
            lv_obj_clear_flag(guider_ui.screen_img_21, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_rinse, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee3, LV_OBJ_FLAG_HIDDEN);
            startflag = true;
        }

        CoffeeVolumeProcess();
        SteamVolumeProcess();
        runtime += 5;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
void updatetemp(void){
    char temp_str[20];
    sprintf(temp_str, "%.1f", current_temp.brew_head_temp);
    lv_label_set_text(guider_ui.screen_label_1, temp_str);
    sprintf(temp_str, "%.1f", current_temp.steam_boiler_temp);
    lv_label_set_text(guider_ui.screen_label_3, temp_str);
    sprintf(temp_str, "%.1f", current_temp.coffee_boiler_temp);
    lv_label_set_text(guider_ui.screen_label_4, temp_str);
    sprintf(temp_str, "%.1f bar", current_temp.pressure);
    lv_label_set_text(guider_ui.screen_label_16, temp_str);
}
void updateTaskStep(void)
{
    char buf[64];
#if (LEFT_OR_COFFEE == LEFT)
    if (taskFeedback.state == TASK_RUNNING){
            lv_bar_set_value(guider_ui.screen_1_bar_maintain,taskFeedback.progress,LV_ANIM_ON);    
            printf("progress %d\n",taskFeedback.progress);    
    } else if (taskFeedback.progress > 1 ){
        if(taskFeedback.function == CMDTYPE_EMPTY_WATER && taskFeedback.state == TASK_FINISH && updatetaskflag == true)
        {
            updatetaskflag = false;
            sprintf(buf,"Water system draining completed.Please turn off the power.");
            lv_bar_set_value(guider_ui.screen_1_bar_maintain,taskFeedback.progress,LV_ANIM_ON);
            lv_label_set_text(guider_ui.screen_1_label_maintain, buf);
        } else if (taskFeedback.function == CMDTYPE_CHANGE_WATER && taskFeedback.state == TASK_FINISH && updatetaskflag == true){
            updatetaskflag = false;
            lv_bar_set_value(guider_ui.screen_1_bar_maintain,taskFeedback.progress,LV_ANIM_ON);
            lv_obj_add_flag(guider_ui.screen_1_cont_maintain,LV_OBJ_FLAG_HIDDEN);
        } else if (taskFeedback.function == CMDTYPE_DESCALE && taskFeedback.step == 1 && taskFeedback.state == TASK_PAUSE && updatetaskflag == true){
            updatetaskflag = false;
            step = 2;
            sprintf(buf,"Replace the tank water with 4L of fresh water.Tap OK to continue rinsing.");
            lv_label_set_text(guider_ui.screen_1_label_maintain, buf);
            lv_obj_clear_flag(guider_ui.screen_1_btn_maintain,LV_OBJ_FLAG_HIDDEN);
        } else if (taskFeedback.function == CMDTYPE_DESCALE && taskFeedback.step == 2 && taskFeedback.state == TASK_PAUSE && updatetaskflag == true ){
            updatetaskflag = false;
            step = 3;
            sprintf(buf,"Tap OK to start boiler water replacement.");
            lv_label_set_text(guider_ui.screen_1_label_maintain, buf);
            lv_obj_clear_flag(guider_ui.screen_1_btn_maintain,LV_OBJ_FLAG_HIDDEN);
        } else if (taskFeedback.function == CMDTYPE_DESCALE && taskFeedback.step == 3 && taskFeedback.state == TASK_FINISH && updatetaskflag == true){
            updatetaskflag = false;
            step = 0;
            lv_bar_set_value(guider_ui.screen_1_bar_maintain,taskFeedback.progress,LV_ANIM_ON);
            lv_obj_add_flag(guider_ui.screen_1_cont_maintain,LV_OBJ_FLAG_HIDDEN);
        }
    }
    #else
    printf("taskFeedback.state %d\n",taskFeedback.state);
    if (taskFeedback.state == TASK_RUNNING || taskFeedback.state == TASK_PAUSE ){
        lv_obj_add_flag(guider_ui.screen_1_bar_maintain,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_1_btn_maintain,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_1_cont_maintain,LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(guider_ui.screen_1_label_maintain, "Maintaining");
    } else {
        lv_obj_add_flag(guider_ui.screen_1_cont_maintain,LV_OBJ_FLAG_HIDDEN);
    }

    #endif
}
void vLvglTaskFunction(void *pvParameters) {
    printf("LVGL task is running. \r\n");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(5); 

    nv3401_gpio_init();
    nv3401_lcd_init();

    lv_init();
	lv_port_disp_init();  
	lv_port_indev_init();  

	setup_ui(&guider_ui);
	events_init(&guider_ui);
    // images_init(&guider_ui);

    ISL1208_Time_t time_read;
    ISL1208_GetTime(&time_read);
    // update_time_display(&time_read);
    while (1) {

        static TickType_t xLastTickCount = 0;
        TickType_t xCurrentTickCount = xTaskGetTickCount();
        uint32_t elapsed_ticks = xCurrentTickCount - xLastTickCount;
        xLastTickCount = xCurrentTickCount;

        lv_tick_inc(elapsed_ticks * portTICK_PERIOD_MS); 

        lv_task_handler();
        updateTaskStep();
        updatetemp();
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}


