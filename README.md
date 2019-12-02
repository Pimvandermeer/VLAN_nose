# VLAN_nose

Arduino_project_checking_VLANS

Arduino-tool  to check what VLAN is configured at a certain Wall outlet. 


At a IT-servicedesk we have sometime the trouble that we have different VLAN's but the technicians in the factory don't know
in what of port of the switch they need to plug the ethetnet cable into. Sometimes we needed to go to the factory to see what happens..Till NOW!

The Arduino with a W5200 shield and a I2c_liquidcrystaldisplay (lcd) resolves this issue.

You need to make MAC-reservations in every DHCP-pool you have. If you have done that and uploaded the code into you're Arduino you're almost good to go!

Use a 9v battery or powerpack and give this to the technician if something is not working you can ask them to use this device. They have to plug the cable into the arduino and tell what they see, if they tell you a IP adress you do not expect you know something is wrong. 

