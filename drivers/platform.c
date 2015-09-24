#include <rtthread.h>
#include <board.h>

void rt_platform_init(void)
{
    wrtnode2r_spi_bridge_init("bridge");
}
