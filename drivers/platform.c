#include <rtthread.h>
#include <wrtnode2r_board.h>

void rt_platform_init(void)
{
    spi_bridge_register("bridge");
}
