#include <rtthread.h>
#include <wrtnode2r_board.h>

void rt_platform_init(void)
{
    wrtnode2r_spi_bridge_init("bridge");
}
