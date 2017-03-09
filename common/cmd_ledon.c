
/*
 * (C) Copyright 2010
 * Jason Kridner <jkridner@beagleboard.org>
 *
 * Based on cmd_led.c patch from:
 * http://www.mail-archive.com/u-boot@lists.denx.de/msg06873.html
 * (C) Copyright 2008
 * Ulf Samuelsson <ulf.samuelsson@atmel.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <status_led.h>
#include <asm/arch-exynos/cpu.h>
#include <asm/arch-exynos/gpio.h>
void do_ledon(cmd_tbl_t* cmdtp,int flag,int argc,char *argv[])
{
//	gpio_get_value();
//	gpio_direction_output(unsigned gpio, int value)

	struct exynos4_gpio_part2 *gpio = (struct exynos4_gpio_part2*)EXYNOS4_GPIO_PART2_BASE;
	s5p_gpio_direction_output(&gpio->x1, 0, 1);
	printf("do_ledon\n");
	return;
}
U_BOOT_CMD(
	ledon, 3, 1, do_ledon,"led_on onon ","on on on"
);
void test_biao_hao(int arg)
{
	int * b;
	b = _TEXT_BASE; 
}
void do_ledoff(cmd_tbl_t* cmdtp,int flag,int argc,char *argv[])
{
//	gpio_get_value();
//	gpio_direction_output(unsigned gpio, int value)

	struct exynos4_gpio_part2 *gpio = (struct exynos4_gpio_part2*)EXYNOS4_GPIO_PART2_BASE;
	s5p_gpio_direction_output(&gpio->x1, 0, 0);
	printf("do_ledon , %x\n",_TEXT_BASE);
	return;
}
U_BOOT_CMD(
	ledoff, 3, 1, do_ledoff,"led_on onon ","on on on"
);

