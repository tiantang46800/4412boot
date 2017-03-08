//make fs4412_config 通过执行执行，进入Makefile，匹配%_config,执行了mkconfig，配置了cpu、board等信息

//make    通过编译找到连接脚本文件
	
//u-boot.lds 文件说明了第一条指令的位置

//uboot代码入口点
//arch/arm/cpu/armv7/start.S 
{
	//设置svc模式
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr,r0
	//点灯测试  串口初始化前的指示

	//设置中断向量
	ldr	r0, =_start
	mcr	p15, 0, r0, c12, c0, 0	@Set VBAR

	//关闭 mmu，tlb cache 
	// * Invalidate L1 I/D
	// * disable MMU stuff and caches
	bl cpu_init_cp15 

	//关闭看门狗 ,时钟初始化，内存初始化，串口初始化
	bl cpu_init_crit 
		b lowlevel_init 

	//一大堆内存数据结构的准备，一大堆硬件的初始化，代码重定位
	//看具体信息，把include/common.h DEBUG 打开
	bl _main 

}

//board/samsung/fs4412/lowlevel_init.S
{
	lowlevel_init:
		//关闭看门狗 
		ldr r0, =0x1002040c
		ldr r1, =0x00
		str r1, [r0]
		//时钟初始化，
		bl system_clock_init
		//内存初始化，
		bl mem_ctrl_asm_init
		//串口初始化
		bl uart_asm_init
}


//arch/arm/lib/crt0.S
{
_main:
		//一大堆内存数据结构的准备，一大堆硬件的初始化，
	bl board_init_f 
	{
		init_fnc_t *init_sequence[] = {
			arch_cpu_init,		/* basic arch cpu dependent setup */
			mark_bootstage,
			timer_init,		/* initialize timer */
			env_init,		/* initialize environment */
			init_baudrate,		/* initialze baudrate settings */
			serial_init,		/* serial communications setup */
			console_init_f,		/* stage 1 init of console */
			display_banner,		/* say that we are here */
			print_cpuinfo,		/* display cpu info (and speed) */
			checkboard,		/* display board info */
			init_func_i2c,
			dram_init,		/* configure available RAM banks */
			NULL,
		};
	}
	    //代码重定位
	b  relocate_code
here://进入主代码
	//初始化bss
	ldr	pc, =board_init_r	/* this is auto-relocated! */
}
//arch/arm/lib/board.c 
{
	board_init_f 
	{
		//一大堆内存数据结构的准备，一大堆硬件的初始化，
	}
	board_init_r 
	{
		for (;;) {
			//进入主代码
			main_loop();
		}
	}
}


//common/main.c
{
	main_loop
	{
		s = getenv ("bootdelay");
		s = getenv ("bootcmd");
		if (bootdelay != -1 && s && !abortboot(bootdelay)) {
			run_command_list(s, -1, 0);
		}
		for (;;) {
			len = readline (CONFIG_SYS_PROMPT);
			rc = run_command(lastcommand, flag);
		}
	}
}
