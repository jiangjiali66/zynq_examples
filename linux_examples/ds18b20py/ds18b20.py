# -*- coding: utf-8 -*-

import ds18b20
ds18b20.init(0x41210000, 1, 0)
while True:
	print "温度为 %.2f°C" %ds18b20.transform()
ds18b20.exit()
