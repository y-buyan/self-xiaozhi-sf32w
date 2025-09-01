#include "bsp_board.h"

void BSP_GPIO_Set(int pin, int val, int is_porta)
{
    GPIO_TypeDef *gpio = (is_porta) ? hwp_gpio1 : hwp_gpio2;
    GPIO_InitTypeDef GPIO_InitStruct;

    // set sensor pin to output mode
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(gpio, &GPIO_InitStruct);

    // set sensor pin to high == power on sensor board
    HAL_GPIO_WritePin(gpio, pin, (GPIO_PinState)val);
}

#define MPI2_POWER_PIN  (11)

__WEAK void BSP_PowerDownCustom(int coreid, bool is_deep_sleep)
{

}

__WEAK void BSP_PowerUpCustom(bool is_deep_sleep)
{
    HAL_PMU_ConfigPeriLdo(PMUC_PERI_LDO_EN_VDD33_LDO3_Pos, 1, 1);
}

extern void *rt_flash_get_handle_by_addr(uint32_t addr);
void BSP_Power_Up(bool is_deep_sleep)
{
    BSP_PowerUpCustom(is_deep_sleep);
#ifdef SOC_BF0_HCPU
    if (!is_deep_sleep)
    {
#ifdef BSP_USING_PSRAM1
        bsp_psram_exit_low_power("psram1");
#endif /* BSP_USING_PSRAM1 */
#ifdef BSP_USING_NOR_FLASH2
        FLASH_HandleTypeDef *flash_handle;
        flash_handle = (FLASH_HandleTypeDef *)rt_flash_get_handle_by_addr(MPI2_MEM_BASE);
        HAL_FLASH_RELEASE_DPD(flash_handle);
        HAL_Delay_us(80);
#endif
    }
#endif  /* SOC_BF0_HCPU */
}

void BSP_IO_Power_Down(int coreid, bool is_deep_sleep)
{
    BSP_PowerDownCustom(coreid, is_deep_sleep);
#ifdef SOC_BF0_HCPU
    if (coreid == CORE_ID_HCPU)
    {
#ifdef BSP_USING_PSRAM1
        bsp_psram_enter_low_power("psram1");
#endif /* BSP_USING_PSRAM1 */
#ifdef BSP_USING_NOR_FLASH2
        FLASH_HandleTypeDef *flash_handle;
        flash_handle = (FLASH_HandleTypeDef *)rt_flash_get_handle_by_addr(MPI2_MEM_BASE);
        HAL_FLASH_DEEP_PWRDOWN(flash_handle);
        HAL_Delay_us(3);
#endif
    }
#endif  /* SOC_BF0_HCPU */
}

void BSP_SDIO_Power_Up(void)
{
#ifdef RT_USING_SDIO
    // TODO: Add SDIO power up

#endif

}
void BSP_SDIO_Power_Down(void)
{
#ifdef RT_USING_SDIO
    // TODO: Add SDIO power down
#endif
}


