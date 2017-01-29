/*
 * DataController.h
 *
 *  Created on: Jan 29, 2017
 *      Author: matt
 */

#ifndef DATACONTROLLER_H_
#define DATACONTROLLER_H_

class DataController {
public:

	double rpm = 1.0;
	double engineThrottle = 1.0;
	double speed = 1.0;
	double airIntakeTemp = 1.0;
	double engineCoolantTemp = 1.0;
	double manifoldABS = 1.0;
	double roll = 0.0;
	double pitch = 0.0;
	double yaw = 0.0;
	double mx = 0.0;
	double my = 0.0;

	DataController();
	virtual ~DataController();
	void UpdateOBD();
	void UpdateAccel();
};

#endif /* DATACONTROLLER_H_ */
