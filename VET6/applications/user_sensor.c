/*
 * 程序清单：这是一个 传感器 设备使用例程
 * 例程导出了 sensor_sample 命令到控制终端
 * 命令调用格式：sensor_sample dev_name
 * 命令解释：命令第二个参数是要使用的传感器设备名称
 * 程序功能：打开对应的传感器，然后连续读取 5 次数据并打印出来。
*/
#include "rtconfig.h"
#ifdef RT_USING_SENSOR
#include "sensor.h"


static void sensor_show_data(rt_size_t num, rt_sensor_t sensor, struct rt_sensor_data *sensor_data)
{
    switch (sensor->info.type)
    {
    case RT_SENSOR_TYPE_ACCE:
        rt_kprintf("num:%3d, x:%5d, y:%5d, z:%5d, timestamp:%5d\n", num, sensor_data->data.acce.x, sensor_data->data.acce.y, sensor_data->data.acce.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_GYRO:
        rt_kprintf("num:%3d, x:%8d, y:%8d, z:%8d, timestamp:%5d\n", num, sensor_data->data.gyro.x, sensor_data->data.gyro.y, sensor_data->data.gyro.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_MAG:
        rt_kprintf("num:%3d, x:%5d, y:%5d, z:%5d, timestamp:%5d\n", num, sensor_data->data.mag.x, sensor_data->data.mag.y, sensor_data->data.mag.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_HUMI:
        rt_kprintf("num:%d, humi:%2.2f%%, timestamp:%u\r\n", num, sensor_data->data.humi,sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_TEMP:
        rt_kprintf("num:%d, temp:%2.2fC, timestamp:%u\r\n", num, sensor_data->data.temp,sensor_data->timestamp);
        break;
    default:
        break;
    }
}

static void sensor_sample(int argc, char **argv)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_size_t res, i;

    /* 查找系统中的传感器设备 */
    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't find device:%s\n", argv[1]);
        return;
    }

    /* 以轮询模式打开传感器设备 */
    if (rt_device_open(dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }

    for (i = 0; i < 5; i++)
    {
        /* 从传感器读取一个数据 */
        res = rt_device_read(dev, 0, &data, 1);
        if (res != 1)
        {
            rt_kprintf("read data failed!size is %d", res);
        }
        else
        {
            sensor_show_data(i, (rt_sensor_t)dev, &data);
        }
        rt_thread_mdelay(100);
    }
    /* 关闭传感器设备 */
    rt_device_close(dev);
}
MSH_CMD_EXPORT(sensor_sample, sensor device sample);
#endif
