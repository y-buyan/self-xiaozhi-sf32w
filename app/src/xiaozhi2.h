#ifndef XIAOZHI2_H
#define XIAOZHI2_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <rtthread.h>
#include "lwip/api.h"
#include "lwip/apps/websocket_client.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/apps/mqtt.h"
#include "xiaozhi.h"
#include "bf0_hal.h"
#include "bts2_app_pan.h"
#include <cJSON.h>
#include "button.h"
#include "audio_server.h"
    /**
     * @brief xiaozhi websocket cntext 数据结构体
     */
    typedef struct
    {
        uint32_t sample_rate;
        uint32_t frame_duration;
        uint8_t session_id[12];
        wsock_state_t clnt;
        rt_sem_t sem;
        uint8_t is_connected;
    } xiaozhi_ws_t;

    typedef enum
    {
        BUTTON_EVENT_NONE,
        BUTTON_EVENT_PRESSED,
        BUTTON_EVENT_RELEASED,
    } button_event_type_t;

#ifdef __cplusplus
}
#endif

#endif // XIAOZHI2_H