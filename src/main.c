/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>

// 定义广播数据
// BT_DATA_BYTES：原始数据
// BT_DATA      ：带类型的数据
// 格式为：长度、类型、数据
// 0x02, 0x01, 0x06: Flags (LE General Discoverable Mode, BR/EDR Not Supported)
// 0x0b, 0x09, 'N', 'C', 'S', ' ', 'H', 'e', 'l', 'l', 'o': Complete Local Name "NCS Hello"
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, "NCS Hello", 9),
};

// 蓝牙协议栈就绪后的回调函数
static void bt_ready(int err)
{
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	// 启动广播
	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

// 主函数
void main(void)
{
	int err;

	printk("Starting BLE Hello World\n");

	// 初始化蓝牙子系统，并注册回调函数
	err = bt_enable(bt_ready);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
	}
}
