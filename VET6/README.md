# BSP README 模板

## 简介

本文档为 VET6自己制作开发板的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

【此处简单介绍一下开发板】

开发板外观如下图所示：
![5f52000e8148e01f51626d40f35b915](https://user-images.githubusercontent.com/78582677/211826402-46a93617-7759-4b29-8344-34db7c43cd2b.jpg)


该开发板常用 **板载资源** 如下：

- MCU：STM32F103VET6，主频 72MHz，512KB FLASH ，64KB RAM
- 外部 RAM：型号，0MB
- 外部 FLASH：型号，16MB

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供RT-Thread Studio工程。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。st-link进行程序下载。

#### 运行结果

下载程序成功之后，系统会自动运行，【这里写开发板运行起来之后的现象，如：LED 闪烁等】。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.0.0 build Jan 11 2023 17:31:04
 2006 - 2022 Copyright by RT-Thread team
[I/SFUD] Find a Winbond flash chip. Size is 16777216 bytes.
[I/SFUD] W25Q128 flash device is initialize success.
[I/SFUD] Probe SPI flash W25Q128 by SPI device spi20 success.
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1 ，Flash 等功能，如果需要更多功能，需要利用 setting工具对BSP 进行配置，相关博客如下：

https://blog.csdn.net/qq_45902737?spm=1000.2115.3001.5343

## 注意事项

- 自制板卡非专业布线

## 联系人信息

维护人:

-  [zxy](https://github.com/ZosCat1), 邮箱：<1308465141@qq.com>
