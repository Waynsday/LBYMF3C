# LBYMF3C
Plant.tio Project

Developer: Wayne Akeboshi

Contributors: Reign Balajadia, Mary Cotoco

ABSTRACT
Plan.tio uses a single master controller and multiple slave controllers, with which the former gathers light and temperature data and the latter receives data, opens water pumps, and controls the LED indicators. The master board is triggered with sunlight, a trigger that is disabled until the sun sets, which sends a trigger and temperature data to the slave controllers. Upon the receipt of data, the slave controllers simultaneously water the plants, wherein any slave with a kill-switch turned on be an exception. Plan.tio is fully scalable following a 1 plant to 1 slave controller ratio, all of which can be independently disabled using kill-switches. For recommendation, integration of an internal clock system, LCD display, and IR remote or bluetooth feature will significantly improve the effectiveness of Plan.tio as well as the user-interface overall. 

Included files:
- Circuit schematic
- Bill of materials
- Ino files (plan_tio1 master board, plan_tio2&3 slave boards)
