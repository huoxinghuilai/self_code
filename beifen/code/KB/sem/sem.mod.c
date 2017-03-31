#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x14522340, "module_layout" },
	{ 0x4f1939c7, "per_cpu__current_task" },
	{ 0xf9a482f9, "msleep" },
	{ 0xfc4f55f3, "down_interruptible" },
	{ 0xea147363, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x748caf40, "down" },
	{ 0x3f1899f1, "up" },
	{ 0x7e9ebb05, "kernel_thread" },
	{ 0x9edbecae, "snprintf" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "50E24BC8F4AAF3D80FBB105");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 7,
	.rhel_release = 572,
};
