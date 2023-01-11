#include "disp_driver.h"
// #include "rtconfig.h"
static int fill_test(int argc, char **argv)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    rt_uint16_t xend, yend;
#if defined(SSUD_BACKLIGHT_SWITCH) || defined(SSUD_BACKLIGHT_PWM)
    if (argc == 2)
    {
        ssud_backlight_light_set(atoi(argv[1]));
    }
    else
    {
        ssud_backlight_light_set(100);
    }
#endif

#if defined(SSUD_DISP_ORIENTATION_PORTRAIT) || defined(SSUD_DISP_ORIENTATION_PORTRAIT_INVERTED)
    xend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_VER_RES :SSUD_DISP_HOR_RES;
    yend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_HOR_RES :SSUD_DISP_VER_RES;
#elif defined(SSUD_DISP_ORIENTATION_LANDSCAPE) || defined(SSUD_DISP_ORIENTATION_LANDSCAPE_INVERTED)
    xend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_HOR_RES :SSUD_DISP_VER_RES;
    yend = SSUD_DISP_HOR_RES > SSUD_DISP_VER_RES ? SSUD_DISP_VER_RES :SSUD_DISP_HOR_RES;
#endif

    ssud_disp_driver_fill(0, 0, xend-1, yend-1, &color1);
    ssud_disp_driver_fill(0, 0, xend/2-1, yend/2-1, &color2);
    ssud_disp_driver_fill(xend/2, yend/2, xend-1, yend-1, &color3);
    ssud_disp_driver_fill(xend/4, yend/4, xend/4*3-1, yend/4*3-1, &color4);

    ssud_disp_driver_fill(0, 0, 0, yend-1, &color5);
    ssud_disp_driver_fill(0, 0, xend-1, 0, &color5);
    ssud_disp_driver_fill(xend-1, 0, xend-1, yend-1, &color5);
    ssud_disp_driver_fill(0, yend-1, xend-1, yend-1, &color5);

    ssud_disp_driver_fill(xend/8, yend/8, xend/4, yend/4, &color4);
    return 0;
}

MSH_CMD_EXPORT(fill_test, fill_test);

static void full_all()
{
    rt_uint16_t x_start,y_start;
    rt_uint16_t x_end,y_end;
    x_start=0;
    x_end=80;
    y_start=0;
    y_end=160;
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    ssud_disp_driver_fill(x_start,y_start,x_end,y_end,&color2);
}
MSH_CMD_EXPORT(full_all, full_all);

static void lcd_point(int x, int y ,void *pcolor)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    rt_uint16_t x_start,y_start;
    rt_uint16_t x_end,y_end;
    x_start=x_end=x;
    y_start=y_end=y;
    ssud_st7735s_fill(x_start, y_start, x_end, y_end, &pcolor);
}
static void point_tesr(void)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    lcd_point(10,10,color5);


}
MSH_CMD_EXPORT(point_tesr, point);


static void draw_circle(int x, int y, int r, void *pcolor)
{
    int a, b, num;
    a = 0;
    b = r;
    while(22 * b * b >= r * r)          // 1/8Ô²¼´¿É
    {
        lcd_point(x + a, y - b,pcolor); // 0~1
        lcd_point(x - a, y - b,pcolor); // 0~7
        lcd_point(x - a, y + b,pcolor); // 4~5
        lcd_point(x + a, y + b,pcolor); // 4~3

        lcd_point(x + b, y + a,pcolor); // 2~3
        lcd_point(x + b, y - a,pcolor); // 2~1
        lcd_point(x - b, y - a,pcolor); // 6~7
        lcd_point(x - b, y + a,pcolor); // 6~5

        a++;
        num = (a * a + b * b) - r*r;
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}
static void user_draw_circle(void)
{
    rt_uint16_t color1 = BLUE;
    rt_uint16_t color2 = GRAY;
    rt_uint16_t color3 = GREEN;
    rt_uint16_t color4 = YELLOW;
    rt_uint16_t color5 = RED;
    draw_circle(40,80,40,color5);
    draw_line(0,80,80,100,color4);
}
MSH_CMD_EXPORT(user_draw_circle, draw_circle);

void draw_line(int x1,int y1,int x2,int y2,void *pcolor)
{
    int dx,dy,e;
    dx=x2-x1;
    dy=y2-y1;
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1+=1;e-=dx;}
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1+=1;e-=dy;}
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1-=1;e-=dx;}
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1+=1;e-=dy;}
                    y1-=1;
                    e+=dx;
                }
            }
        }
    }
    else //dx<0
    {
        dx=-dx;     //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1+=1;e-=dx;}
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1-=1;e-=dy;}
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){y1-=1;e-=dx;}
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    lcd_point(x1,y1,pcolor);
                    if(e>0){x1-=1;e-=dy;}
                    y1-=1;
                    e+=dx;
                }
            }
        }
    }
}
